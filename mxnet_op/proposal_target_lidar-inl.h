/*!
 * Copyright (c) 2019 by TuSimple
 * \file proposal_target_lidar-inl.h
 * \brief C++ version proposal target
 * \author Xiaotao Chen
 */
#ifndef MXNET_OPERATOR_PROPOSAL_TARGET_LIDAR_INL_H_
#define MXNET_OPERATOR_PROPOSAL_TARGET_LIDAR_INL_H_

#include <dmlc/logging.h>
#include <dmlc/parameter.h>
#include <mxnet/operator.h>
#include <cmath>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include "../operator_common.h"

#include <iostream>

namespace mshadow {
namespace proposal_target_lidar_v1 {
template <typename DType>
inline void SampleROI(
  const Tensor<cpu, 2, DType> &all_rois,
  const Tensor<cpu, 2, DType> &gt_boxes,
  const Tensor<cpu, 1, DType> &bbox_mean,
  const Tensor<cpu, 1, DType> &bbox_std,
  const Tensor<cpu, 1, DType> &bbox_weight,
  const index_t fg_rois_per_image,
  const index_t rois_per_image,
  const index_t num_classes,
  const float fg_thresh,
  const float bg_thresh_hi,
  const float bg_thresh_lo,
  const bool class_agnostic,
  Tensor<cpu, 2, DType> &&rois,
  Tensor<cpu, 1, DType> &&labels,
  Tensor<cpu, 2, DType> &&bbox_targets,
  Tensor<cpu, 2, DType> &&bbox_weights
);

template <typename DType>
void BBoxOverlap(
  const Tensor<cpu, 2, DType> &boxes,
  const Tensor<cpu, 2, DType> &query_boxes,
  Tensor<cpu, 2, DType> &overlaps
);

template <typename DType>
void ExpandBboxRegressionTargets(
  const Tensor<cpu, 2, DType> &bbox_target_data,
  Tensor<cpu, 2, DType> &bbox_targets,
  Tensor<cpu, 2, DType> &bbox_weights,
  const Tensor<cpu, 1, DType> &bbox_weight
);

template <typename DType>
void NonLinearTransformWithAngleAndNormalization(
  const Tensor<cpu, 2, DType> &ex_rois,
  const Tensor<cpu, 2, DType> &gt_rois,
  Tensor<cpu, 2, DType> &targets,
  const Tensor<cpu, 1, DType> &bbox_mean,
  const Tensor<cpu, 1, DType> &bbox_std
);

template <typename DType>
void outer_gt_bbox(
  const Tensor<cpu, 2, DType> &gt_rois, 
  Tensor<cpu, 2, DType> &gt_boxes_2point
);

} // namespace proposal_target_lidar_v1
} // namespace mshadow

namespace mxnet {
namespace op {

namespace proposal_target_lidar_enum {
enum ProposalTargetLidarInputs {kRois, kGtBboxes};
enum ProposalTargetLidarOutputs {kRoiOutput, kLabel, kBboxTarget, kBboxWeight};
}

struct ProposalTargetLidarParam : public dmlc::Parameter<ProposalTargetLidarParam> {
  index_t num_classes;
  index_t batch_images;
  int image_rois;
  float fg_fraction;
  float fg_thresh;
  float bg_thresh_hi;
  float bg_thresh_lo;
  bool proposal_without_gt;
  bool class_agnostic;
  nnvm::Tuple<float> bbox_mean;
  nnvm::Tuple<float> bbox_std;
  nnvm::Tuple<float> bbox_weight;

