#pragma once

#define vec(T) T*
#define new_vec(T, CAP) new_vec_impl(sizeof(T), CAP)

void* new_vec_impl(unsigned int element_size, unsigned int capacity);

void free_vec(void *v);

unsigned int get_vec_size(void *v);

unsigned int get_vec_capacity(void *v);

unsigned int is_vec_empty(void* v);

void reserve_vec(void** v, unsigned int capacity);

void resize_vec(void** v, unsigned int size);
