#ifndef EMMINTRIN_H
#define EMMINTRIN_H

#if defined(_MSC_VER)
#include <emmintrin.h>
#elif defined(__GNUC__) || defined(__clang__)
#include <emmintrin.h>
#else
#error "SSE2 (emmintrin.h) is not supported by this compiler architecture."
#endif

#endif // EMMINTRIN_H
