#include <err.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>

#include "thickslice.h"
#include "thickslice_internal.h"

const size_t VECTOR_INIT_CAP = 8;

struct vector {
	void **arr;  /* variadic array */
	size_t len;  /* length of variadic array */
	size_t cap;  /* memory capacity of variadic array */
};

static void grow(struct vector *vec)
{
	size_t newnmemb;
	if (vec->cap > SIZE_MAX / 2)
		erreno(1, ENOMEM, "grow");
	newnmemb = vec->cap * 2;
	vec->arr = xreallocarray(vec->arr, newnmemb, sizeof(void *));
	vec->cap = newnmemb;
}

struct vector *vector_new(void)
{
	struct vector *r = xmalloc(sizeof(struct vector));
	*r = (struct vector){
		.arr = xallocarray(VECTOR_INIT_CAP, sizeof(void *)),
		.len = 0,
		.cap = VECTOR_INIT_CAP
	};
	return r;
}

void vector_del(struct vector *vec)
{
	free(vec->arr);
	free(vec);
}

void vector_push(struct vector *vec, void *val)
{
	if (vec->cap < vec->len)
		errx(1, "BUG: vec->cap < vec->len");
	else if (vec->cap == vec->len)
		grow(vec);
	vec->arr[vec->len++] = val;
}

size_t vector_len(struct vector *vec)
{
	return vec->len;
}

void *vector_get(struct vector *vec, size_t index)
{
	if (index >= vec->len)
		erreno(1, EINVAL, "vector_get");
	return vec->arr[index];
}
