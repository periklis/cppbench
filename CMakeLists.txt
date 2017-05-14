cmake_minimum_required (VERSION 3.2 FATAL_ERROR)
project (CPPBench LANGUAGES CXX)

set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -O0")

enable_testing()

add_subdirectory("${PROJECT_SOURCE_DIR}/lib")

add_subdirectory("${PROJECT_SOURCE_DIR}/src/containers")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/cpp-tests")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/learning")
# add_subdirectory("${PROJECT_SOURCE_DIR}/src/string-tests")
