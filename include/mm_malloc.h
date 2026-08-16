#ifndef MM_MALLOC_H
#define MM_MALLOC_H

#include <stdlib.h>

#if defined(_MSC_VER)
#include <malloc.h>
#elif defined(__GNUC__) || defined(__clang__)
#include <mm_malloc.h>
#endif

static inline void* xaligned_alloc(size_t alignment, size_t size) {
#if defined(_MSC_VER)
    return _aligned_malloc(size, alignment);
#elif defined(__GNUC__) || defined(__clang__)
    void* ptr = NULL;
    if (posix_memalign(&ptr, alignment, size) != 0) {
        return NULL;
    }
    return ptr;
#else
    return malloc(size);
#endif
}

static inline void xaligned_free(void* ptr) {
#if defined(_MSC_VER)
    _aligned_free(ptr);
#elif defined(__GNUC__) || defined(__clang__)
    free(ptr);
#else
    free(ptr);
#endif
}

#endif // MM_MALLOC_H
