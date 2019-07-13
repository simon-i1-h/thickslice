#ifndef THICKSLICE_INTERNAL_H
#define THICKSLICE_INTERNAL_H

#include <stddef.h>

/* util.c */
void *xmalloc(size_t size);
void *xreallocarray(void *ptr, size_t nmemb, size_t size);
void *xallocarray(size_t nmemb, size_t size);

/* vector.c */
struct vector;
struct vector *vector_new(void);
void vector_del(struct vector *vec);
void vector_push(struct vector *vec, void *v);
size_t vector_len(struct vector *vec);

#endif  /* THICKSLICE_INTERNAL_H */
