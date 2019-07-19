#ifndef THICKSLICE_INTERNAL_H
#define THICKSLICE_INTERNAL_H

#include <stdbool.h>
#include <stddef.h>

#define arrlen(arr) (sizeof(arr) / sizeof(arr[0]))

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

/* hashmap.c */
struct hashmap;
struct keyiter;
struct hashmap *hashmap_new(void);
void hashmap_del(struct hashmap *map);
void *hashmap_get(struct hashmap *map, char *key);
void hashmap_set(struct hashmap *map, char *key, void *val);
bool hashmap_has(struct hashmap *map, char *key);
struct keyiter *hashmap_keys(struct hashmap *map);
char *keyiter_next(struct keyiter *i);
void keyiter_del(struct keyiter *i);

#endif  /* THICKSLICE_INTERNAL_H */
