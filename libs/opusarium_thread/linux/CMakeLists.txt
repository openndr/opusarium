# SPDX-License-Identifier:	MPL-2.0

target_include_directories(opusarium_thread PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_sources(opusarium_thread PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/opusarium_linux_thread.c")
