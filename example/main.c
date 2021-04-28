#include "../vector.h"

#include <stdio.h>

int main()
{
  vec(int) t = new_vec(int, 20);

  int tSize = get_vec_size(t);
  printf("size: %d\n", tSize);

  int tCapacity = get_vec_capacity(t);
  printf("capacity: %d\n", tCapacity);

  if (is_vec_empty(t))
    printf("vector is empty\n");

  reserve_vec(&t, 50);

  tCapacity = get_vec_capacity(t);
  printf("capacity: %d\n", tCapacity);

  resize_vec(&t, 2);

  tSize = get_vec_size(t);
  printf("size: %d\n", tSize);

  resize_vec(&t, 100);

  tSize = get_vec_size(t);
  printf("size: %d\n", tSize);

  tCapacity = get_vec_capacity(t);
  printf("capacity: %d\n", tCapacity);

  if (is_vec_empty(t))
    printf("vector is empty\n");

  free_vec(t);
  return 0;
}
