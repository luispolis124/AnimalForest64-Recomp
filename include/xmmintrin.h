#ifndef XMMINTRIN_H
#define XMMINTRIN_H

#if defined(_MSC_VER)
#include <xmmintrin.h>
#elif defined(__GNUC__) || defined(__clang__)
#include <xmmintrin.h>
#else
#error "SSE (xmmintrin.h) is not supported by this compiler architecture."
#endif

#endif // XMMINTRIN_H
