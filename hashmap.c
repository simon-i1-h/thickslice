#include <err.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "thickslice.h"
#include "thickslice_internal.h"

const size_t HASHMAP_INIT_SIZE = 16;

struct hashmap {
	char **keys;
	void **vals;
	size_t len;  /* length of associative array */
	size_t cap;  /* memory capacity of associative array */
};

struct keyiter {
	struct hashmap *map;
	size_t count;
};

static size_t
calc_hash(char *str)
{
	/* DJBX33A algorithm */
	size_t i, r = 5381;
	for (i = 0; str[i] != '\0'; i++)
		r = (r << 5) + r + str[i];  /* (r << 5) + r == r * 33 */
	return r;
}

static bool
is_many_cap(struct hashmap *map)
{
	size_t cap;
	cap = map->cap;
	/* (cap >> 1) + (cap >> 3) + (cap >> 4) ~= cap * 0.6875 */
	return map->len > (cap >> 1) + (cap >> 3) + (cap >> 4);
}

static size_t
find_index(struct hashmap *map, char *key)
{
	size_t hash, mask = map->cap - 1;
	hash = calc_hash(key) & mask;
	for (; map->keys[hash] != NULL; hash = (hash + 1) & mask)
		if (strcmp(map->keys[hash], key) == 0)
			break;
	return hash;
}

static ssize_t
next_index(struct hashmap *map, size_t curr)
{
	for (; curr < map->cap; curr++)
		if (map->keys[curr] != NULL)
			return curr;
	return -1;
}

static void
assign(struct hashmap *map, char *key, void *val)
{
	size_t idx;
	idx = find_index(map, key);
	free(map->keys[idx]);
	map->keys[idx] = key;
	map->vals[idx] = val;
	map->len++;
}

static struct hashmap *
new_with_cap(size_t cap)
{
	size_t i;
	struct hashmap *r;
	r = xmalloc(sizeof(struct hashmap));
	*r = (struct hashmap){
		.keys = xallocarray(cap, sizeof(char *)),
		.vals = xallocarray(cap, sizeof(void *)),
		.len = 0,
		.cap = cap
	};
	for (i = 0; i < r->cap; i++)
		r->keys[i] = NULL;
	return r;
}

static void
rehash(struct hashmap *map)
{
	ssize_t i;
	struct hashmap *tmp;
	if (map->cap > SIZE_MAX / 2)
		erreno(1, ENOMEM, "rehash");
	tmp = new_with_cap(map->cap * 2);
	for (i = next_index(map, 0); i != -1; i = next_index(map, i + 1))
		assign(tmp, map->keys[i], map->vals[i]);
	free(map->keys);
	free(map->vals);
	*map = *tmp;
	free(tmp);
}

struct hashmap *
hashmap_new(void)
{
	return new_with_cap(HASHMAP_INIT_SIZE);
}

void
hashmap_del(struct hashmap *map)
{
	size_t i;
	for (i = 0; i < map->cap; i++)
		free(map->keys[i]);
	free(map->keys);
	free(map->vals);
	free(map);
}

void *
hashmap_get(struct hashmap *map, char *key)
{
	size_t idx;
	idx = find_index(map, key);
	if (map->keys[idx] == NULL)
		erreno(1, EINVAL, "hashmap_get");
	return map->vals[idx];
}

void
hashmap_set(struct hashmap *map, char *key, void *val)
{
	if (is_many_cap(map))
		rehash(map);
	assign(map, xstrdup(key), val);
}

bool
hashmap_has(struct hashmap *map, char *key)
{
	return map->keys[find_index(map, key)] != NULL;
}

struct keyiter *
hashmap_keys(struct hashmap *map)
{
	struct keyiter *r;
	r = xmalloc(sizeof(struct keyiter));
	*r = (struct keyiter){.map = map, .count = 0};
	return r;
}

char *
keyiter_next(struct keyiter *i)
{
	ssize_t idx;
	idx = next_index(i->map, i->count);
	if (idx == -1)
		return NULL;
	else {
		i->count = idx;
		return i->map->keys[i->count++];
	}
}

void
keyiter_del(struct keyiter *i)
{
	free(i);
}
