#include <err.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "thickslice.h"
#include "thickslice_internal.h"

#define assert_true(cond) do {					\
		if (!(cond))					\
			errx(1, "assert_true: %s", #cond);	\
	} while (0)

void
regress_vector(void)
{
	struct vector *vec;
	int *tmpi;
	size_t i;
	const int nveclen = 10;
	vec = vector_new();
	for (i = nveclen; i > 0; i--) {
		tmpi = xmalloc(sizeof(int));
		*tmpi = i * i;
		vector_push(vec, tmpi);
	}
	assert_true(*(int *)vector_get(vec, 0) == 100);
	assert_true(*(int *)vector_get(vec, 5) == 25);
	assert_true(*(int *)vector_get(vec, 9) == 1);
	for (i = 0; i < nveclen; i++)
		free(vector_get(vec, i));
	vector_del(vec);
}

void
regress_map(void)
{
	struct hashmap *map;
	char *keys[] = {
		"key1 alice",
		"key2 bob",
		"key3 carol",
		"key4 dave",
		"key5 eve",
		"key6 isaac",
		"key7 ivan",
		"key8 justin",
		"key9 mallory",
		"key10 matilda",
		"key11 oscar",
		"key12 pat",
		"key13 peggy",
		"key9 mallory",
		"key14 victor",
		"key15 plod",
		"key16 stave",
		"key17 zoe"
	};
	int *tmpi;
	size_t i;
	const size_t keylen = arrlen(keys);
	struct keyiter *iter;
	char *k;
	map = hashmap_new();

	for (i = 0; i < keylen; i++) {
		if (hashmap_has(map, keys[i]))
			free(hashmap_get(map, keys[i]));
		tmpi = xmalloc(sizeof(int));
		*tmpi = i * 2;
		hashmap_set(map, keys[i], tmpi);
	}
	assert_true(*(int *)hashmap_get(map, keys[0]) == 0);
	assert_true(*(int *)hashmap_get(map, keys[8]) == 26);
	assert_true(*(int *)hashmap_get(map, keys[17]) == 34);
	iter = hashmap_keys(map);
	for (k = keyiter_next(iter); k != NULL; k = keyiter_next(iter))
		free(hashmap_get(map, k));
	hashmap_del(map);
	keyiter_del(iter);
}

void
test_obj(void)
{
	FILE *f;
	char *s;
	struct json *json;
	struct keyiter *iter;

	s = "  {  \t \r}\n";
	f = fmemopen(s, strlen(s), "r");
	json_parse(f, &json);
	assert_true(json->tag == JSON_OBJ);
	iter = hashmap_keys(json->v.obj);
	assert_true(keyiter_next(iter) == NULL);
	keyiter_del(iter);
	json_collapse(json);
	fclose(f);
}

int
main(void)
{
	regress_vector();
	regress_map();
	test_obj();
	return 0;
}
