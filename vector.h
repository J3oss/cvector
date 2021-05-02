#pragma once

#define vec(T) T*
#define new_vec(T, CAP)      impl_new_vec(sizeof(T), CAP)

#define vec_shrink_fit(T)    impl_vec_shrink_fit ((void**)T)
#define vec_resize(T, E)     impl_vec_resize     ((void**)T, E)
#define vec_reserve(T, E)    impl_vec_reserve    ((void**)T, E)
#define vec_push_back(T, E)  impl_vec_push_back  ((void**)T, (void*)E)

void* impl_new_vec(unsigned int element_size, unsigned int capacity);

void vec_free(void *v);

unsigned int vec_get_size(void *v);

unsigned int vec_get_capacity(void *v);

unsigned int vec_is_empty(void* v);

void impl_vec_reserve(void** v, unsigned int capacity);

void impl_vec_resize(void** v, unsigned int size);

void impl_vec_shrink_fit(void** v);

void impl_vec_push_back(void** v, void* element);
