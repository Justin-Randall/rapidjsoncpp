# Copyright (c) 2020 Justin Randall / Playscale PTE LTD
# Released under the MIT license. See LICENSE included with this
# source package for details.

cmake_minimum_required(VERSION 3.19)
configure_file(CMakeLists.txt.in googletest-download/CmakeLists.txt)

set(GTEST_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/googletest-build")

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

add_executable(jsoncpp_tests 
  "test_json_pod.cpp" 
  "test_json_vector.cpp" 
  "test_json_map.cpp"
  "test_json_unordered_map.cpp"
  "test_json_set.cpp"
  "test_struct.cpp")

target_compile_features(jsoncpp_tests PRIVATE cxx_std_17)

target_link_libraries(jsoncpp_tests PRIVATE gtest_main)

add_test(NAME test_jsoncpp COMMAND "opencppcoverage jsoncpp_tests")

include_directories("${gtest_SOURCE_DIR}/include"
    "${rapidjsoncpp_SOURCE_DIR}/include/rapidjsoncpp/*.hpp"
    "${rapidjsoncpp_SOURCE_DIR}/include"
)
