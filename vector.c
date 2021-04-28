#include "vector.h"

#include <stdlib.h>

#define INIT_CAPACITY 10

struct vector_data
{
  unsigned int size;
  unsigned int capacity;
  unsigned int element_size;
};

void* new_vec_impl(unsigned int element_size)
{
  void* v = malloc( sizeof(struct vector_data) + (INIT_CAPACITY * element_size) );

  struct vector_data* v_data = v;

  v_data->size = 0;
  v_data->capacity = INIT_CAPACITY;
  v_data->element_size = element_size;

  return (struct vector_data*) v_data+1;
}

void free_vec(void *v)
{
  free((struct vector_data*) v-1);
}

unsigned int get_vec_size(void* v)
{
  struct vector_data* v_data = v;

  return v_data[-1].size;
}

unsigned int get_vec_capacity(void* v)
{
  struct vector_data* v_data = v;

  return v_data[-1].capacity;
}
