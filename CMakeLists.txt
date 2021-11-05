# Copyright (c) 2020 Justin Randall / Playscale PTE LTD
# Released under the MIT license. See LICENSE included with this
# source package for details.

cmake_minimum_required(VERSION 3.9)

project(rapidjsoncpp VERSION 0.0.1 LANGUAGES CXX)
include(CTest)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
option(RAPIDJSON_BUILD_THIRDPARTY_GTEST OFF)
option(RAPIDJSON_BUILD_TESTS OFF)
option(RAPIDJSON_BUILD_EXAMPLES OFF)

include(FetchContent)
FetchContent_Declare(
    rapidjson
    GIT_REPOSITORY https://github.com/Justin-Randall/rapidjson.git
    GIT_TAG        origin/master
)
FetchContent_MakeAvailable(rapidjson)

add_library(rapidjsoncpp INTERFACE)
target_include_directories(
    rapidjsoncpp 
    INTERFACE 
    "${rapidjson_SOURCE_DIR}/include"
    "${rapidjsoncpp_SOURCE_DIR}/include"
)

include_directories("${rapidjson_SOURCE_DIR}/include"
"${rapidjsoncpp_SOURCE_DIR}/include"
)

enable_testing()

add_subdirectory(tests)
set(RAPIDJSON_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
