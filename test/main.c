#include "../src/cvec.h"

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

int main()
{
    vec(int) v = new_vec(int, 0);
    assert(v != 0);
    
    printf("Initial size: %u\n", vec_size(v));
    printf("Initial capacity: %u\n", vec_capacity(v));

    for (int i = 0; i < 10; ++i) {
        vec_push_back((void**)&v, &i);
    }

    printf("Size after pushing elements: %u\n", vec_size(v));
    assert(vec_size(v) == 10);
    printf("Capacity after pushing elements: %u\n", vec_capacity(v));

    for (uint32_t i = 0; i < vec_size(v); ++i) {
        printf("Element at index %d: %d\n", i, v[i]);
        assert(v[i] == i);
    }

    vec_resize((void**)&v, 15);

    printf("Size after resizing: %u\n", vec_size(v));
    assert(vec_size(v) == 15);
    printf("Capacity after resizing: %u\n", vec_capacity(v));

    for (int i = 10; i < 15; ++i) {
        vec_push_back((void**)&v, &i);
    }

    printf("Size after pushing more elements: %u\n", vec_size(v));
    assert(vec_size(v) == 20);
    printf("Capacity after pushing more elements: %u\n", vec_capacity(v));
    assert(vec_capacity(v) == 22); //15 * 3/2

    vec_shrink_fit((void**)&v);
    printf("Size after shrink fit: %u\n", vec_size(v));
    printf("Capacity after shrink fit: %u\n", vec_capacity(v));
    assert(vec_size(v) == vec_capacity(v) &&  vec_size(v) == 20);

    if (vec_is_empty(v)) {
        printf("The vector is empty.\n");
    } else {
        printf("The vector is not empty.\n");
    }
    assert(!vec_is_empty(v));

    vec_free(v);
}
