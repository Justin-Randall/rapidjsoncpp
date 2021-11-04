# Copyright (c) 2020 Justin Randall / Playscale PTE LTD
# Released under the MIT license. See LICENSE included with this
# source package for details.

cmake_minimum_required(VERSION 3.9)

project(rapidjsoncpp VERSION 0.0.1 LANGUAGES CXX)
include(CTest)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(RAPIDJSON_BUILD_TESTS false)

include(FetchContent)
FetchContent_Declare(
    rapidjson
    GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
    GIT_TAG        origin/master
)
FetchContent_MakeAvailable(rapidjson)

enable_testing()

add_subdirectory(tests)
set(RAPIDJSON_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
