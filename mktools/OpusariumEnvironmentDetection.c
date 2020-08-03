/* SPDX-License-Identifier:	MPL-2.0 */

#if defined(_AIX)
#error OPUSARIUM_BUILD_ENVIRONMENT_RESULT aix
#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
#error OPUSARIUM_BUILD_ENVIRONMENT_RESULT freebsd
#elif defined(__NetBSD__)
#error OPUSARIUM_BUILD_ENVIRONMENT_RESULT netbsd
#elif defined(__OpenBSD__)
#error OPUSARIUM_BUILD_ENVIRONMENT_RESULT openbsd
#elif defined(__nucleus__)
#error OPUSARIUM_BUILD_ENVIRONMENT_RESULT nucleus
#elif defined(__linux__) || defined(linux) || (__linux)
#error OPUSARIUM_BUILD_ENVIRONMENT_RESULT linux
#elif defined(sun) || defined(__sun)
#error OPUSARIUM_BUILD_ENVIRONMENT_RESULT solaris
#elif defined(__VXWORKS__) || defined(__vxworks)
#error OPUSARIUM_BUILD_ENVIRONMENT_RESULT vxworks
#elif defined(_WIN32) || defined(_WIN64) || defined(__WIN32__)
#error OPUSARIUM_BUILD_ENVIRONMENT_RESULT windows
#elif defined(_WIN32_WCE)
#error OPUSARIUM_BUILD_ENVIRONMENT_RESULT wince
#else
#error OPUSARIUM_BUILD_ENVIRONMENT_RESULT unknown
#endif
