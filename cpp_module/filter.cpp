#include <pybind11/pybind11.h>
#include <vector>
#include <string>
#include <pybind11/stl.h>
#include <algorithm>

using namespace std;

std::vector<int> apply_filter_cpp(const std::vector<int>& data, int width, int height, const std::string& filter_name) {
    std::vector<int> result(data);

    if (filter_name == "invert") {
        for (size_t i = 0; i < result.size(); i += 4) {
            result[i]     = 255 - result[i];
            result[i + 1] = 255 - result[i + 1];
            result[i + 2] = 255 - result[i + 2];
        }
        return result;
    }

    // 3x3 kernels
    std::vector<std::vector<int>> kernel;
    int divisor = 1;  // normalization factor

    if (filter_name == "blur") {
        kernel = {
            {1, 1, 1},
            {1, 1, 1},
            {1, 1, 1}
        };
        divisor = 9;
    } else if (filter_name == "edge_detect") {
        kernel = {
            { 0,  1, 0},
            { 1, -4, 1},
            { 0,  1, 0}
        };
    } else if (filter_name == "emboss") {
        kernel = {
            {-2, -1, 0},
            {-1,  1, 1},
            { 0,  1, 2}
        };
    } else {
        return result;  // unsupported filter
    }

    // Піксельна обробка
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            int r = 0, g = 0, b = 0;
            int center_idx = (y * width + x) * 4;

            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    int px = x + kx;
                    int py = y + ky;
                    int idx = (py * width + px) * 4;
                    int k = kernel[ky + 1][kx + 1];

                    r += data[idx]     * k;
                    g += data[idx + 1] * k;
                    b += data[idx + 2] * k;
                }
            }

            // Normalize and clamp
            r = std::min(255, std::max(0, r / divisor));
            g = std::min(255, std::max(0, g / divisor));
            b = std::min(255, std::max(0, b / divisor));

            result[center_idx]     = r;
            result[center_idx + 1] = g;
            result[center_idx + 2] = b;
            result[center_idx + 3] = data[center_idx + 3]; // Alpha без змін
        }
    }

    return result;
}

PYBIND11_MODULE(filter, m) {
    m.doc() = "Filter module using pybind11";
    m.def("apply_filter_cpp", &apply_filter_cpp, "Apply image filter");
}
