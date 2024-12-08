#include "../src/cvec.h"

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

typedef struct
{
    uint32_t a;
    uint32_t b;
    uint32_t c;
} myStruct;

int main()
{
    cvec(int) v = new_cvec(int, 0);
    assert(v != 0);
    
    printf("Initial size: %u\n", cvec_size(v));
    printf("Initial capacity: %u\n", cvec_capacity(v));

    for (uint32_t i = 0; i < 10; ++i) {
        cvec_push_back(&v, &i);
    }

    printf("Size after pushing elements: %u\n", cvec_size(v));
    assert(cvec_size(v) == 10);
    printf("Capacity after pushing elements: %u\n", cvec_capacity(v));

    for (uint32_t i = 0; i < cvec_size(v); ++i) {
        printf("Element at index %d: %d\n", i, v[i]);
        assert(v[i] == i);
    }

    cvec_resize(&v, 15);

    printf("Size after resizing: %u\n", cvec_size(v));
    assert(cvec_size(v) == 15);
    printf("Capacity after resizing: %u\n", cvec_capacity(v));

    for (int i = 10; i < 15; ++i) {
        cvec_push_back(&v, &i);
    }

    printf("Size after pushing more elements: %u\n", cvec_size(v));
    assert(cvec_size(v) == 20);
    printf("Capacity after pushing more elements: %u\n", cvec_capacity(v));
    assert(cvec_capacity(v) == 22); //15 * 3/2

    cvec_shrink_fit(&v);
    printf("Size after shrink fit: %u\n", cvec_size(v));
    printf("Capacity after shrink fit: %u\n", cvec_capacity(v));
    assert(cvec_size(v) == cvec_capacity(v) &&  cvec_size(v) == 20);

    if (cvec_is_empty(v)) {
        printf("The vector is empty.\n");
    } else {
        printf("The vector is not empty.\n");
    }
    assert(!cvec_is_empty(v));

    cvec_free(v);

    //struct test
    myStruct ms0 = { 0, 5, 10};
    myStruct ms1 = { 1, 6, 11};
    myStruct ms2 = { 2, 7, 12};
    myStruct ms3 = { 3, 8, 13};
    myStruct ms4 = { 4, 9, 14};

    cvec(myStruct) vStruct = new_cvec(myStruct, 0);
    assert(vStruct != 0);

    printf("Initial size: %u\n", cvec_size(vStruct));
    printf("Initial capacity: %u\n", cvec_capacity(vStruct));

    cvec_push_back(&vStruct, &ms0);
    cvec_push_back(&vStruct, &ms1);
    cvec_push_back(&vStruct, &ms2);
    cvec_push_back(&vStruct, &ms3);
    cvec_push_back(&vStruct, &ms4);

    printf("Size after pushing elements: %u\n", cvec_size(vStruct));
    assert(cvec_size(vStruct) == 5);
    printf("Capacity after pushing elements: %u\n", cvec_capacity(vStruct));

    for (uint32_t i = 0; i < cvec_size(vStruct); ++i) {
        printf("Element at index %d: { %d, %d, %d }\n", i, vStruct[i].a, vStruct[i].b, vStruct[i].c);
        assert(vStruct[i].a == i && vStruct[i].b == i+5 && vStruct[i].c == i+10);
    }
}
