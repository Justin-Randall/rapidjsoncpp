# Copyright (c) 2020 Justin Randall / Playscale PTE LTD
# Released under the MIT license. See LICENSE included with this
# source package for details.

cmake_minimum_required(VERSION 3.11)

if(NOT DEFINED JSONCPP_DISABLE_TESTING)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG origin/main
  )
  FetchContent_MakeAvailable(googletest)

  add_executable(jsoncpp_tests
    "test_json_pod.cpp"
    "test_json_vector.cpp"
    "test_json_map.cpp"
    "test_json_unordered_map.cpp"
    "test_json_set.cpp"
    "test_struct.cpp"
    "test_json_pair.cpp"
  )

  target_compile_features(jsoncpp_tests PRIVATE cxx_std_17)

  target_link_libraries(jsoncpp_tests PRIVATE gtest_main)

  set(UNIT_TEST jsoncpp_tests)
  add_test(NAME ${UNIT_TEST} COMMAND jsoncpp_tests)

  include_directories("${gtest_SOURCE_DIR}/include")

  find_program(OpenCppCoverage_BINARY OpenCppCoverage.exe)

  set(TEST_COMMAND_LINE_OPTIONS ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> -R "^${UNIT_TEST}$" --output-on-failures)

  if(OpenCppCoverage_BINARY)
    add_custom_command(
      TARGET ${UNIT_TEST}
      COMMENT "Run coverage report"
      POST_BUILD
      WORKING_DIRECTORY ${CMAKE_TEST_DIRECTORY}
      COMMAND ${OpenCppCoverage_BINARY} --quiet --export_type cobertura:${CMAKE_SOURCE_DIR}/build/coverage.xml --cover_children --sources rapidjsoncpp --excluded_modules system32 --excluded_sources build -- ${TEST_COMMAND_LINE_OPTIONS}
    )
  else()
    add_custom_command(
      TARGET ${UNIT_TEST}
      COMMENT "Run tests"
      POST_BUILD
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
      COMMAND ${TEST_COMMAND_LINE_OPTIONS}
    )
  endif()
endif()
