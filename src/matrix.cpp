#include "matrix.h"

#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

namespace matrix_calc {
namespace {

constexpr int kMaxRowsToShow = 10;
constexpr int kMaxColsToShow = 8;
constexpr int kColumnWidth = 9;

void validate_matrix(const Matrix& matrix, const char* name) {
    if (matrix.data == nullptr || matrix.rows <= 0 || matrix.cols <= 0) {
        throw std::invalid_argument(std::string(name) + " must be a non-empty matrix");
    }
}

}  // namespace

Matrix create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive");
    }

    Matrix matrix;
    matrix.rows = rows;
    matrix.cols = cols;

    try {
        matrix.data = new double*[static_cast<std::size_t>(rows)]{};
        for (int i = 0; i < rows; ++i) {
            matrix.data[i] = new double[static_cast<std::size_t>(cols)]{};
        }
    } catch (...) {
        if (matrix.data != nullptr) {
            for (int i = 0; i < rows; ++i) {
                delete[] matrix.data[i];
            }
            delete[] matrix.data;
        }
        throw;
    }

    return matrix;
}

void free_matrix(Matrix& matrix) noexcept {
    if (matrix.data != nullptr) {
        for (int i = 0; i < matrix.rows; ++i) {
            delete[] matrix.data[i];
        }
        delete[] matrix.data;
    }
    matrix = Matrix{};
}

Matrix matrix_add(const Matrix& a, const Matrix& b) {
    validate_matrix(a, "a");
    validate_matrix(b, "b");
    if (a.rows != b.rows || a.cols != b.cols) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }

    Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; ++i) {
        for (int j = 0; j < a.cols; ++j) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return result;
}

Matrix matrix_multiply(const Matrix& a, const Matrix& b) {
    validate_matrix(a, "a");
    validate_matrix(b, "b");
    if (a.cols != b.rows) {
        throw std::invalid_argument("Matrix dimensions are incompatible for multiplication");
    }

    Matrix result = create_matrix(a.rows, b.cols);
    for (int i = 0; i < a.rows; ++i) {
        for (int k = 0; k < a.cols; ++k) {
            const double value = a.data[i][k];
            for (int j = 0; j < b.cols; ++j) {
                result.data[i][j] += value * b.data[k][j];
            }
        }
    }
    return result;
}

Matrix matrix_from_array(const double* data, int rows, int cols) {
    if (data == nullptr) {
        throw std::invalid_argument("Source array must not be null");
    }

    Matrix result = create_matrix(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i * cols + j];
        }
    }
    return result;
}

void print_matrix(const Matrix& matrix) {
    if (matrix.data == nullptr || matrix.rows <= 0 || matrix.cols <= 0) {
        std::cout << "[Empty matrix]\n";
        return;
    }

    const std::ios::fmtflags old_flags = std::cout.flags();
    const std::streamsize old_precision = std::cout.precision();
    std::cout << std::fixed << std::setprecision(2);

    const bool rows_hidden = matrix.rows > kMaxRowsToShow;
    const bool cols_hidden = matrix.cols > kMaxColsToShow;
    const int rows_to_show = std::min(matrix.rows, kMaxRowsToShow);
    const int cols_to_show = std::min(matrix.cols, kMaxColsToShow);

    for (int i = 0; i < rows_to_show; ++i) {
        std::cout << '[';
        for (int j = 0; j < cols_to_show; ++j) {
            if (j > 0) {
                std::cout << ' ';
            }
            std::cout << std::setw(kColumnWidth) << matrix.data[i][j];
        }
        if (cols_hidden) {
            std::cout << " ...";
        }
        std::cout << "]\n";
    }

    if (rows_hidden) {
        std::cout << "[...]\n";
    }
    if (rows_hidden || cols_hidden) {
        std::cout << "Matrix " << matrix.rows << "x" << matrix.cols << " (showing first "
                  << rows_to_show << "x" << cols_to_show << ")\n";
    }

    std::cout.flags(old_flags);
    std::cout.precision(old_precision);
}

}  // namespace matrix_calc
