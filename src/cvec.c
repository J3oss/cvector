#include "cvec.h"

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

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
void* cvec_alloc(void* pMetaData, const uint32_t dataSize)
{
  void* pVec = pMetaData ? pMetaData:NULL;
  const uint32_t total_size = sizeof(meta_data) + dataSize;  

  return realloc(pVec, total_size);
}

//returns pointer to data
void* _impl_new_cvec(const uint32_t type_size, const uint32_t capacity)
{
  const uint32_t init_cap = capacity ? capacity:INIT_CAPACITY;

  meta_data* v = cvec_alloc(NULL, init_cap * type_size);
  v->size = 0;
  v->tsize = type_size;
  v->capacity = init_cap;

  return ++v;
}

void cvec_free(void *pVec)
{
  free(METADATA_PTR(pVec));
}

uint32_t cvec_size(const void* pVec)
{
  return SIZE(pVec);
}

uint32_t cvec_capacity(const void* pVec)
{
  return CAPACITY(pVec);
}

uint32_t cvec_element_size(const void* pVec)
{
  return TSIZE(pVec);
}

bool cvec_is_empty(const void* pVec)
{
  return SIZE(pVec) ? false : true;
}

void cvec_reserve(void** ppVec, const uint32_t new_capacity)
{
  if (CAPACITY(*ppVec) > new_capacity)
    return;

  meta_data* new_vec = cvec_alloc(METADATA_PTR(*ppVec), new_capacity * TSIZE(*ppVec));
  new_vec->capacity = new_capacity;
  *ppVec = ++new_vec;
}

void cvec_resize(void* pVec, const uint32_t size)
{
  void** ppVec = pVec;

  if (size > SIZE(*ppVec))
    cvec_reserve(ppVec, size);

  METADATA_PTR(*ppVec)->size = size;
}

void cvec_shrink_fit(void* pVec)
{
  void** ppVec = pVec;

  meta_data* new_v = cvec_alloc(METADATA_PTR(*ppVec), SIZE(*ppVec) * CAPACITY(*ppVec));
  new_v->size = new_v->size;
  new_v->capacity = new_v->size;

  *ppVec = ++new_v;
}

#ifndef _WIN32
void __attribute__((ms_abi)) cvec_push_back(void* pVec, ...) __attribute__((alias("_impl_cvec_push_back")));
void __attribute__((ms_abi)) _impl_cvec_push_back(void* pVec, uint64_t arg1)
#endif
#ifdef _WIN32
void cvec_push_back(void* pVec, ...);
void _impl_cvec_push_back(void* pVec, uint64_t arg1)
#endif
{
  void** ppVec = pVec;

  const uint32_t size = SIZE(*ppVec);
  const uint32_t tsize = TSIZE(*ppVec);

  if (CAPACITY(*ppVec) < size + 1) {
    cvec_reserve(ppVec, size * GROWTH_RATE);
  }

  void* dest = (char*) (*ppVec) + size * tsize;
  switch (tsize)
  {
    case 1:
    case 2:
    case 4:
    case 8:
      memcpy(dest, &arg1, tsize);
      break;
    default:
      memcpy(dest, (void*)arg1, tsize);
    break;
  }

  METADATA_PTR(*ppVec)->size = size + 1;
}

