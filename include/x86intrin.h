#ifndef X86INTRIN_H
#define X86INTRIN_H

#if defined(_MSC_VER)
#include <intrin.h>
#elif defined(__GNUC__) || defined(__clang__)
#include <x86intrin.h>
#else
#error "x86 intrinsics (x86intrin.h) are not supported by this compiler architecture."
#endif

#endif // X86INTRIN_H
