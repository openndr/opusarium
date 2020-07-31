add_library(opusarium_thread STATIC "")
target_include_directories(opusarium_thread PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

if(${OPUSARIUM_CMAKE_ENVIRONMENT_NAME} STREQUAL "linux")
	add_subdirectory(linux)
else()
	message(FATAL_ERROR "Unsupported environment: ${OPUSARIUM_CMAKE_ENVIRONMENT_NAME}")
endif()
