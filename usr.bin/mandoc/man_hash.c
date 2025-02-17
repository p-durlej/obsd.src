/*	$OpenBSD: man_hash.c,v 1.26 2017/04/24 23:06:09 schwarze Exp $ */
/*
 * Copyright (c) 2008, 2009, 2010 Kristaps Dzonsons <kristaps@bsd.lv>
 * Copyright (c) 2015, 2017 Ingo Schwarze <schwarze@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#include <sys/types.h>

#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>

#include "mandoc.h"
#include "roff.h"
#include "man.h"
#include "libmandoc.h"
#include "libman.h"

#define	HASH_DEPTH	 6

#define	HASH_ROW(x) do { \
		if (isupper((unsigned char)(x))) \
			(x) -= 65; \
		else \
			(x) -= 97; \
		(x) *= HASH_DEPTH; \
	} while (/* CONSTCOND */ 0)

/*
 * Lookup table is indexed first by lower-case first letter (plus one
 * for the period, which is stored in the last row), then by lower or
 * uppercase second letter.  Buckets correspond to the index of the
 * macro (the integer value of the enum stored as a char to save a bit
 * of space).
 */
static	unsigned char	 table[26 * HASH_DEPTH];


void
man_hash_init(void)
{
	int		 i, j, x;

	if (*table != '\0')
		return;

	memset(table, UCHAR_MAX, sizeof(table));

	for (i = 0; i < (int)(MAN_MAX - MAN_TH); i++) {
		x = *roff_name[MAN_TH + i];

		assert(isalpha((unsigned char)x));

		HASH_ROW(x);

		for (j = 0; j < HASH_DEPTH; j++)
			if (UCHAR_MAX == table[x + j]) {
				table[x + j] = (unsigned char)i;
				break;
			}

		assert(j < HASH_DEPTH);
	}
}

enum roff_tok
man_hash_find(const char *tmp)
{
	int		 x, y, i;

	if ('\0' == (x = tmp[0]))
		return TOKEN_NONE;
	if ( ! (isalpha((unsigned char)x)))
		return TOKEN_NONE;

	HASH_ROW(x);

	for (i = 0; i < HASH_DEPTH; i++) {
		if (UCHAR_MAX == (y = table[x + i]))
			return TOKEN_NONE;

		if (strcmp(tmp, roff_name[MAN_TH + y]) == 0)
			return MAN_TH + y;
	}

	return TOKEN_NONE;
}
