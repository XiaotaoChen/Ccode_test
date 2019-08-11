// header file to use mshadow
#include "mshadow/tensor.h"

#include <vector>

// this namespace contains all data structures, functions
using namespace mshadow;
// this namespace contains all operator overloads
using namespace mshadow::expr;

template<typename Device, int dim>
std::vector<int> get_tensor_vec(Tensor<Device, dim, float> tensor) {
  int kdim = tensor.shape_.kDimension;
  std::vector<int> shape_vec(kdim);
  for (int i=0; i < kdim; i++) {
    shape_vec[i] = tensor.shape_[i];
  }
  return shape_vec;
}

void print_vec(std::vector<int> vec){
  int size = vec.size();
  for (int i=0; i< size; i++) {
    printf("%d, ", vec[i]);
  }
  printf("\n");
}

//template <typename Device, int dim>
//float get_sum(Tensor<Device, dim, float> tensor) {
//  float dst = 0.0f;
//
//  for (int i=0; i< tensor.size)
//  red::sum(dst, )
//}

int main(void) {
  // intialize tensor engine before using tensor operation, needed for CuBLAS
  InitTensorEngine<cpu>();
  // assume we have a float space
  float data[20];
  // create a 2 x 5 x 2 tensor, from existing space
  Tensor<cpu, 3> ts(data, Shape3(2,5,2));
  // take first subscript of the tensor
  Tensor<cpu, 2> mat = ts[0];
  // Tensor object is only a handle, assignment means they have same data content
  // we can specify content type of a Tensor, if not specified, it is float bydefault
  Tensor<cpu, 2, float> mat2 = mat;
  mat = Tensor<cpu, 1>(data, Shape1(10)).FlatTo2D();

  // shaape of matrix, note size order is same as numpy
  printf("%u X %u matrix\n", mat.size(0), mat.size(1));

  std::vector<int> shape_vec = get_tensor_vec<cpu, 2>(mat);
  print_vec(shape_vec);


  // initialize all element to zero
  mat = 0.0f;
  // assign some values
  mat[0][1] = 1.0f; mat[1][0] = 2.0f;
  printf("mat[0,1]: %f, mat[1,0]: %f, (0): %d, (1):%d\n",
          mat[0][1], mat[1][0], mat.size(0), mat.size(1));
  // elementwise operations
  mat += (mat + 10.0f) / 10.0f + 2.0f;

  // print out matrix, note: mat2 and mat1 are handles(pointers)
  for (index_t i = 0; i < mat.size(0); ++i) {
    for (index_t j = 0; j < mat.size(1); ++j) {
      printf("%.2f ", mat2[i][j]);
    }
    printf("\n");
  }

  Tensor<cpu, 1, float> mat1D = mat.FlatTo1D();
  int size = mat1D.size(0);
  float dst = 0.0f;
  for (int i=0; i< size; i++) {
    red::sum::Reduce(dst, mat1D[i]);
  }
  printf("sum(mat):%.2f\n", dst);


//  TensorContainer<cpu, 2> lhs(Shape2(2, 3)), rhs(Shape2(2, 3)), ret(Shape2(2,2));
//  lhs = 1.0;
//  rhs = 1.0;
//  ret = implicit_dot(lhs, rhs.T());
//  VectorDot(ret[0].Slice(0, 1), lhs[0], rhs[0]);
//  printf("vdot=%f\n", ret[0][0]);
//  int cnt = 0;
//  for (index_t i = 0; i < ret.size(0); ++i) {
//    for (index_t j = 0; j < ret.size(1); ++j) {
//      printf("%.2f ", ret[i][j]);
//    }
//    printf("\n");
//  }
//
//  printf("\n");
//
//  for (index_t i = 0; i < lhs.size(0); ++i) {
//    for (index_t j = 0; j < lhs.size(1); ++j) {
//      lhs[i][j] = cnt++;
//      printf("%.2f ", lhs[i][j]);
//    }
//    printf("\n");
//  }
//  printf("\n");
//  TensorContainer<cpu, 1> index(Shape1(2)), choosed(Shape1(2));
//  index[0] = 1; index[1] = 2;
//  choosed = mat_choose_row_element(lhs, index);
//  for (index_t i = 0; i < choosed.size(0); ++i) {
//    printf("%.2f ", choosed[i]);
//  }
//  printf("\n");
////
//  TensorContainer<cpu, 2> recover_lhs(Shape2(2, 3)), small_mat(Shape2(2, 3));
//  small_mat = -100.0f;
//  recover_lhs = mat_fill_row_element(small_mat, choosed, index);
//  for (index_t i = 0; i < recover_lhs.size(0); ++i) {
//    for (index_t j = 0; j < recover_lhs.size(1); ++j) {
//      printf("%.2f ", recover_lhs[i][j] - lhs[i][j]);
//    }
//  }
//  printf("\n");
//
//  rhs = one_hot_encode(index, 3);
//
//  for (index_t i = 0; i < lhs.size(0); ++i) {
//    for (index_t j = 0; j < lhs.size(1); ++j) {
//      printf("%.2f ", rhs[i][j]);
//    }
//    printf("\n");
//  }
//  printf("\n");
//  TensorContainer<cpu, 1> idx(Shape1(3));
//  idx[0] = 8;
//  idx[1] = 0;
//  idx[2] = 1;
//
//  TensorContainer<cpu, 2> weight(Shape2(10, 5));
//  TensorContainer<cpu, 2> embed(Shape2(3, 5));
//
//  for (index_t i = 0; i < weight.size(0); ++i) {
//    for (index_t j = 0; j < weight.size(1); ++j) {
//      weight[i][j] = i;
//    }
//  }
//  embed = take(idx, weight);
//  for (index_t i = 0; i < embed.size(0); ++i) {
//    for (index_t j = 0; j < embed.size(1); ++j) {
//      printf("%.2f ", embed[i][j]);
//    }
//    printf("\n");
//  }
//  printf("\n\n");
//  weight = take_grad(idx, embed, 10);
//  for (index_t i = 0; i < weight.size(0); ++i) {
//    for (index_t j = 0; j < weight.size(1); ++j) {
//      printf("%.2f ", weight[i][j]);
//    }
//    printf("\n");
//  }
//
//  printf("upsampling\n");
//  TensorContainer<cpu, 2> small(Shape2(2, 2));
//  small[0][0] = 1.0f;
//  small[0][1] = 2.0f;
//  small[1][0] = 3.0f;
//  small[1][1] = 4.0f;
//  TensorContainer<cpu, 2> large(Shape2(6, 6));
//  large = upsampling_nearest(small, 3);
//  for (index_t i = 0; i < large.size(0); ++i) {
//    for (index_t j = 0; j < large.size(1); ++j) {
//      printf("%.2f ", large[i][j]);
//    }
//    printf("\n");
//  }
//  small = pool<red::sum>(large, small.shape_, 3, 3, 3, 3);
//  // shutdown tensor enigne after usage
//  for (index_t i = 0; i < small.size(0); ++i) {
//    for (index_t j = 0; j < small.size(1); ++j) {
//      printf("%.2f ", small[i][j]);
//    }
//    printf("\n");
//  }
//
//  printf("mask\n");
//  TensorContainer<cpu, 2> mask_data(Shape2(6, 8));
//  TensorContainer<cpu, 2> mask_out(Shape2(6, 8));
//  TensorContainer<cpu, 1> mask_src(Shape1(6));
//
//  mask_data = 1.0f;
//  for (int i = 0; i < 6; ++i) {
//    mask_src[i] = static_cast<float>(i);
//  }
//  mask_out = mask(mask_src, mask_data);
//  for (index_t i = 0; i < mask_out.size(0); ++i) {
//    for (index_t j = 0; j < mask_out.size(1); ++j) {
//      printf("%.2f ", mask_out[i][j]);
//    }
//    printf("\n");
//  }
  ShutdownTensorEngine<cpu>();
  return 0;
}
