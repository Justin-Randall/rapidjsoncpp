# Copyright (c) 2021 Justin Randall / Playscale PTE LTD
# Released under the MIT license. See LICENSE included with this
# source package for details.

cmake_minimum_required(VERSION 3.9)

project(rapidjsoncpp VERSION 0.0.1 LANGUAGES CXX)

add_subdirectory(tests)

set(RAPIDJSON_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
