#ifndef THICKSLICE_INTERNAL_H
#define THICKSLICE_INTERNAL_H

#include <stddef.h>

#define arrlen(arr) (sizeof(arr) / sizeof(arr[0]))

/* util.c */
void *xmalloc(size_t size);
void *xreallocarray(void *ptr, size_t nmemb, size_t size);
void *xallocarray(size_t nmemb, size_t size);
char *xstrdup(const char *str);
char *erreno(int eval, int eno, const char *fmt, ...);

#endif  /* THICKSLICE_INTERNAL_H */
