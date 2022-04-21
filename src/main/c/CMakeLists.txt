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

cmake_minimum_required(VERSION 3.16)
set(CMAKE_OSX_DEPLOYMENT_TARGET "11.3" CACHE STRING "Minimum OS X deployment version")

# URL_BASE download domain name
include(FetchContent)
if (NOT DEFINED URL_BASE)
    set(URL_BASE "github.com")
    #set(URL_BASE "github.com.cnpmjs.org")
endif()

# download bcos-cmake-scripts
# set(BCOS_CMAKE_SCRIPTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bcos-cmake-scripts)
# FetchContent_Declare(bcos-cmake-scripts
#    GIT_REPOSITORY https://${URL_BASE}/FISCO-BCOS/bcos-cmake-scripts.git
#    GIT_TAG dev
#    SOURCE_DIR ${BCOS_CMAKE_SCRIPTS_DIR}
# )
# FetchContent_MakeAvailable(bcos-cmake-scripts)

set(JAVA_SDK_JNI_CMAKE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake" CACHE PATH "The cmake path for the library")
# list(APPEND CMAKE_MODULE_PATH ${BCOS_CMAKE_SCRIPTS_DIR})
list(APPEND CMAKE_MODULE_PATH ${JAVA_SDK_JNI_CMAKE_DIR})

#init hunter
include(HunterGate)
HunterGate(
    URL "https://${URL_BASE}/FISCO-BCOS/hunter/archive/a97876640bdca736c23a48dc0ad0f168fd3d695c.tar.gz"
    SHA1 "bb6f77268bfa8772ca30d5a4a62dda35840078ad"
    FILEPATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake"
)

# project name
project(bcos-sdk-jni VERSION "3.0.0")
set(VERSION_SUFFIX "-rc4")

# Debug, Release, RelWithDebInfo, MinSizeRel
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories(${CMAKE_INSTALL_INCLUDEDIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# message(STATUS "CMAKE_INSTALL_INCLUDEDIR ==> ${CMAKE_INSTALL_INCLUDEDIR}")
# message(STATUS "CMAKE_CURRENT_SOURCE_DIR ==> ${CMAKE_CURRENT_SOURCE_DIR}")
# message(STATUS "CMAKE_CURRENT_SOURCE_DIR ==> ${CMAKE_CURRENT_SOURCE_DIR}/include")

# find JNI 
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

include(InstallDependencies)

# basic settings
include(Options)
configure_project()
include(CompilerSettings)
include(InstallConfig)
# install the include files for hash
include(InstallInclude)

# source
file(GLOB_RECURSE SOURCES "jni/*.h" "jni/*.cpp" "jni/*.c")

# rust static library linking requirements for macos
if(APPLE)
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -framework Security -framework Foundation")
else()
   set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-as-needed -ldl")
endif()

set(FISCO_BCOS_JNI_TARGET "bcos-sdk-jni")
# add suffix for macOS M1
if(APPLE AND CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "arm64")
    set(FISCO_BCOS_JNI_TARGET "bcos-sdk-jni-aarch64")
endif()

add_library(${FISCO_BCOS_JNI_TARGET} SHARED ${SOURCES})
target_link_libraries(${FISCO_BCOS_JNI_TARGET} PUBLIC wedpr-crypto::crypto wedpr-crypto::extend-crypto bcos-cpp-sdk::bcos-cpp-sdk bcos-c-sdk::bcos-c-sdk-static)

set(FISCO_BCOS_JNI_STATIC_TARGET "bcos-sdk-jni-static")
add_library(${FISCO_BCOS_JNI_STATIC_TARGET} ${SOURCES})
target_link_libraries(${FISCO_BCOS_JNI_STATIC_TARGET} PUBLIC wedpr-crypto::crypto wedpr-crypto::extend-crypto bcos-cpp-sdk::bcos-cpp-sdk bcos-c-sdk::bcos-c-sdk-static)

# ut and binary exe
# if (TESTS)
#    enable_testing()
#    set(CTEST_OUTPUT_ON_FAILURE TRUE)
#    add_subdirectory(test)
# endif()

if (BUILD_EXEC_TEST)
    add_subdirectory(test/exe)
endif()

# SET(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
install(
    TARGETS ${FISCO_BCOS_JNI_TARGET}
    EXPORT "${TARGETS_EXPORT_NAME}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install(
    TARGETS ${FISCO_BCOS_JNI_STATIC_TARGET}
    EXPORT "${TARGETS_EXPORT_NAME}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

