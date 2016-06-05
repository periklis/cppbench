cmake_minimum_required (VERSION 2.8)
project (string-tests CXX)

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

add_executable(string-tests-main main.cpp String.cpp)

enable_testing()
add_executable(string-tests-tests tests/test_cstring.cpp String.cpp)
add_test("StringTests::Tests" string-tests-tests COMMANDS string-tests-tests --build_info=1 --color_output=1 --report_level=detailed)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/string-tests-main"
  PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE
  DESTINATION "${PROJECT_SOURCE_DIR}/../../bin")
