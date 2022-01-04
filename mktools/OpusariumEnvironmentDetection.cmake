# SPDX-License-Identifier:	MPL-2.0

if(${OPUSARIUM_CMAKE_ENVIRONMENT_INCGUARD})
    return()
endif()
set(OPUSARIUM_CMAKE_ENVIRONMENT_INCGUARD TRUE)

try_run(
    run_result_unused
    compile_result_unused
    "${CMAKE_BINARY_DIR}"
    "${CMAKE_CURRENT_LIST_DIR}/OpusariumEnvironmentDetection.c"
    COMPILE_OUTPUT_VARIABLE OPUSARIUM_CMAKE_ENVIRONMENT_NAME
)
string(REGEX MATCH "OPUSARIUM_TEST_ENVIRONMENT_RESULT ([a-zA-Z0-9_]+)"
    OPUSARIUM_CMAKE_ENVIRONMENT_NAME "${OPUSARIUM_CMAKE_ENVIRONMENT_NAME}")
string(REPLACE "OPUSARIUM_TEST_ENVIRONMENT_RESULT " ""
    OPUSARIUM_CMAKE_ENVIRONMENT_NAME "${OPUSARIUM_CMAKE_ENVIRONMENT_NAME}")
if(NOT OPUSARIUM_CMAKE_ENVIRONMENT_NAME)
    set(OPUSARIUM_CMAKE_ENVIRONMENT_NAME unknown)
endif()

if(${OPUSARIUM_CMAKE_ENVIRONMENT_NAME} STREQUAL "aix")
    if(${CMAKE_VERSION} VERSION_LESS "3.12.0")
        add_definitions(-DOPUSARIUM_TEST_ENVIRONMENT_AIX)
    else()
        add_compile_definitions(OPUSARIUM_TEST_ENVIRONMENT_AIX)
    endif()
elseif(${OPUSARIUM_CMAKE_ENVIRONMENT_NAME} STREQUAL "freebsd")
    if(${CMAKE_VERSION} VERSION_LESS "3.12.0")
        add_definitions(-DOPUSARIUM_TEST_ENVIRONMENT_FREEBSD)
    else()
        add_compile_definitions(OPUSARIUM_TEST_ENVIRONMENT_FREEBSD)
    endif()
elseif(${OPUSARIUM_CMAKE_ENVIRONMENT_NAME} STREQUAL "netbsd")
    if(${CMAKE_VERSION} VERSION_LESS "3.12.0")
        add_definitions(-DOPUSARIUM_TEST_ENVIRONMENT_NETBSD)
    else()
        add_compile_definitions(OPUSARIUM_TEST_ENVIRONMENT_NETBSD)
    endif()
elseif(${OPUSARIUM_CMAKE_ENVIRONMENT_NAME} STREQUAL "openbsd")
    if(${CMAKE_VERSION} VERSION_LESS "3.12.0")
        add_definitions(-DOPUSARIUM_TEST_ENVIRONMENT_OPENBSD)
    else()
        add_compile_definitions(OPUSARIUM_TEST_ENVIRONMENT_OPENBSD)
    endif()
elseif(${OPUSARIUM_CMAKE_ENVIRONMENT_NAME} STREQUAL "nucleus")
    if(${CMAKE_VERSION} VERSION_LESS "3.12.0")
        add_definitions(-DOPUSARIUM_TEST_ENVIRONMENT_NUCLEUS)
    else()
        add_compile_definitions(OPUSARIUM_TEST_ENVIRONMENT_NUCLEUS)
    endif()
elseif(${OPUSARIUM_CMAKE_ENVIRONMENT_NAME} STREQUAL "linux")
    if(${CMAKE_VERSION} VERSION_LESS "3.12.0")
        add_definitions(-DOPUSARIUM_TEST_ENVIRONMENT_LINUX)
    else()
        add_compile_definitions(OPUSARIUM_TEST_ENVIRONMENT_LINUX)
    endif()
elseif(${OPUSARIUM_CMAKE_ENVIRONMENT_NAME} STREQUAL "solaris")
    if(${CMAKE_VERSION} VERSION_LESS "3.12.0")
        add_definitions(-DOPUSARIUM_TEST_ENVIRONMENT_SOLARIS)
    else()
        add_compile_definitions(OPUSARIUM_TEST_ENVIRONMENT_SOLARIS)
    endif()
elseif(${OPUSARIUM_CMAKE_ENVIRONMENT_NAME} STREQUAL "vxworks")
    if(${CMAKE_VERSION} VERSION_LESS "3.12.0")
        add_definitions(-DOPUSARIUM_TEST_ENVIRONMENT_VXWORKS)
    else()
        add_compile_definitions(OPUSARIUM_TEST_ENVIRONMENT_VXWORKS)
    endif()
elseif(${OPUSARIUM_CMAKE_ENVIRONMENT_NAME} STREQUAL "windows")
    if(${CMAKE_VERSION} VERSION_LESS "3.12.0")
        add_definitions(-DOPUSARIUM_TEST_ENVIRONMENT_WINDOWS)
    else()
        add_compile_definitions(OPUSARIUM_TEST_ENVIRONMENT_WINDOWS)
    endif()
elseif(${OPUSARIUM_CMAKE_ENVIRONMENT_NAME} STREQUAL "wince")
    if(${CMAKE_VERSION} VERSION_LESS "3.12.0")
        add_definitions(-DOPUSARIUM_TEST_ENVIRONMENT_WINCE)
    else()
        add_compile_definitions(OPUSARIUM_TEST_ENVIRONMENT_WINCE)
    endif()
else()
    message(FATAL_ERROR "Unsupported environment: ${OPUSARIUM_CMAKE_ENVIRONMENT_NAME}")
endif()
message(STATUS "Opusarium environment detected: ${OPUSARIUM_CMAKE_ENVIRONMENT_NAME}")
