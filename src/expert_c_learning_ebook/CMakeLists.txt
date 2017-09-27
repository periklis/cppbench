cmake_minimum_required (VERSION 3.2 FATAL_ERROR)
project (learning LANGUAGES C)

add_executable(time_ch time_challenge.c)

set_target_properties(time_ch PROPERTIES
  C_STANDARD 99)

target_compile_options(time_ch
  PUBLIC -Wall -Werror)


add_executable(multi_array_ch multi_array_challenge.c)

set_target_properties(multi_array_ch PROPERTIES
  C_STANDARD 99)

target_compile_options(multi_array_ch
  PUBLIC -Wall -Werror)
