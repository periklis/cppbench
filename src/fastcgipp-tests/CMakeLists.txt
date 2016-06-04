cmake_minimum_required (VERSION 2.8)
project (Fastcgipp_tests CXX)

# Set compile flags for gcc and clang
if(UNIX)
  set(CMAKE_CXX_FLAGS
    "$ENV{CXXFLAGS} -std=c++14 -Wall -Werror -pthread")
  set(CMAKE_CXX_FLAGS_RELEASE
    "$ENV{CXXFLAGS} -O3 -fomit-frame-pointer -std=c++14 -Wall -Werror -pthread")
  set(CMAKE_CXX_FLAGS_DEBUG
    "$ENV{CXXFLAGS} -Og -fno-omit-frame-pointer -g -ggdb -std=c++14 -Wall -Werror -pthread")
endif()

include_directories(
  "${CMAKE_CURRENT_BINARY_DIR}/../../lib/fastcgi++/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/fastcgi++/include")

add_executable(hellofcgipp.fcgi hellofcgipp.cpp)
add_dependencies(hellofcgipp.fcgi fastcgipp)
target_link_libraries(hellofcgipp.fcgi PRIVATE fastcgipp)

install(FILES hellofcgipp.fcgi
  PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE
  DESTINATION "${PROJECT_SOURCE_DIR}/../../bin")
