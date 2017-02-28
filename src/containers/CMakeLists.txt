cmake_minimum_required (VERSION 3.2 FATAL_ERROR)
project (containers LANGUAGES CXX)

#
# Container Tests
#
add_executable(vector_construct_test vector_construct_test.cpp)
set_target_properties(vector_construct_test PROPERTIES
  CXX_STANDARD 14)
target_compile_options(vector_construct_test
  PUBLIC -Wall -Werror)
target_link_libraries(vector_construct_test PRIVATE gtest_main)
add_test(NAME vector_construct_test COMMAND vector_construct_test)


add_executable(vector_invariants_test vector_invariants_test.cpp)
set_target_properties(vector_invariants_test PROPERTIES
  CXX_STANDARD 14)
target_compile_options(vector_invariants_test
  PUBLIC -Wall -Werror)
target_link_libraries(vector_invariants_test PRIVATE gtest_main)
add_test(NAME vector_invariants_test COMMAND vector_invariants_test)


add_executable(vector_mutate_test vector_mutate_test.cpp)
set_target_properties(vector_mutate_test PROPERTIES
  CXX_STANDARD 14)
target_compile_options(vector_mutate_test
  PUBLIC -Wall -Werror)
target_link_libraries(vector_mutate_test PRIVATE gtest_main)
add_test(NAME vector_mutate_test COMMAND vector_mutate_test)


add_executable(vector_operators_test vector_operators_test.cpp)
set_target_properties(vector_operators_test PROPERTIES
  CXX_STANDARD 14)
target_compile_options(vector_operators_test
  PUBLIC -Wall -Werror)
target_link_libraries(vector_operators_test PRIVATE gtest_main)
add_test(NAME vector_operators_test COMMAND vector_operators_test)
