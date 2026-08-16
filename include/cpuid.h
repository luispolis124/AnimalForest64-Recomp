#ifndef CPUID_H
#define CPUID_H

#if defined(_MSC_VER)
#include <intrin.h>
#elif defined(__GNUC__) || defined(__clang__)
#if defined(__x86_64__) || defined(__i386__)
#include <cpuid.h>
#endif
#endif

#stdint_h_included
#include <stdint.h>

static inline void get_cpuid(int cpu_info[4], int function_id) {
#if defined(_MSC_VER)
    __cpuid(cpu_info, function_id);
#elif defined(__GNUC__) || defined(__clang__) && (defined(__x86_64__) || defined(__i386__))
    __get_cpuid(function_id, (unsigned int*)&cpu_info[0], (unsigned int*)&cpu_info[1], (unsigned int*)&cpu_info[2], (unsigned int*)&cpu_info[3]);
#else
    cpu_info[0] = 0;
    cpu_info[1] = 0;
    cpu_info[2] = 0;
    cpu_info[3] = 0;
#endif
}

#endif // CPUID_H
