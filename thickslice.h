#ifndef THICKSLICE_H
#define THICKSLICE_H

#include <stdbool.h>
#include <stdio.h>

enum json_tag {
	JSON_OBJ
};

struct json {
	enum json_tag tag;
	union {
		struct hashmap *obj;
	} v;
};

/* vector.c */
struct vector;
struct vector *vector_new(void);
void vector_del(struct vector *vec);
void vector_push(struct vector *vec, void *val);
size_t vector_len(struct vector *vec);
void *vector_get(struct vector *vec, size_t idx);

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

/* json.c */
void json_parse(FILE *file, struct json **ret);
void json_del(struct json *json);
void json_collapse(struct json *json);

#endif  /* THICKSLICE_H */
