# SPDX-License-Identifier:	MPL-2.0

cmake_minimum_required(VERSION 3.2.0)
project(opusarium)

include(${CMAKE_CURRENT_SOURCE_DIR}/mktools/OpusariumLanguageDetection.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/mktools/OpusariumEnvironmentDetection.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/mktools/OpusariumCompilerDetection.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/mktools/OpusariumArchitectureDetection.cmake)

if(${OPUSARIUM_CMAKE_COMPILER_NAME} STREQUAL "msvc")
    add_compile_options("/W3" "/WX")
else()
    add_compile_options("-Wall" "-Wextra" "-Werror")
endif()

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE OPUSARIUM_CMAKE_SUBMODULE_RESULT)

        if(NOT OPUSARIUM_CMAKE_SUBMODULE_RESULT EQUAL "0")
            message(FATAL_ERROR "Failed submodule synchronization: ${OPUSARIUM_CMAKE_SUBMODULE_RESULT}")
        else()
            message(STATUS "Opusarium submodule updated")
        endif()
    endif()
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/extmods/utest.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/compdeps)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/archdeps)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)