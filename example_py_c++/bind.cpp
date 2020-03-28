/*
<%
setup_pybind11(cfg)
%>
*/
#include <chrono>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <unordered_map>

namespace py = pybind11;

template <typename T> void add_scalar(py::array_t<T> arr, T scalar) {
  // mutable_unchecked: convert arr to fixed rank mutable tensor
  // here we assume arr is 2d array
  auto arr_rw = arr.template mutable_unchecked<2>();
  auto arr_ptr = arr.mutable_data();
  auto d0 = arr_rw.shape(0);
  auto d1 = arr_rw.shape(1);
  for (int i = 0; i < d0; ++i) {
    for (int j = 0; j < d1; ++j) {
      // 1. directly modify by array index
      arr_rw(i, j) += scalar;
      // 2. get ref
      T &elem = arr_rw(i, j);
      elem += scalar;
      // 3. use data ptr
      arr_ptr[i * d1 + j] += scalar;
    }
  }
}

PYBIND11_MODULE(bind, m) {
  m.def("add_scalar_fp32", &add_scalar<float>);
  m.def("add_scalar_int32_nogil", &add_scalar<int>,
        py::call_guard<py::gil_scoped_release>());
}
