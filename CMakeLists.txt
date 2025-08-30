cmake_minimum_required(VERSION 3.10)
project(lab_4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(tests)
add_subdirectory(stress_test)

add_executable(main main.cpp)

target_include_directories(main PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/complex_numbers
    ${CMAKE_SOURCE_DIR}/UI
)