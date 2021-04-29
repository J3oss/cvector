#include "vector.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INIT_CAPACITY 10

#define VSTART(V) (((struct vector_info*) V)-1)
#define  VDATA(V) (((struct vector_info*) V)+1)

struct vector_info
{
  unsigned int size;
  unsigned int capacity;
  unsigned int element_size;
};

void* new_vec_impl(unsigned int element_size, unsigned int capacity)
{
  unsigned int init_capacity = INIT_CAPACITY;

  if (capacity)
    init_capacity = capacity;

  struct vector_info* v = malloc( sizeof(struct vector_info) + (init_capacity * element_size) );

  v->size = 0;
  v->capacity = init_capacity;
  v->element_size = element_size;

  return ++v;
}

void free_vec(void *v)
{
  free(VSTART(v));
}

unsigned int get_vec_size(void* v)
{
  return VSTART(v)->size;
}

unsigned int get_vec_capacity(void* v)
{
  return VSTART(v)->capacity;
}

unsigned int get_vec_element_size(void* v)
{
  return VSTART(v)->element_size;
}

unsigned int is_vec_empty(void* v)
{
  return (get_vec_size(v) > 0) ? 0 : 1;
}

void reserve_vec(void** v, unsigned int capacity)
{
  if (get_vec_capacity(*v) > capacity)
    return;

  struct vector_info* new_v;

  new_v = realloc(VSTART(*v), sizeof(struct vector_info) + capacity * VSTART(*v)->element_size);
  assert(new_v);

  new_v->capacity = capacity;

  *v = new_v + 1;
}

void resize_vec(void** v, unsigned int size)
{
  if (size > get_vec_capacity(*v))
    reserve_vec(v, size);

  VSTART(*v)->size = size;
}

void shrink_fit_vec(void** v)
{
  struct vector_info* new_v;

  new_v = realloc(VSTART(*v), sizeof(struct vector_info) + VSTART(*v)->size * VSTART(*v)->element_size);
  assert(new_v);

  new_v->capacity = new_v->size;

  *v = VDATA(new_v);
}
