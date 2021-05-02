#include "../vector.h"

#include <stdio.h>

int main()
{
  vec(int) t = new_vec(int, 0);

  int tSize;
  int tCapacity;

  tSize = vec_get_size(t);
  printf("size: %d\n", tSize);
  tCapacity = vec_get_capacity(t);
  printf("capacity: %d\n", tCapacity);

  if (vec_is_empty(t))
    printf("vector is empty\n");

  int n = 5;
  vec_push_back(&t, &n);
  printf("%d\n", t[0]);

  vec_push_back(&t, &n);

  if (vec_is_empty(t))
    printf("vector is empty\n");

  tSize = vec_get_size(t);
  printf("size: %d\n", tSize);
  tCapacity = vec_get_capacity(t);
  printf("capacity: %d\n", tCapacity);

  vec_push_back(&t, &n);
  printf("%d\n", t[1]);

  tSize = vec_get_size(t);
  printf("size: %d\n", tSize);
  tCapacity = vec_get_capacity(t);
  printf("capacity: %d\n", tCapacity);

  if (vec_is_empty(t))
    printf("vector is empty\n");

  vec_reserve(&t, 50);

  tSize = vec_get_size(t);
  printf("size: %d\n", tSize);
  tCapacity = vec_get_capacity(t);
  printf("capacity: %d\n", tCapacity);

  vec_resize(&t, 2);

  tSize = vec_get_size(t);
  printf("size: %d\n", tSize);
  tCapacity = vec_get_capacity(t);
  printf("capacity: %d\n", tCapacity);

  vec_shrink_fit(&t);

  tSize = vec_get_size(t);
  printf("size: %d\n", tSize);
  tCapacity = vec_get_capacity(t);
  printf("capacity: %d\n", tCapacity);

  vec_resize(&t, 100);

  tSize = vec_get_size(t);
  printf("size: %d\n", tSize);
  tCapacity = vec_get_capacity(t);
  printf("capacity: %d\n", tCapacity);

  tSize = vec_get_size(t);
  printf("size: %d\n", tSize);
  tCapacity = vec_get_capacity(t);
  printf("capacity: %d\n", tCapacity);

  vec_free(t);
  return 0;
}
