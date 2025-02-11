#pragma once

#include <stddef.h>
#include <stdbool.h>

#define vec(T) T *

#ifndef _WIN32
#define CALLCONVENTION __attribute__((ms_abi))
#define VA_LIST __builtin_ms_va_list
#define VA_START __builtin_ms_va_start
#define VA_ARG __builtin_va_arg
#else
#define CALLCONVENTION
#define VA_LIST va_list
#define VA_START va_start
#define VA_ARG va_arg
#endif

#define new_vec(T, CAP) _impl_new_vec(sizeof(T), CAP)
// NOLINTNEXTLINE
void *_impl_new_vec(size_t element_size, size_t capacity);

void vec_free(void *p_vec);

size_t vec_size(void *p_vec);
size_t vec_capacity(void *p_vec);
size_t vec_element_size(void *p_vec);

bool vec_is_empty(void *p_vec);

void vec_resize(void *p_vec, size_t size);

void vec_shrink_fit(void *p_vec);

void vec_remove(void *p_vec, size_t index);
void vec_remove_ordered(void *p_vec, size_t index);

size_t CALLCONVENTION vec_push(void *p_vec, ...);
size_t vec_push_ptr(void *p_vec, void *value);