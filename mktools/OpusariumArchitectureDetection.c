#if defined(__arm__) || defined(_M_ARM)
#if defined(__ARM_ARCH_2__)
#error OPUSARIUM_TEST_ARCHITECTURE_RESULT armv2
#elif defined(__ARM_ARCH_3__) || defined(__ARM_ARCH_3M__)
#error OPUSARIUM_TEST_ARCHITECTURE_RESULT armv3
#elif defined(__ARM_ARCH_4T__) || defined(__TARGET_ARM4T)
#error OPUSARIUM_TEST_ARCHITECTURE_RESULT armv4
#elif defined(__ARM_ARCH_5__) || defined(__ARM_ARCH_5E__)
#error OPUSARIUM_TEST_ARCHITECTURE_RESULT armv5
#elif defined(__ARM_ARCH_5T__) || defined(__ARM_ARCH_5TE__) || defined(__ARM_ARCH_5TEJ__)
#error OPUSARIUM_TEST_ARCHITECTURE_RESULT armv5t
#elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || \
	defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__)
#error OPUSARIUM_TEST_ARCHITECTURE_RESULT armv6
#elif defined(__ARM_ARCH_6T2__)
#error OPUSARIUM_TEST_ARCHITECTURE_RESULT armv6t2
#elif defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || \
	defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
#error OPUSARIUM_TEST_ARCHITECTURE_RESULT armv7
#endif
#elif defined(__aarch64__)
#error OPUSARIUM_TEST_ARCHITECTURE_RESULT arm64
#elif defined(i386) || defined(__i386) || defined(__i386__) || \
	defined(_M_IX86) || defined(_X86_)
#error OPUSARIUM_TEST_ARCHITECTURE_RESULT i386
#elif defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || \
	defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64)
#error OPUSARIUM_TEST_ARCHITECTURE_RESULT amd64
#elif defined(__ia64__) || defined(_IA64) || defined(__IA64__) || \
	defined(__ia64) || defined(_M_IA64) || defined(__itanium__)
#error OPUSARIUM_TEST_ARCHITECTURE_RESULT ia64
#elif defined(__mips__) || defined(mips) || defined(__mips) || defined(_MIPS_ISA)
#if defined(_MIPS_ISA_MIPS1)
#error OPUSARIUM_TEST_ARCHITECTURE_RESULT mips1
#elif defined(_MIPS_ISA_MIPS2)
#error OPUSARIUM_TEST_ARCHITECTURE_RESULT mips2
#elif defined(_MIPS_ISA_MIPS3)
#error OPUSARIUM_TEST_ARCHITECTURE_RESULT mips3
#elif defined(_MIPS_ISA_MIPS4)
#error OPUSARIUM_TEST_ARCHITECTURE_RESULT mips4
#endif
#elif defined(__powerpc) || defined(__powerpc__) || defined(__powerpc64__) || defined(__POWERPC__) || \
	defined(__ppc__) || defined(__ppc64__) || defined(__PPC__) || defined(__PPC64__) || \
	defined(_ARCH_PPC) || defined(_ARCH_PPC64) || defined(_M_PPC)
#if defined(__powerpc64__) || defined(__ppc64__) || defined(__PPC64__) || defined(_ARCH_PPC64)
#error OPUSARIUM_TEST_ARCHITECTURE_RESULT ppc64
#else
#error OPUSARIUM_TEST_ARCHITECTURE_RESULT ppc
#endif
#else
