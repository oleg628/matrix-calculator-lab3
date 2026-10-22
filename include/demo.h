#pragma once

/**
 * @file demo.h
 * @brief Демонстрационные сценарии матричного калькулятора.
 * @author Алексей Стегунов
 */

namespace matrix_calc {

/**
 * @brief Показывает базовые операции: сложение и умножение матриц.
 *
 * @exception std::invalid_argument При некорректных размерах матриц.
 * @exception std::bad_alloc При нехватке памяти.
 */
void run_base_demo();

/**
 * @brief Показывает вариант 25: создание матрицы из одномерного массива.
 *
 * @exception std::invalid_argument При некорректных входных данных.
 * @exception std::bad_alloc При нехватке памяти.
 */
void run_variant25_demo();

}  // namespace matrix_calc
