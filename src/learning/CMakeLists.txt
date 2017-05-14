cmake_minimum_required (VERSION 3.2 FATAL_ERROR)
project (learning LANGUAGES CXX)

add_executable(arrays arrays.cpp)

set_target_properties(arrays PROPERTIES
  CXX_STANDARD 14)

target_compile_options(arrays
  PUBLIC -Wall -Werror)


# add_executable(prim prim.cpp)
# set_target_properties(prim PROPERTIES
#   CXX_STANDARD 14)

# target_compile_options(prim
#   PUBLIC -Wall -Werror)

# add_executable(libcpp libcpp.cpp)
# set_target_properties(libcpp PROPERTIES
#   CXX_STANDARD 14)

# target_include_directories(libcpp
#   PRIVATE "/Users/periklis/.nix-profile/include"
#   PRIVATE "/Users/periklis/.nix-profile/include/c++/v1")

# target_compile_options(libcpp
#   PUBLIC -Wall -Werror)
