#include "vector.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <stdio.h>

#define INIT_CAPACITY 10
#define GROWTH_RATE  3/2

#define VSTART(V) (((struct vector_info*) V)-1)
#define  VDATA(V) (((struct vector_info*) V)+1)

struct vector_info
{
  unsigned int size;
  unsigned int capacity;
  unsigned int element_size;
};

void* vec_alloc(void* v, unsigned int size)
{
  void* ptr = v ? VSTART(v):NULL;
  unsigned int total_size = sizeof(struct vector_info) + ( v ? size * VSTART(v)->element_size : size);

  return realloc(ptr, total_size);
}

void* impl_new_vec(unsigned int element_size, unsigned int capacity)
{
  unsigned int init_capacity = INIT_CAPACITY;

  if (capacity)
    init_capacity = capacity;

  struct vector_info* v = vec_alloc(NULL, init_capacity * element_size);

  v->size = 0;
  v->capacity = init_capacity;
  v->element_size = element_size;

  return ++v;
}

void vec_free(void *v)
{
  free(VSTART(v));
}

unsigned int vec_get_size(void* v)
{
  return VSTART(v)->size;
}

unsigned int vec_get_capacity(void* v)
{
  return VSTART(v)->capacity;
}

unsigned int vec_get_element_size(void* v)
{
  return VSTART(v)->element_size;
}

unsigned int vec_is_empty(void* v)
{
  return (vec_get_size(v) > 0) ? 0 : 1;
}

void impl_vec_reserve(void** v, unsigned int capacity)
{
  if (vec_get_capacity(*v) > capacity)
    return;

  struct vector_info* new_v = vec_alloc(*v, capacity);

  new_v->capacity = capacity;

  *v = ++new_v;
}

void impl_vec_resize(void** v, unsigned int size)
{
  if (size > vec_get_capacity(*v))
    vec_reserve(v, size * GROWTH_RATE);

  VSTART(*v)->size = size;
}

void impl_vec_shrink_fit(void** v)
{
  struct vector_info* new_v = vec_alloc(*v, VSTART(*v)->size);

  new_v->capacity = new_v->size;

  *v = ++new_v;
}

void impl_vec_push_back(void** v, void* element)
{
  unsigned int size = vec_get_size(*v);
  unsigned int capacity = vec_get_capacity(*v);
  unsigned int esize = vec_get_element_size(*v);

  vec_resize(v, size + 1);

  void* dest = (char*) (*v) + size * esize;

  memcpy( dest, element, esize );
}
