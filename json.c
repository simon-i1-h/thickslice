#include <stdio.h>
#include <stdlib.h>

#include "thickslice.h"
#include "thickslice_internal.h"

void
json_parse(FILE *file, struct json **ret)
{
	size_t i, len;
	struct vector *toks;
	struct json *r;
	lex(file, &toks);
	parse(toks, &r);
	len = vector_len(toks);
	for (i = 0; i < len; i++)
		free(vector_get(toks, i));  /* XXX TODO: token_del */
	vector_del(toks);
	*ret = r;
}

void
json_del(struct json *json)
{
	switch (json->tag) {
	case JSON_OBJ:
		hashmap_del(json->v.obj);
		break;
	case JSON_ARR:
		vector_del(json->v.arr);
		break;
	}
	free(json);
}

void
json_collapse(struct json *json)
{
	struct keyiter *iter;
	char *k;
	size_t i, len;

	switch (json->tag) {
	case JSON_OBJ:
		iter = hashmap_keys(json->v.obj);
		while ((k = keyiter_next(iter)) != NULL)
			json_collapse((struct json *)hashmap_get(
				json->v.obj,
				k
			));
		keyiter_del(iter);
		break;
	case JSON_ARR:
		len = vector_len(json->v.arr);
		for (i = 0; i < len; i++)
			json_collapse((struct json *)vector_get(
				json->v.arr,
				i
			));
		break;
	}
	json_del(json);
}
