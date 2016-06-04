cmake_minimum_required (VERSION 2.8)
project (CPPBench CXX)

add_subdirectory("${PROJECT_SOURCE_DIR}/lib/fastcgi++")

# include_directories("$PROJECT_SOURCE_DIR/lib/fastcgi++/include")

add_subdirectory("${PROJECT_SOURCE_DIR}/src/cmake_test")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/fastcgipp-tests")
