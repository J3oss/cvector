#include "cvec.h"

#include <stdlib.h>
#include <string.h>

#define INIT_CAPACITY 10
#define GROWTH_RATE  3/2

typedef struct
{
  size_t size;
  size_t tsize;
  size_t capacity;
} meta_data_t;

#define DATA_PTR(pData)  (((meta_data_t*) pData) + 1)
#define METADATA_PTR(pData) (((meta_data_t*) pData) - 1)

#define SIZE(pVec) METADATA_PTR(pVec)->size
#define TSIZE(pVec) METADATA_PTR(pVec)->tsize
#define CAPACITY(pVec) METADATA_PTR(pVec)->capacity

//returns pointer to meta data
void* cvec_alloc(void* pMetaData, const size_t dataSize)
{
  void* pVec = pMetaData ? pMetaData:NULL;
  const size_t total_size = sizeof(meta_data_t) + dataSize;

  return realloc(pVec, total_size);
}

//returns pointer to data
void* _impl_new_cvec(const size_t type_size, const size_t capacity)
{
  const size_t init_cap = capacity ? capacity:INIT_CAPACITY;

  meta_data_t* v = cvec_alloc(NULL, init_cap * type_size);
  v->size = 0;
  v->tsize = type_size;
  v->capacity = init_cap;

  return ++v;
}

void cvec_free(void *pVec)
{
  void* const * ppVec = pVec;
  free(METADATA_PTR(*ppVec));
}

size_t cvec_size(const void* pVec)
{
  void* const * ppVec = pVec;
  return SIZE(*ppVec);
}

size_t cvec_capacity(const void* pVec)
{
  void* const * ppVec = pVec;
  return CAPACITY(*ppVec);
}

size_t cvec_element_size(const void* pVec)
{
  void* const * ppVec = pVec;
  return TSIZE(*ppVec);
}

bool cvec_is_empty(const void* pVec)
{
  void* const * ppVec = pVec;
  return SIZE(*ppVec) ? false : true;
}

void cvec_reserve(void** ppVec, const size_t new_capacity)
{
  if (CAPACITY(*ppVec) > new_capacity)
    return;

  meta_data_t* new_vec = cvec_alloc(METADATA_PTR(*ppVec), new_capacity * TSIZE(*ppVec));
  new_vec->capacity = new_capacity;
  *ppVec = ++new_vec;
}

void cvec_resize(void* pVec, const size_t size)
{
  void** ppVec = pVec;

  if (size > SIZE(*ppVec))
    cvec_reserve(ppVec, size);

  METADATA_PTR(*ppVec)->size = size;
}

void cvec_shrink_fit(void* pVec)
{
  void** ppVec = pVec;

  meta_data_t* new_v = cvec_alloc(METADATA_PTR(*ppVec), SIZE(*ppVec) * CAPACITY(*ppVec));
  new_v->size = new_v->size;
  new_v->capacity = new_v->size;

  *ppVec = ++new_v;
}

#ifndef _WIN32
void __attribute__((ms_abi)) cvec_push(void* pVec, ...) __attribute__((alias("_impl_cvec_push")));
void __attribute__((ms_abi)) _impl_cvec_push(void* pVec, size_t arg1)
#endif
#ifdef _WIN32
void cvec_push(void* pVec, ...);
void _impl_cvec_push(void* pVec, size_t arg1)
#endif
{
  void** ppVec = pVec;

  const size_t size = SIZE(*ppVec);
  const size_t tsize = TSIZE(*ppVec);

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

