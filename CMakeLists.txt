cmake_minimum_required (VERSION 2.8)
project (CPPBench CXX)

enable_testing()

add_subdirectory("${PROJECT_SOURCE_DIR}/lib/fastcgi++")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/cmake-tests")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/fastcgipp-tests")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/string-tests")
