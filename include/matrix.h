#pragma once

/**
 * @file matrix.h
 * @brief Публичный интерфейс библиотеки для работы с матрицами.
 * @author Алексей Стегунов
 * @version 1.0.0
 */

namespace matrix_calc {

/**
 * @brief Матрица, хранящая двумерный динамический массив.
 *
 * Элементы расположены построчно: data[i][j] соответствует i-й строке
 * и j-му столбцу. Память выделяется функцией create_matrix() или
 * matrix_from_array() и освобождается функцией free_matrix().
 *
 * @warning Копирование структуры создаёт поверхностную копию указателя.
 *          Владелец матрицы должен быть один.
 */
struct Matrix {
    double** data = nullptr;  ///< Указатель на массив строк.
    int rows = 0;             ///< Количество строк.
    int cols = 0;             ///< Количество столбцов.
};

/**
 * @brief Создаёт матрицу заданного размера, заполненную нулями.
 *
 * @param rows Количество строк, должно быть больше нуля.
 * @param cols Количество столбцов, должно быть больше нуля.
 * @return Новая матрица размера rows x cols.
 *
 * @exception std::invalid_argument Если rows <= 0 или cols <= 0.
 * @exception std::bad_alloc Если не удалось выделить память.
 *
 * @note Время выполнения O(rows * cols), память O(rows * cols).
 * @see free_matrix()
 *
 * @code
 * Matrix a = create_matrix(2, 2);
 * free_matrix(a);
 * @endcode
 */
Matrix create_matrix(int rows, int cols);

/**
 * @brief Освобождает память матрицы и переводит её в пустое состояние.
 *
 * @param[in,out] matrix Матрица, память которой нужно освободить.
 *
 * @note Принимает ссылку, чтобы обнулить указатель у вызывающего кода и
 *       исключить повторное освобождение. Повторный вызов безопасен.
 * @see create_matrix()
 */
void free_matrix(Matrix& matrix) noexcept;

/**
 * @brief Вычисляет сумму двух матриц одинакового размера.
 *
 * @param a Первая матрица.
 * @param b Вторая матрица.
 * @return Новая матрица с элементами a[i][j] + b[i][j].
 *
 * @exception std::invalid_argument Если матрица пуста или размеры не совпадают.
 * @exception std::bad_alloc Если не удалось выделить память результата.
 *
 * @note Время выполнения O(rows * cols).
 * @warning Результат нужно освободить через free_matrix().
 */
Matrix matrix_add(const Matrix& a, const Matrix& b);

/**
 * @brief Умножает две матрицы.
 *
 * @param a Матрица размера M x N.
 * @param b Матрица размера N x K.
 * @return Новая матрица размера M x K.
 *
 * @exception std::invalid_argument Если матрица пуста или a.cols != b.rows.
 * @exception std::bad_alloc Если не удалось выделить память результата.
 *
 * @note Время выполнения O(M * N * K), память O(M * K).
 * @warning Результат нужно освободить через free_matrix().
 */
Matrix matrix_multiply(const Matrix& a, const Matrix& b);

/**
 * @brief Создаёт матрицу из одномерного массива (вариант 25).
 *
 * Данные копируются построчно: первые cols элементов образуют первую
 * строку, следующие cols элементов — вторую и так далее. Исходный массив
 * не изменяется и может быть освобождён сразу после вызова.
 *
 * @param data Указатель на массив из rows * cols элементов.
 * @param rows Количество строк, должно быть больше нуля.
 * @param cols Количество столбцов, должно быть больше нуля.
 * @return Новая матрица с копией данных.
 *
 * @exception std::invalid_argument Если data == nullptr, rows <= 0 или cols <= 0.
 * @exception std::bad_alloc Если не удалось выделить память.
 *
 * @note Время выполнения O(rows * cols).
 * @see create_matrix()
 *
 * @code
 * double values[] = {1.0, 2.0, 3.0, 4.0};
 * Matrix m = matrix_from_array(values, 2, 2);
 * free_matrix(m);
 * @endcode
 */
Matrix matrix_from_array(const double* data, int rows, int cols);

/**
 * @brief Выводит матрицу в стандартный поток вывода.
 *
 * Для больших матриц (больше 10 строк или 8 столбцов) печатаются только
 * первые строки и столбцы, после чего указывается фактический размер.
 * Формат чисел — fixed с двумя знаками после запятой.
 *
 * @param matrix Матрица для вывода; пустая матрица выводится как [Empty matrix].
 *
 * @note Состояние форматирования std::cout восстанавливается после вывода.
 */
void print_matrix(const Matrix& matrix);

}  // namespace matrix_calc
