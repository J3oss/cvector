#include "../vector.h"

#include <stdio.h>

int main()
{
  vec(int) t = new_vec(int);

  int tSize = get_vec_size(t);
  printf("%d\n", tSize);

  int tCapacity = get_vec_capacity(t);
  printf("%d\n", tCapacity);

  free_vec(t);
  return 0;
}
