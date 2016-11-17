cmake_minimum_required (VERSION 2.8)
project (CPPBench LANGUAGES CXX)

enable_testing()

add_subdirectory("${PROJECT_SOURCE_DIR}/src/cpp-tests")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/string-tests")
