#pragma once

#define vec(T) T*
#define new_vec(T) new_vec_impl(sizeof(T))

void* new_vec_impl(unsigned int element_size);

void free_vec(void *v);

unsigned int get_vec_size(void *v);

unsigned int get_vec_capacity(void *v);
