#include "../src/cvec.h"

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

typedef struct
{
    char a;
    char b;
    char c;
} struct03_t;

typedef struct
{
    uint32_t a;
    uint16_t b;
    char c;
} struct07_t;

typedef struct
{
    uint64_t a;
    uint16_t b;
    char c;
} struct11_t;

typedef struct
{
    uint64_t a;
    uint64_t b;
    char c;
} struct17_t;

int main()
{
    //int vector test
    cvec(int) v = new_cvec(int, 0);
    assert(v != 0);
    
    printf("Initial size: %llu\n", cvec_size(v));
    printf("Initial capacity: %llu\n", cvec_capacity(v));

    for (uint32_t i = 0; i < 10; ++i) {
        cvec_push(&v, i);
    }

    printf("Size after pushing elements: %llu\n", cvec_size(v));
    assert(cvec_size(v) == 10);
    printf("Capacity after pushing elements: %llu\n", cvec_capacity(v));

    for (uint32_t i = 0; i < cvec_size(v); ++i) {
        printf("Element at index %d: %d\n", i, v[i]);
        assert(v[i] == i);
    }

    cvec_resize(&v, 15);

    printf("Size after resizing: %llu\n", cvec_size(v));
    assert(cvec_size(v) == 15);
    printf("Capacity after resizing: %llu\n", cvec_capacity(v));

    for (int i = 10; i < 15; ++i) {
        cvec_push(&v, i);
    }

    printf("Size after pushing more elements: %llu\n", cvec_size(v));
    assert(cvec_size(v) == 20);
    printf("Capacity after pushing more elements: %llu\n", cvec_capacity(v));
    assert(cvec_capacity(v) == 22); //15 * 3/2

    cvec_shrink_fit(&v);
    printf("Size after shrink fit: %llu\n", cvec_size(v));
    printf("Capacity after shrink fit: %llu\n", cvec_capacity(v));
    assert(cvec_size(v) == cvec_capacity(v) &&  cvec_size(v) == 20);

    if (cvec_is_empty(v)) {
        printf("The vector is empty.\n");
    } else {
        printf("The vector is not empty.\n");
    }
    assert(!cvec_is_empty(v));

    cvec_free(v);

    //user defined test
    struct03_t s03_0 = {33,3,0}; struct07_t s07_0 = {777,77,7}; struct11_t s11_0 = {111111,1111,11}; struct17_t s17_0 = {171717,1717,17};
    struct03_t s03_1 = {34,4,1}; struct07_t s07_1 = {778,78,8}; struct11_t s11_1 = {111112,1112,12}; struct17_t s17_1 = {171718,1718,18};
    struct03_t s03_2 = {35,5,2}; struct07_t s07_2 = {779,79,9}; struct11_t s11_2 = {111113,1113,13}; struct17_t s17_2 = {171719,1719,19};

    cvec(struct03_t) vS03 = new_cvec(struct03_t, 0);
    cvec(struct07_t) vS07 = new_cvec(struct07_t, 0);
    cvec(struct11_t) vS11 = new_cvec(struct11_t, 0);
    cvec(struct17_t) vS17 = new_cvec(struct17_t, 0);

    cvec_push(&vS03, s03_0);
    cvec_push(&vS03, s03_1);
    cvec_push(&vS03, s03_2);

    cvec_push(&vS07, s07_0);
    cvec_push(&vS07, s07_1);
    cvec_push(&vS07, s07_2);

    cvec_push(&vS11, s11_0);
    cvec_push(&vS11, s11_1);
    cvec_push(&vS11, s11_2);

    cvec_push(&vS17, s17_0);
    cvec_push(&vS17, s17_1);
    cvec_push(&vS17, s17_2);

    for (uint32_t i = 0; i < cvec_size(vS03); ++i) {
        printf("vS03 Element at index %d: { %u, %u, %u }\n", i, vS03[i].a, vS03[i].b, vS03[i].c);
        assert(vS03[i].a == i+33 && vS03[i].b == i+3 && vS03[i].c == i+0);

        printf("vS07 Element at index %d: { %u, %u, %u }\n", i, vS07[i].a, vS07[i].b, vS07[i].c);
        assert(vS07[i].a == i+777 && vS07[i].b == i+77 && vS07[i].c == i+7);

        printf("vS11 Element at index %d: { %llu, %u, %u }\n", i, vS11[i].a, vS11[i].b, vS11[i].c);
        assert(vS11[i].a == i+111111 && vS11[i].b == i+1111 && vS11[i].c == i+11);

        printf("vS17 Element at index %d: { %llu, %llu, %u }\n", i, vS17[i].a, vS17[i].b, vS17[i].c);
        assert(vS17[i].a == i+171717 && vS17[i].b == i+1717 && vS17[i].c == i+17);
    }

    cvec_free(&vS03);
    cvec_free(&vS07);
    cvec_free(&vS11);
    cvec_free(&vS17);
}
