#include <err.h>

#include "thickslice.h"
#include "thickslice_internal.h"

static void
parse_arr(struct vector *toks, size_t *tok_cur, struct json **ret)
{
	if (((struct token *)vector_get(toks, *tok_cur))->tag ==
	    TOK_CLOSE_BRACKET) {
		(*tok_cur)++;
		*ret = xmalloc(sizeof(struct json));
		**ret = (struct json){.tag = JSON_ARR, .v.arr = vector_new()};
		return;
	}

	errx(1, "parse_arr: unexpected tokens");
}

static void
parse_obj(struct vector *toks, size_t *tok_cur, struct json **ret)
{
	if (((struct token *)vector_get(toks, *tok_cur))->tag ==
	    TOK_CLOSE_BRACE) {
		(*tok_cur)++;
		*ret = xmalloc(sizeof(struct json));
		**ret = (struct json){
			.tag = JSON_OBJ,
			.v.obj = hashmap_new()
		};
		return;
	}

	errx(1, "parse_obj: unexpected tokens");
}

void
parse(struct vector *toks, struct json **ret)
{
	size_t tok_cur = 0;

	if (((struct token *)vector_get(toks, tok_cur))->tag ==
	    TOK_OPEN_BRACE) {
		tok_cur++;
		parse_obj(toks, &tok_cur, ret);
	} else if (((struct token *)vector_get(toks, tok_cur))->tag ==
		   TOK_OPEN_BRACKET) {
		tok_cur++;
		parse_arr(toks, &tok_cur, ret);
	}

	if (((struct token *)vector_get(toks, tok_cur))->tag ==
	    TOK_EOF)
		return;

	errx(1, "parse: unexpected tokens");
}
