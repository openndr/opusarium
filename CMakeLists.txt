# SPDX-License-Identifier:	MPL-2.0

cmake_minimum_required(VERSION 3.2.0)
project(opusarium)

include(${CMAKE_CURRENT_SOURCE_DIR}/mktools/OpusariumLanguageDetection.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/mktools/OpusariumCompilerDetection.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/mktools/OpusariumArchitectureDetection.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/mktools/OpusariumEnvironmentDetection.cmake)

include_directories(compdeps)
include_directories(archdeps)

add_subdirectory(libs)
