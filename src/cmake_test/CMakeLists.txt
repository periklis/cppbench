cmake_minimum_required (VERSION 2.8)
project (Cmake_tests CXX)

# Set compile flags for gcc and clang
if(UNIX)
  set(CMAKE_CXX_FLAGS
    "$ENV{CXXFLAGS} -std=c++14 -Wall -Werror -pthread")
  set(CMAKE_CXX_FLAGS_RELEASE
    "$ENV{CXXFLAGS} -O3 -fomit-frame-pointer -std=c++14 -Wall -Werror -pthread")
  set(CMAKE_CXX_FLAGS_DEBUG
    "$ENV{CXXFLAGS} -Og -fno-omit-frame-pointer -g -ggdb -std=c++14 -Wall -Werror -pthread")
endif()

add_executable(cmake_test main.cpp)
install(TARGET cmake_test
  PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE
  DESTINATION "${PROJECT_SOURCE_DIR}/../../bin")
