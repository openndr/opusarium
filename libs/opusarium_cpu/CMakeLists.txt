# SPDX-License-Identifier:	MPL-2.0

add_library(opusarium_cpu STATIC "")
target_include_directories(opusarium_cpu PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

if(${OPUSARIUM_CMAKE_ENVIRONMENT_NAME} STREQUAL "linux")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/linux)
else()
    message(FATAL_ERROR "Unsupported environment: ${OPUSARIUM_CMAKE_ENVIRONMENT_NAME}")
endif()
