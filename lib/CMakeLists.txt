cmake_minimum_required (VERSION 3.2 FATAL_ERROR)
project (LibDependencies LANGUAGES CXX)

foreach(libdep googletest)
  # Download and unpack googletest at configure time
  configure_file(${libdep}/CMakeLists.txt.in ${libdep}/CMakeLists.txt)

  if(${libdep} STREQUAL "boost")
    configure_file(${libdep}/user-config.jam.in ${CMAKE_CURRENT_BINARY_DIR}/${libdep}/src/tools/build/src/user-config.jam)
  endif(${libdep} STREQUAL "boost")

  message(${CMAKE_BINARY_DIR})
  execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${libdep})
  if(result)
    message(FATAL_ERROR "CMake step for ${libdep} failed: ${result}")
  endif()
  execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${libdep})
  if(result)
    message(FATAL_ERROR "Build step for ${libdep} failed: ${result}")
  endif()
endforeach(libdep)

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(
  ${CMAKE_CURRENT_BINARY_DIR}/googletest/src
  ${CMAKE_CURRENT_BINARY_DIR}/googletest/build)
