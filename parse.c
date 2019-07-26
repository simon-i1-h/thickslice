#include <err.h>

#include "thickslice.h"
#include "thickslice_internal.h"

void
parse(struct vector *toks, struct json **ret)
{
	struct json *r;
	if (((struct token *)vector_get(toks, 0))->tag == TOK_OPEN_BRACE &&
	    ((struct token *)vector_get(toks, 1))->tag == TOK_CLOSE_BRACE &&
	    ((struct token *)vector_get(toks, 2))->tag == TOK_EOF) {
		r = xmalloc(sizeof(struct json));
		*r = (struct json){.tag = JSON_OBJ, .v.obj = hashmap_new()};
		*ret = r;
		return;
	}
	errx(1, "unexpected tokens");
}
