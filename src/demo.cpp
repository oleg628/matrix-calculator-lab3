#include "demo.h"

#include <iostream>

#include "matrix.h"

namespace matrix_calc {
namespace {

void print_title(const char* title) {
    std::cout << "\n=== " << title << " ===\n";
}

}  // namespace

void run_base_demo() {
    print_title("Матричный калькулятор: базовые операции");

    const double a_values[] = {1.0, 2.0, 3.0, 4.0};
    const double b_values[] = {5.0, 6.0, 7.0, 8.0};
    Matrix a = matrix_from_array(a_values, 2, 2);
    Matrix b = matrix_from_array(b_values, 2, 2);

    std::cout << "Матрица A:\n";
    print_matrix(a);
    std::cout << "Матрица B:\n";
    print_matrix(b);

    Matrix sum = matrix_add(a, b);
    std::cout << "A + B:\n";
    print_matrix(sum);

    Matrix product = matrix_multiply(a, b);
    std::cout << "A * B:\n";
    print_matrix(product);

    free_matrix(product);
    free_matrix(sum);
    free_matrix(b);
    free_matrix(a);
}

void run_variant25_demo() {
    print_title("Вариант 25: матрица из одномерного массива");

    double values[] = {1.5, 2.5, 3.5, 4.5, 5.5, 6.5};
    Matrix matrix = matrix_from_array(values, 2, 3);

    std::cout << "Исходный массив: 1.5 2.5 3.5 4.5 5.5 6.5\n";
    std::cout << "Матрица 2x3 (заполнение построчно):\n";
    print_matrix(matrix);

    values[0] = 99.0;
    std::cout << "После изменения values[0] элемент matrix[0][0] = " << matrix.data[0][0] << '\n';

    free_matrix(matrix);
}

}  // namespace matrix_calc
