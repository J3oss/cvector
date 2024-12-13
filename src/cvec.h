#pragma once

#include <stdbool.h>

#define cvec(T) T*

#define new_cvec(T, CAP) _impl_new_cvec(sizeof(T), CAP)
void* _impl_new_cvec(const size_t element_size, const size_t capacity);

void cvec_free(void *pVec);

size_t cvec_size(const void* pVec);
size_t cvec_capacity(const void* pVec);
size_t cvec_element_size(const void* pVec);

bool cvec_is_empty(const void* pVec);

//takes a reference of vector and new size
void cvec_resize(void* pVec, const size_t size);

//takes a reference of vector
void cvec_shrink_fit(void* pVec);

#ifndef _WIN32
//takes a reference of vector and T element
void __attribute__((ms_abi)) cvec_push(void* pVec, ...);
#endif
#ifdef _WIN32
#pragma comment(linker, "/alternatename:cvec_push=_impl_cvec_push")
//takes a reference of vector and T element
void cvec_push(void* pVec, ...);
#endif
