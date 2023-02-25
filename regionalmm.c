#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct region {
  void *start;
  size_t size;
  void *current;
} region;

region *create_region(size_t size) {
  region *r = (region *)malloc(sizeof(region));
  r->start = malloc(size);
  r->size = size;
  r->current = r->start;
  return r;
}

void *region_alloc(region *r, size_t size) {
  if (r->current + size > r->start + r->size) {
    return NULL; // Out of memory
  }
  void *p = r->current;
  r->current += size;
  return p;
}

void free_region(region *r) {
    free(r->start);
    r->start = NULL;
    r->current = NULL;
    free(r);
    r = NULL;
}

void *get_from_region(region *r, size_t offset, size_t size) {
    if (r->start + offset + size > r->start + r->size) {
        return NULL; // Out of memory
    }
    return r->start + offset;
}

int test();
int test2();

int main() {
    test();
    test2();

    return 0;
}

int test() {
    region *r = create_region(sizeof(int)*2);

    int *y = (int *)region_alloc(r, sizeof(int));
    *y = 42;

    int *b = (int *)region_alloc(r, sizeof(int));
    *b = 63;

    int x;
    memcpy(&x, get_from_region(r, (size_t)y - (size_t)r->start, sizeof(int)), sizeof(int));

    free_region(r);
    printf("x = %p\n", b); // should print "x = 42"
}

int test2() {
    region *r = create_region(sizeof(int)*2);

    int *y = (int *)region_alloc(r, sizeof(int));
    *y = 42;

    int *b = (int *)region_alloc(r, sizeof(int));
    *b = 63;

    int x;
    memcpy(&x, get_from_region(r, (size_t)y - (size_t)r->start, sizeof(int)), sizeof(int));

    free_region(r);
    printf("x = %p\n", b); // should print "x = 42"
}
