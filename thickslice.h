#ifndef THICKSLICE_H
#define THICKSLICE_H

#include <stdbool.h>
#include <stddef.h>

#define arrlen(arr) (sizeof(arr) / sizeof(arr[0]))

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

#endif  /* THICKSLICE_H */
