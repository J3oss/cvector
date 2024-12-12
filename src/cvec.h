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

//takes a reference of vector and new size
void cvec_resize(void* pVec, const uint32_t size);

//takes a reference of vector
void cvec_shrink_fit(void* pVec);

//takes a reference of vector and T element
#ifndef _WIN32
void __attribute__((ms_abi)) cvec_push_back(void* pVec, ...);
#endif

#ifdef _WIN32
#pragma comment(linker, "/alternatename:cvec_push_back=_impl_cvec_push_back")
void cvec_push_back(void* pVec, ...);
#endif
