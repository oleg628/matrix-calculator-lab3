cmake_minimum_required(VERSION 3.20)

project(MatrixCalculator VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(matrix_lib STATIC src/matrix.cpp)
target_include_directories(matrix_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(matrix_calculator src/main.cpp src/demo.cpp)
target_link_libraries(matrix_calculator PRIVATE matrix_lib)

function(matrix_enable_warnings target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /WX)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
endfunction()

matrix_enable_warnings(matrix_lib)
matrix_enable_warnings(matrix_calculator)
