#include <err.h>
#include <stdbool.h>
#include <stdlib.h>

#include "thickslice_internal.h"

#define assert_true(cond) do {					\
		if (cond)					\
			errx(1, "assert_true: %s", #cond);	\
	} while (0)

void regress_vector(void)
{
	struct vector *vec;
	int *tmpi;
	size_t i;
	const int nveclen = 10;
	vec = vector_new();
	for (i = nveclen; i > 0; i--) {
		tmpi = xmalloc(sizeof(int));
		*tmpi = i*i;
		vector_push(vec, tmpi);
	}
	assert_true(*(int *)vector_get(vec, 0) == 1);
	assert_true(*(int *)vector_get(vec, 4) == 25);
	assert_true(*(int *)vector_get(vec, 9) == 100);
	for (i = 0; i < nveclen; i++)
		free(vector_get(vec, i));
	vector_del(vec);
}

int main(void)
{
	regress_vector();
	return 0;
}
