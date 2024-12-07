#pragma once
#include <stdint.h>
#include <stdbool.h>

#define cvec(T) T*

#define new_cvec(T, CAP) _impl_new_cvec(sizeof(T), CAP)
void* _impl_new_cvec(const uint32_t element_size, const uint32_t capacity);

void cvec_free(void *pVec);

uint32_t cvec_size(const void* pVec);
uint32_t cvec_capacity(const void* pVec);
uint32_t cvec_element_size(const void* pVec);

bool cvec_is_empty(const void* pVec);

void cvec_resize(void** ppVec, const uint32_t size);

void cvec_shrink_fit(void** ppVec);

// argument are void** v and T element
void cvec_push_back(void** v, ...);
