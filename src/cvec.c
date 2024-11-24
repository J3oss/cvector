#include "cvec.h"

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define INIT_CAPACITY 10
#define GROWTH_RATE  3/2

typedef struct
{
  uint32_t size;
  uint32_t tsize;
  uint32_t capacity;
} meta_data;

#define DATA_PTR(pData)  (((meta_data*) pData) + 1)
#define METADATA_PTR(pData) (((meta_data*) pData) - 1)

#define SIZE(pVec) METADATA_PTR(pVec)->size
#define TSIZE(pVec) METADATA_PTR(pVec)->tsize
#define CAPACITY(pVec) METADATA_PTR(pVec)->capacity

//returns pointer to meta data
void* vec_alloc(void* pMetaData, const uint32_t dataSize)
{
  void* pVec = pMetaData ? pMetaData:NULL;
  const uint32_t total_size = sizeof(meta_data) + dataSize;  

  return realloc(pVec, total_size);
}

//returns pointer to data
void* _impl_new_vec(const uint32_t type_size, const uint32_t capacity)
{
  const uint32_t init_cap = capacity ? capacity:INIT_CAPACITY;

  meta_data* v = vec_alloc(NULL, init_cap * type_size);  
  v->size = 0;
  v->tsize = type_size;
  v->capacity = init_cap;

  return ++v;
}

void vec_free(void *pVec)
{
  free(METADATA_PTR(pVec));
}

uint32_t vec_size(const void* pVec)
{
  return SIZE(pVec);
}

uint32_t vec_capacity(const void* pVec)
{
  return CAPACITY(pVec);
}

uint32_t vec_element_size(const void* pVec)
{
  return TSIZE(pVec);
}

bool vec_is_empty(const void* pVec)
{
  return SIZE(pVec) ? false : true;
}

void vec_reserve(void** ppVec, const uint32_t new_capacity)
{
  if (CAPACITY(*ppVec) > new_capacity)
    return;

  meta_data* new_vec = vec_alloc(METADATA_PTR(*ppVec), new_capacity * TSIZE(*ppVec));
  new_vec->capacity = new_capacity;
  *ppVec = ++new_vec;
}

void vec_resize(void** ppVec, const uint32_t size)
{
  if (size > SIZE(*ppVec))
    vec_reserve(ppVec, size);

  METADATA_PTR(*ppVec)->size = size;
}

void vec_shrink_fit(void** ppVec)
{
  meta_data* new_v = vec_alloc(METADATA_PTR(*ppVec), SIZE(*ppVec) * CAPACITY(*ppVec));
  new_v->size = new_v->size;
  new_v->capacity = new_v->size;

  *ppVec = ++new_v;
}

void vec_push_back(void** ppVec, void* element)
{
  const uint32_t size = SIZE(*ppVec);
  const uint32_t tsize = TSIZE(*ppVec);

  if (CAPACITY(*ppVec) < size + 1) {
    vec_reserve(ppVec, size * GROWTH_RATE);
  }

  void* dest = (char*) (*ppVec) + size * tsize;
  memcpy(dest, element, tsize);

  METADATA_PTR(*ppVec)->size = size + 1;
}