  DMLC_DECLARE_PARAMETER(ProposalTargetLidarParam) {
    DMLC_DECLARE_FIELD(num_classes).describe("Number of classes for detection");
    DMLC_DECLARE_FIELD(batch_images).describe("Number of samples in a batch");
    DMLC_DECLARE_FIELD(image_rois).describe("Number of ROIs for one image");
    DMLC_DECLARE_FIELD(fg_thresh).describe("Foreground IOU threshold");
    DMLC_DECLARE_FIELD(bg_thresh_hi).describe("Background IOU upper bound");
    DMLC_DECLARE_FIELD(bg_thresh_lo).describe("Background IOU lower bound");
    DMLC_DECLARE_FIELD(fg_fraction).set_default(0.25f).describe("Fraction of foreground proposals");
    DMLC_DECLARE_FIELD(proposal_without_gt).describe("Do not append ground-truth bounding boxes to output");
    DMLC_DECLARE_FIELD(class_agnostic).set_default(false).describe("class agnostic bbox_target");
    float tmp[] = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
    DMLC_DECLARE_FIELD(bbox_mean).set_default(nnvm::Tuple<float>(tmp, tmp+6)).describe("Bounding box mean");
    tmp[0] = 1.f; tmp[1] = 1.f; tmp[2] = 1.f; tmp[3] = 1.f; tmp[4] = 1.f; tmp[5] = 1.f;
    DMLC_DECLARE_FIELD(bbox_std).set_default(nnvm::Tuple<float>(tmp, tmp+6)).describe("Bounding box std");
    tmp[0] = 1.f; tmp[1] = 1.f; tmp[2] = 1.f; tmp[3] = 1.f; tmp[4] = 1.f; tmp[5] = 1.f;
    DMLC_DECLARE_FIELD(bbox_weight).set_default(nnvm::Tuple<float>(tmp, tmp+6)).describe("Foreground bounding box weight");
  }
};

template<typename xpu, typename DType>
class ProposalTargetLidarOp : public Operator {
 public:
  explicit ProposalTargetLidarOp(ProposalTargetLidarParam param) {
    this->param_ = param;
  }

