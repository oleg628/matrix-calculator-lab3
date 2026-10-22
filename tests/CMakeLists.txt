include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(matrix_tests test_matrix.cpp)
target_link_libraries(matrix_tests PRIVATE matrix_lib GTest::gtest_main)

if(MSVC)
    target_compile_options(matrix_tests PRIVATE /W4 /WX)
else()
    target_compile_options(matrix_tests PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

include(GoogleTest)
gtest_discover_tests(matrix_tests)
