#ifndef MMINTRIN_H
#define MMINTRIN_H

#if defined(_MSC_VER)
#include <mmintrin.h>
#elif defined(__GNUC__) || defined(__clang__)
#include <mmintrin.h>
#else
#error "MMX (mmintrin.h) is not supported by this compiler architecture."
#endif

#endif // MMINTRIN_H