  virtual void Forward(const OpContext &ctx,
                       const std::vector<TBlob> &in_data,
                       const std::vector<OpReqType> &req,
                       const std::vector<TBlob> &out_data,
                       const std::vector<TBlob> &aux_args) {
    using namespace mshadow;
    using namespace mshadow::expr;
    CHECK_EQ(in_data.size(), 2);
    CHECK_EQ(out_data.size(), 4);
    CHECK_EQ(req.size(), 4);
    CHECK_EQ(req[proposal_target_lidar_enum::kRoiOutput], kWriteTo);
    CHECK_EQ(req[proposal_target_lidar_enum::kLabel], kWriteTo);
    CHECK_EQ(req[proposal_target_lidar_enum::kBboxTarget], kWriteTo);
    CHECK_EQ(req[proposal_target_lidar_enum::kBboxWeight], kWriteTo);
    Stream<xpu> *s = ctx.get_stream<xpu>();
    const index_t num_image         = param_.batch_images;
    const index_t num_roi           = in_data[proposal_target_lidar_enum::kRois].Size() / (num_image * 4);
    const index_t num_gtbbox        = in_data[proposal_target_lidar_enum::kGtBboxes].Size() / (num_image * 10);
    const int image_rois            = param_.image_rois;
    Tensor<xpu, 3, DType> xpu_rois      = in_data[proposal_target_lidar_enum::kRois].
                                          get_with_shape<xpu, 3, DType>(Shape3(num_image, num_roi, 4), s);
    Tensor<xpu, 3, DType> xpu_gt_bboxes = in_data[proposal_target_lidar_enum::kGtBboxes].
                                          get_with_shape<xpu, 3, DType>(Shape3(num_image, num_gtbbox, 10), s);
    TensorContainer<cpu, 3, DType> rois     (xpu_rois.shape_);
    TensorContainer<cpu, 3, DType> gt_bboxes(xpu_gt_bboxes.shape_);
    Copy(rois, xpu_rois, s);
    Copy(gt_bboxes, xpu_gt_bboxes, s);

    std::vector<std::vector<Tensor<cpu, 1, DType>>> kept_rois;
    std::vector<std::vector<Tensor<cpu, 1, DType>>> kept_gtbboxes;

    // clean up bboxes
    for (index_t i = 0; i < num_image; ++i) {
      kept_gtbboxes.push_back(std::vector<Tensor<cpu, 1, DType>>());
      for (index_t j = 0; j < gt_bboxes.size(1); ++j) {
        if (gt_bboxes[i][j][9] != -1) {
          kept_gtbboxes[i].push_back(gt_bboxes[i][j]);
        }
      }
    }

    index_t start = 0;
    for (index_t i = 0; i < num_image; ++i) {
      kept_rois.push_back(std::vector<Tensor<cpu, 1, DType>>());
      for (index_t j = 0; j < rois.size(1); ++j) {
        // y2 == 0 indicates padding
        if (rois[i][j][3] > 0)
          kept_rois[i].push_back(rois[i][j]);
      }
      if (!param_.proposal_without_gt) {
        // all gt bboxes are appended
        LOG(FATAL) << "proposal with gt is not supported currently";
      }
    }

    TensorContainer<cpu, 3, DType> cpu_output_rois(Shape3(num_image, image_rois, 4), 0.f);
    TensorContainer<cpu, 2, DType> cpu_labels(Shape2(num_image, image_rois), 0.f);
    TensorContainer<cpu, 3, DType> cpu_bbox_targets(Shape3(num_image, image_rois, param_.num_classes * 6), 0.f);
    TensorContainer<cpu, 3, DType> cpu_bbox_weights(Shape3(num_image, image_rois, param_.num_classes * 6), 0.f);

    index_t fg_rois_per_image = static_cast<index_t>(image_rois * param_.fg_fraction);
    TensorContainer<cpu, 1, DType> bbox_mean(Shape1(6));
    TensorContainer<cpu, 1, DType> bbox_std(Shape1(6));
    TensorContainer<cpu, 1, DType> bbox_weight(Shape1(6));
    bbox_mean[0] = param_.bbox_mean[0];
    bbox_mean[1] = param_.bbox_mean[1];
    bbox_mean[2] = param_.bbox_mean[2];
    bbox_mean[3] = param_.bbox_mean[3];
    bbox_mean[4] = param_.bbox_mean[4];
    bbox_mean[5] = param_.bbox_mean[5];
    bbox_std[0] = param_.bbox_std[0];
    bbox_std[1] = param_.bbox_std[1];
    bbox_std[2] = param_.bbox_std[2];
    bbox_std[3] = param_.bbox_std[3];
    bbox_std[4] = param_.bbox_std[4];
    bbox_std[5] = param_.bbox_std[5];
    bbox_weight[0] = param_.bbox_weight[0];
    bbox_weight[1] = param_.bbox_weight[1];
    bbox_weight[2] = param_.bbox_weight[2];
    bbox_weight[3] = param_.bbox_weight[3];
    bbox_weight[4] = param_.bbox_weight[4];
    bbox_weight[5] = param_.bbox_weight[5];

    const int omp_threads(engine::OpenMP::Get()->GetRecommendedOMPThreadCount());
    #pragma omp parallel for num_threads(omp_threads)
    for (index_t i = 0; i < num_image; ++i) {
      if (kept_gtbboxes[i].size() == 0)
        continue;
      TensorContainer<cpu, 2, DType> kept_rois_i    (Shape2(kept_rois[i].size(),     rois.size(2)));
      TensorContainer<cpu, 2, DType> kept_gtbboxes_i(Shape2(kept_gtbboxes[i].size(), gt_bboxes.size(2)));
      for (index_t j = 0; j < kept_rois_i.size(0); ++j) {
          Copy(kept_rois_i[j], kept_rois[i][j]);
      }
      for (index_t j = 0; j < kept_gtbboxes_i.size(0); ++j) {
          Copy(kept_gtbboxes_i[j], kept_gtbboxes[i][j]);
      }
      proposal_target_lidar_v1::SampleROI(
        kept_rois_i, 
        kept_gtbboxes_i, 
        bbox_mean, 
        bbox_std, 
        bbox_weight,
        fg_rois_per_image, 
        image_rois,
        param_.num_classes, 
        param_.fg_thresh, 
        param_.bg_thresh_hi, 
        param_.bg_thresh_lo,
        param_.class_agnostic,
        cpu_output_rois[i],
        cpu_labels[i],
        cpu_bbox_targets[i],
        cpu_bbox_weights[i]
      );
    }

    Tensor<xpu, 3, DType> xpu_output_rois  = out_data[proposal_target_lidar_enum::kRoiOutput].
                                             get_with_shape<xpu, 3, DType>(Shape3(num_image, image_rois, 4), s);
    Tensor<xpu, 2, DType> xpu_labels       = out_data[proposal_target_lidar_enum::kLabel].
                                             get_with_shape<xpu, 2, DType>(Shape2(num_image, image_rois), s);
    Tensor<xpu, 3, DType> xpu_bbox_targets = out_data[proposal_target_lidar_enum::kBboxTarget].
                                             get_with_shape<xpu, 3, DType>(Shape3(num_image, image_rois, param_.num_classes * 6), s);
    Tensor<xpu, 3, DType> xpu_bbox_weights = out_data[proposal_target_lidar_enum::kBboxWeight].
                                             get_with_shape<xpu, 3, DType>(Shape3(num_image, image_rois, param_.num_classes * 6), s);

    Copy(xpu_output_rois, cpu_output_rois, s);
    Copy(xpu_labels, cpu_labels, s);
    Copy(xpu_bbox_targets, cpu_bbox_targets, s);
    Copy(xpu_bbox_weights, cpu_bbox_weights, s);
  }

