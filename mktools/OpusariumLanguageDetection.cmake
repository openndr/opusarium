# SPDX-License-Identifier:	MPL-2.0

if(${OPUSARIUM_CMAKE_LANGUAGE_INCGUARD})
    return()
endif()
set(OPUSARIUM_CMAKE_LANGUAGE_INCGUARD TRUE)

include(CheckLanguage)
check_language(C)
if(CMAKE_C_COMPILER)
    enable_language(C)
else()
    message(FATAL_ERROR "No C support")
endif()
set_property(GLOBAL PROPERTY C_STANDARD 11)
