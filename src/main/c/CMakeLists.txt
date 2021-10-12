#------------------------------------------------------------------------------
# Top-level CMake file for java-sdk-jni
# ------------------------------------------------------------------------------
# Copyright (C) 2021 java-sdk-jni
# SPDX-License-Identifier: Apache-2.0
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.18)

project(java-sdk-jni VERSION "3.0.0")

# set(CMAKE_BUILD_TYPE Release)

set(FISCO_BCOS_JNI_TARGET "fisco-bcos-jni")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${CMAKE_INSTALL_INCLUDEDIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# message(STATUS "CMAKE_INSTALL_INCLUDEDIR ==> ${CMAKE_INSTALL_INCLUDEDIR}")
# message(STATUS "CMAKE_CURRENT_SOURCE_DIR ==> ${CMAKE_CURRENT_SOURCE_DIR}")
# message(STATUS "CMAKE_CURRENT_SOURCE_DIR ==> ${CMAKE_CURRENT_SOURCE_DIR}/include")

# find JNI 
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

set(SOURCE_FILES Utilities.cpp)
file(GLOB_RECURSE SOURCES "include/*.h" "src/*.cpp" "src/*.c")

add_library(${FISCO_BCOS_JNI_TARGET} SHARED ${SOURCES})
