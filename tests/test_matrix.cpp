#include <gtest/gtest.h>

#include <initializer_list>
#include <stdexcept>

#include "matrix.h"

namespace {

matrix_calc::Matrix make_matrix(std::initializer_list<std::initializer_list<double>> rows) {
    const int row_count = static_cast<int>(rows.size());
    const int col_count = static_cast<int>(rows.begin()->size());
    matrix_calc::Matrix matrix = matrix_calc::create_matrix(row_count, col_count);

    int i = 0;
    for (const auto& row : rows) {
        int j = 0;
        for (const double value : row) {
            matrix.data[i][j] = value;
            ++j;
        }
        ++i;
    }
    return matrix;
}

}  // namespace

TEST(MatrixTest, CreateMatrixInitializesZeros) {
    matrix_calc::Matrix matrix = matrix_calc::create_matrix(3, 4);

    EXPECT_EQ(matrix.rows, 3);
    EXPECT_EQ(matrix.cols, 4);
    ASSERT_NE(matrix.data, nullptr);
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j) {
            EXPECT_DOUBLE_EQ(matrix.data[i][j], 0.0);
        }
    }

    matrix_calc::free_matrix(matrix);
}

TEST(MatrixTest, AddMatrices) {
    matrix_calc::Matrix a = make_matrix({{1.0, 2.0}, {3.0, 4.0}});
    matrix_calc::Matrix b = make_matrix({{5.0, 6.0}, {7.0, 8.0}});

    matrix_calc::Matrix sum = matrix_calc::matrix_add(a, b);

    EXPECT_EQ(sum.rows, 2);
    EXPECT_EQ(sum.cols, 2);
    EXPECT_DOUBLE_EQ(sum.data[0][0], 6.0);
    EXPECT_DOUBLE_EQ(sum.data[0][1], 8.0);
    EXPECT_DOUBLE_EQ(sum.data[1][0], 10.0);
    EXPECT_DOUBLE_EQ(sum.data[1][1], 12.0);

    matrix_calc::free_matrix(sum);
    matrix_calc::free_matrix(b);
    matrix_calc::free_matrix(a);
}

TEST(MatrixTest, MultiplyMatrices) {
    matrix_calc::Matrix a = make_matrix({{1.0, 2.0}, {3.0, 4.0}});
    matrix_calc::Matrix b = make_matrix({{5.0, 6.0}, {7.0, 8.0}});

    matrix_calc::Matrix product = matrix_calc::matrix_multiply(a, b);

    EXPECT_EQ(product.rows, 2);
    EXPECT_EQ(product.cols, 2);
    EXPECT_DOUBLE_EQ(product.data[0][0], 19.0);
    EXPECT_DOUBLE_EQ(product.data[0][1], 22.0);
    EXPECT_DOUBLE_EQ(product.data[1][0], 43.0);
    EXPECT_DOUBLE_EQ(product.data[1][1], 50.0);

    matrix_calc::free_matrix(product);
    matrix_calc::free_matrix(b);
    matrix_calc::free_matrix(a);
}

TEST(MatrixTest, MultiplyRowByColumn) {
    matrix_calc::Matrix row = make_matrix({{1.0, 2.0, 3.0}});
    matrix_calc::Matrix column = make_matrix({{4.0}, {5.0}, {6.0}});

    matrix_calc::Matrix product = matrix_calc::matrix_multiply(row, column);

    EXPECT_EQ(product.rows, 1);
    EXPECT_EQ(product.cols, 1);
    EXPECT_DOUBLE_EQ(product.data[0][0], 32.0);

    matrix_calc::free_matrix(product);
    matrix_calc::free_matrix(column);
    matrix_calc::free_matrix(row);
}

TEST(MatrixTest, FromArrayCopiesRowMajorValues) {
    double values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    matrix_calc::Matrix matrix = matrix_calc::matrix_from_array(values, 2, 3);

    EXPECT_EQ(matrix.rows, 2);
    EXPECT_EQ(matrix.cols, 3);
    EXPECT_DOUBLE_EQ(matrix.data[0][0], 1.0);
    EXPECT_DOUBLE_EQ(matrix.data[0][2], 3.0);
    EXPECT_DOUBLE_EQ(matrix.data[1][0], 4.0);
    EXPECT_DOUBLE_EQ(matrix.data[1][2], 6.0);

    values[0] = 99.0;
    EXPECT_DOUBLE_EQ(matrix.data[0][0], 1.0);

    matrix_calc::free_matrix(matrix);
}

TEST(MatrixTest, FromArrayAcceptsSingleElement) {
    const double values[] = {42.5};
    matrix_calc::Matrix matrix = matrix_calc::matrix_from_array(values, 1, 1);

    EXPECT_EQ(matrix.rows, 1);
    EXPECT_EQ(matrix.cols, 1);
    EXPECT_DOUBLE_EQ(matrix.data[0][0], 42.5);

    matrix_calc::free_matrix(matrix);
}

TEST(MatrixTest, CreateMatrixRejectsInvalidDimensions) {
    EXPECT_THROW(matrix_calc::create_matrix(0, 3), std::invalid_argument);
    EXPECT_THROW(matrix_calc::create_matrix(3, -1), std::invalid_argument);
}

TEST(MatrixTest, FromArrayRejectsNullPointer) {
    EXPECT_THROW(matrix_calc::matrix_from_array(nullptr, 2, 2), std::invalid_argument);
}

TEST(MatrixTest, AddRejectsSizeMismatch) {
    matrix_calc::Matrix a = matrix_calc::create_matrix(2, 2);
    matrix_calc::Matrix b = matrix_calc::create_matrix(3, 3);

    EXPECT_THROW(matrix_calc::matrix_add(a, b), std::invalid_argument);

    matrix_calc::free_matrix(b);
    matrix_calc::free_matrix(a);
}

TEST(MatrixTest, MultiplyRejectsSizeMismatch) {
    matrix_calc::Matrix a = matrix_calc::create_matrix(2, 3);
    matrix_calc::Matrix b = matrix_calc::create_matrix(2, 2);

    EXPECT_THROW(matrix_calc::matrix_multiply(a, b), std::invalid_argument);

    matrix_calc::free_matrix(b);
    matrix_calc::free_matrix(a);
}

TEST(MatrixTest, FreeMatrixIsIdempotent) {
    matrix_calc::Matrix matrix{};

    EXPECT_NO_THROW(matrix_calc::free_matrix(matrix));
    EXPECT_NO_THROW(matrix_calc::free_matrix(matrix));
    EXPECT_EQ(matrix.data, nullptr);
    EXPECT_EQ(matrix.rows, 0);
    EXPECT_EQ(matrix.cols, 0);
}
