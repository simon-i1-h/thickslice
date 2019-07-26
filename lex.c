#include <err.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#include "thickslice.h"
#include "thickslice_internal.h"

static const bool is_whitespace[UCHAR_MAX + 1] = {
	[' '] = true,
	['\t'] = true,
	['\n'] = true,
	['\r'] = true
};

void
read_token(FILE *file, struct token *ret)
{
	int c;

st_init:
	/* prepare */
	if ((c = fgetc(file)) == EOF) {
		*ret = (struct token){.tag = TOK_EOF};
		return;
	}
	/* transition */
	if (is_whitespace[c])
		goto st_init;
	else if (tochar(c) == '{') {
		*ret = (struct token){.tag = TOK_OPEN_BRACE};
		return;
	} else if (tochar(c) == '}') {
		*ret = (struct token){.tag = TOK_CLOSE_BRACE};
		return;
	} else if (tochar(c) == '[') {
		*ret = (struct token){.tag = TOK_OPEN_BRACKET};
		return;
	} else if (tochar(c) == ']') {
		*ret = (struct token){.tag = TOK_CLOSE_BRACKET};
		return;
	} else
		errx(1, "unexpected character: %c", tochar(c));
}

void
lex(FILE *file, struct vector **ret)
{
	struct vector *r;
	struct token *tmp;
	r = vector_new();
	do {
		tmp = xmalloc(sizeof(struct token));
		read_token(file, tmp);
		vector_push(r, tmp);
	} while (tmp->tag != TOK_EOF);
	*ret = r;
}
