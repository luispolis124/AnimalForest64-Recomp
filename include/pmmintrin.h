#ifndef PMMINTRIN_H
#define PMMINTRIN_H

#if defined(_MSC_VER)
#include <pmmintrin.h>
#elif defined(__GNUC__) || defined(__clang__)
#include <pmmintrin.h>
#else
#error "SSE3 (pmmintrin.h) is not supported by this compiler architecture."
#endif

#endif // PMMINTRIN_H
