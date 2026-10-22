#include <exception>
#include <iostream>

#include "demo.h"

int main() {
    try {
        matrix_calc::run_base_demo();
    } catch (const std::exception& error) {
        std::cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
