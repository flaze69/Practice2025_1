#include <pybind11/pybind11.h>

int apply_filter_cpp(int x) {
    return x * 2; // Приклад, замініть на вашу логіку
}

PYBIND11_MODULE(filter, m) {
    m.doc() = "Example module";
    m.def("apply_filter_cpp", &apply_filter_cpp, "Apply filter to input");
}