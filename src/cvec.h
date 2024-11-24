#pragma once
#include <stdint.h>
#include <stdbool.h>

#define vec(T) T*

#define new_vec(T, CAP) _impl_new_vec(sizeof(T), CAP)
void* _impl_new_vec(const uint32_t element_size, const uint32_t capacity);

void vec_free(void *pVec);

uint32_t vec_size(const void* pVec);
uint32_t vec_capacity(const void* pVec);
uint32_t vec_element_size(const void* pVec);

bool vec_is_empty(const void* pVec);

void vec_resize(void** ppVec, const uint32_t size);

void vec_shrink_fit(void** ppVec);

void vec_push_back(void** v, void* element);
