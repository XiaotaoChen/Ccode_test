#include "mshadow/tensor.h"

using namespace mshadow;

template <int dim>
void print_tensor(Tensor<cpu, dim, float > tensor);

template <>
void print_tensor(Tensor<cpu, 2, float> tensor) {
    for (int i=0; i<tensor.size(0); i++) {
        for (int j=0; j< tensor.size(1); j++) {
            printf("%.2f,", tensor[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}

void assign_tensor(Tensor<cpu, 2, float> &tensor) {
    for(int i=0; i< tensor.size(0); i++) {
        for(int j=0; j< tensor.size(1); j++) {
            tensor[i][j] += i * tensor.size(1) + j;
        }
    }
}

struct maxoftwo {
    // map can also be normal functions,
    // however, this can only be applied to float tensor
    MSHADOW_XINLINE static float Map(float a, float b) {
        if(a > b) return a;
        else return b;
    }
};

int main() {
    InitTensorEngine<cpu>();
    Shape<2> shape = Shape2(2, 5);
    Stream<cpu>* stream = NewStream<cpu>(0);
    Tensor<cpu, 2, float> tensor1 = NewTensor<cpu, float, 2>(shape, 0.0f);
    Tensor<cpu, 2, float> tensor2 = NewTensor<cpu, float, 2>(shape, 5.5f);
    assign_tensor(tensor1);
    assign_tensor(tensor2);

    tensor1 += 10.0f;
    tensor2 = (tensor1 + 2.0f) / 10.0f + 1.0f;
    print_tensor<2>(tensor1);
    print_tensor<2>(tensor2);

    // the calculation happen in '=' stage, the dst must allocate before, so '='
    // can trigger the calculation.
    Tensor<cpu, 2, float>  ele_add_dst = NewTensor<cpu, float, 2>(shape, 0.0f);
    Tensor<cpu, 2, float>  ele_add_dst2 = NewTensor<cpu, float, 2>(shape, 0.0f);
    Tensor<cpu, 2, float>  ele_minus_dst = NewTensor<cpu, float, 2>(shape, 0.0f);

    ele_add_dst = tensor1 + tensor2;
    ele_add_dst2 = expr::F<op::plus>(tensor1, tensor2);
    ele_minus_dst = expr::F<op::minus>(tensor1, tensor2);
    print_tensor<2>(ele_add_dst);
    print_tensor<2>(ele_add_dst2);
    print_tensor<2>(ele_minus_dst);

    float max_dst, sum_dst;
    Tensor<cpu, 1, float> tensor1TO1D = tensor1.FlatTo1D();
    Tensor<cpu, 1, float> tensor2To1D = tensor2.FlatTo1D();
    for (int i=0; i< tensor1TO1D.shape_.Size(); i++) {
        printf("i:%d, data:%.2f\n", i, tensor1TO1D[i]);
        red::sum::Reduce(sum_dst, tensor1TO1D[i]);
    }
    for (int i=0; i < tensor1TO1D.shape_.Size(); i++) {
        red::maximum::Reduce(max_dst, tensor1TO1D[i]);
    }
    printf("sum(tensor1): %.2f, max(tensor1): %.2f\n", sum_dst, max_dst);

    max_dst = sum_dst = 0;
    for (int i=0; i<tensor1.size(0); i++) {
        for (int j=0; j< tensor1.size(1); j++) {
            printf("[%d,%d]:%.2f\n", i, j, tensor1[i][j]);
            red::sum::Reduce(sum_dst, tensor1[i][j]);
        }
    }
    for (int i=0; i<tensor1.size(0); i++) {
        for (int j=0; j< tensor1.size(1); j++) {
            red::maximum::Reduce(max_dst, tensor1[i][j]);
        }
    }
    printf("sum(tensor1): %.2f, max(tensor1): %.2f\n", sum_dst, max_dst);

    FreeSpace(&tensor1);
    FreeSpace(&tensor2);
    FreeSpace(&ele_add_dst);
    FreeSpace(&ele_add_dst2);
    FreeSpace(&ele_minus_dst);
    ShutdownTensorEngine<cpu>();
    return 0;
}