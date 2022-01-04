# SPDX-License-Identifier:	MPL-2.0

set(CURRENT_TARGET_BINPATH ${CMAKE_BINARY_PATH}/test)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/archdeps OPUSARIUM_TEST_ARCHDEPS)

add_executable(opusarium_test ${OPUSARIUM_TEST_ARCHDEPS} opusarium_test.c)
set_target_properties(${CURRENT_TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CURRENT_TARGET_BINPATH})