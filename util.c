#include <err.h>
#include <stdlib.h>

void *xmalloc(size_t size)
{
	void *r = malloc(size);
	if (r == NULL)
		err(1, "malloc");
	return r;
}

void *xreallocarray(void *ptr, size_t nmemb, size_t size)
{
	void *r = reallocarray(ptr, nmemb, size);
	if (r == NULL)
		err(1, "reallocarray");
	return r;
}

void *xallocarray(size_t nmemb, size_t size)
{
	return xreallocarray(NULL, nmemb, size);
}