  virtual void Backward(const OpContext &ctx,
                        const std::vector<TBlob> &out_grad,
                        const std::vector<TBlob> &in_data,
                        const std::vector<TBlob> &out_data,
                        const std::vector<OpReqType> &req,
                        const std::vector<TBlob> &in_grad,
                        const std::vector<TBlob> &aux_args) {
    using namespace mshadow;
    using namespace mshadow::expr;
    CHECK_EQ(in_grad.size(), 2);
    const index_t num_image         = param_.batch_images;
    const index_t num_gtbbox        = in_data[proposal_target_lidar_enum::kGtBboxes].Size() / (num_image * 10);

    Stream<xpu> *s = ctx.get_stream<xpu>();
    Tensor<xpu, 3, DType> rois      = in_grad[proposal_target_lidar_enum::kRois].get<xpu, 3, DType>(s);
    Tensor<xpu, 3, DType> gt_bboxes = in_grad[proposal_target_lidar_enum::kGtBboxes].get_with_shape<xpu, 3, DType>(Shape3(num_image, num_gtbbox, 10), s);

    rois = 0.f;
    gt_bboxes = 0.f;
  }

 private:
  ProposalTargetLidarParam param_;
};  // class ProposalTargetLidarOp

template<typename xpu>
Operator *CreateOp(ProposalTargetLidarParam param, int dtype);

#if DMLC_USE_CXX11
class ProposalTargetLidarProp : public OperatorProperty {
 public:
  void Init(const std::vector<std::pair<std::string, std::string> > &kwargs) override {
    param_.Init(kwargs);
  }

  std::map<std::string, std::string> GetParams() const override {
    return param_.__DICT__();
  }

  int NumVisibleOutputs() const override {
    return 4;
  }

  int NumOutputs() const override {
    return 4;
  }

  std::vector<std::string> ListArguments() const override {
    return {"rois", "gt_boxes"};
  }

  std::vector<std::string> ListOutputs() const override {
    return {"roi_output", "label", "bbox_target", "bbox_weight"};
  }

  bool InferShape(std::vector<TShape> *in_shape,
                  std::vector<TShape> *out_shape,
                  std::vector<TShape> *aux_shape) const override {
    using namespace mshadow;
    CHECK_EQ(in_shape->size(), 2) << "Input:[rois, gt_boxes]";
    const TShape &dshape = in_shape->at(proposal_target_lidar_enum::kRois);
    const int image_rois  = param_.image_rois;

    auto output_rois_shape = Shape3(dshape[0], image_rois, 4);
    auto label_shape = Shape2(dshape[0], image_rois);
    auto bbox_target_shape = Shape3(dshape[0], image_rois, param_.num_classes * 6);
    auto bbox_weight_shape = Shape3(dshape[0], image_rois, param_.num_classes * 6);

    out_shape->clear();
    out_shape->push_back(output_rois_shape);
    out_shape->push_back(label_shape);
    out_shape->push_back(bbox_target_shape);
    out_shape->push_back(bbox_weight_shape);
    aux_shape->clear();

    return true;
  }

  std::vector<int> DeclareBackwardDependency(
      const std::vector<int> &out_grad,
      const std::vector<int> &in_data,
      const std::vector<int> &out_data) const override {
    return {};
  }

  std::string TypeString() const override {
    return "_contrib_ProposalTargetLidar";
  }

  OperatorProperty *Copy() const override {
    auto ptr = new ProposalTargetLidarProp();
    ptr->param_ = param_;
    return ptr;
  }

  Operator *CreateOperator(Context ctx) const override {
    LOG(FATAL) << "Not Implemented.";
    return NULL;
  }

  Operator *CreateOperatorEx(Context ctx, std::vector<TShape> *in_shape,
                             std::vector<int> *in_type) const override;

 private:
  ProposalTargetLidarParam param_;
};  // class ProposalTargetLidarProp
#endif  // DMLC_USE_CXX11

}  // namespace op
}  // namespace mxnet

#endif  // MXNET_OPERATOR_PROPOSAL_TARGET_LIDAR_INL_H_
