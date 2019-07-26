#ifndef THICKSLICE_INTERNAL_H
#define THICKSLICE_INTERNAL_H

#include <stdio.h>

#include "thickslice.h"

#define arrlen(arr) (sizeof(arr) / sizeof(arr[0]))

#define tochar(i) ((char)(unsigned char)i)

enum token_tag {
	TOK_OPEN_BRACE,
	TOK_CLOSE_BRACE,
	TOK_EOF
};

struct token {
	enum token_tag tag;
};

/* util.c */
void *xmalloc(size_t size);
void *xreallocarray(void *ptr, size_t nmemb, size_t size);
void *xallocarray(size_t nmemb, size_t size);
char *xstrdup(const char *str);
char *erreno(int eval, int eno, const char *fmt, ...);

/* lex.c */
void lex(FILE *file, struct vector **ret);

/* parse.c */
void parse(struct vector *toks, struct json **ret);

#endif  /* THICKSLICE_INTERNAL_H */
