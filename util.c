#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void *
xmalloc(size_t size)
{
	void *r = malloc(size);
	if (r == NULL)
		err(1, "malloc");
	return r;
}

void *
xreallocarray(void *ptr, size_t nmemb, size_t size)
{
	void *r = reallocarray(ptr, nmemb, size);
	if (r == NULL)
		err(1, "reallocarray");
	return r;
}

void *
xallocarray(size_t nmemb, size_t size)
{
	return xreallocarray(NULL, nmemb, size);
}

char *
xstrdup(const char *str)
{
	char *r;
	r = strdup(str);
	if (r == NULL)
		err(1, "strdup");
	return r;
}

char *
erreno(int eval, int eno, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	errno = eno;
	verr(eval, fmt, ap);
	va_end(ap);
}
