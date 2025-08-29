add_executable(stress_test stress_test.cpp)

target_include_directories(stress_test PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)