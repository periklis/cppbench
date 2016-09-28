cmake_minimum_required (VERSION 2.8)
project (string-tests LANGUAGES CXX)

# Set compile flags for gcc and clang
if(UNIX)
  set(CMAKE_CXX_FLAGS
    "$ENV{CXXFLAGS} -std=c++14")
  set(CMAKE_CXX_FLAGS_RELEASE
    "$ENV{CXXFLAGS} -O3 -fomit-frame-pointer -std=c++14")
  set(CMAKE_CXX_FLAGS_DEBUG
    "$ENV{CXXFLAGS} -Og -fno-omit-frame-pointer -g -ggdb -std=c++14")
endif()

include_directories(
  "${CMAKE_CURRENT_BINARY_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}")


add_executable(assertions assertions.cpp)
add_executable(class_types class_types.cpp)
add_executable(compile_time_polymorphism compile_time_polymorphism.cpp)
add_executable(copy_semantics copy_semantics.cpp)
add_executable(exception_quarantees exception_quarantees.cpp)
add_executable(init_procedures init_procedures.cpp)
add_executable(move_semantics move_semantics.cpp)
add_executable(operators operators.cpp)
add_executable(runtime_polymorphism runtime_polymorphism.cpp)
add_executable(special_member_functions special_member_functions.cpp)
#add_executable(type_traits type_traits.cpp)

#install(FILES "${CMAKE_CURRENT_BINARY_DIR}/"
#  PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE
#  DESTINATION "${PROJECT_SOURCE_DIR}/../../bin")
