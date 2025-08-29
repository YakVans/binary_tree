add_executable(tests_runner tests_runner.cpp)

target_include_directories(tests_runner PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/doctest
    ${CMAKE_CURRENT_SOURCE_DIR}
)