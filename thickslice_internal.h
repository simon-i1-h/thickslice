#ifndef THICKSLICE_INTERNAL_H
#define THICKSLICE_INTERNAL_H

#include <stddef.h>

/* util.c */
void *xmalloc(size_t size);
void *xreallocarray(void *ptr, size_t nmemb, size_t size);
void *xallocarray(size_t nmemb, size_t size);
char *xstrdup(const char *str);
char *erreno(int eval, int eno, const char *fmt, ...);

/* vector.c */
struct vector;
struct vector *vector_new(void);
void vector_del(struct vector *vec);
void vector_push(struct vector *vec, void *val);
size_t vector_len(struct vector *vec);
void *vector_get(struct vector *vec, size_t index);

#endif  /* THICKSLICE_INTERNAL_H */
