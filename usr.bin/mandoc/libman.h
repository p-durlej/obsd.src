/*	$OpenBSD: libman.h,v 1.55 2017/04/24 23:06:09 schwarze Exp $ */
/*
 * Copyright (c) 2009, 2010, 2011 Kristaps Dzonsons <kristaps@bsd.lv>
 * Copyright (c) 2014, 2015 Ingo Schwarze <schwarze@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHORS DISCLAIM ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#define	MACRO_PROT_ARGS	  struct roff_man *man, \
			  enum roff_tok tok, \
			  int line, \
			  int ppos, \
			  int *pos, \
			  char *buf

struct	man_macro {
	void		(*fp)(MACRO_PROT_ARGS);
	int		  flags;
#define	MAN_SCOPED	 (1 << 0)  /* Optional next-line scope. */
#define	MAN_NSCOPED	 (1 << 1)  /* Allowed in next-line element scope. */
#define	MAN_BSCOPE	 (1 << 2)  /* Break next-line block scope. */
#define	MAN_JOIN	 (1 << 3)  /* Join arguments together. */
};

extern	const struct man_macro *const man_macros;


enum roff_tok	  man_hash_find(const char *);
void		  man_node_validate(struct roff_man *);
void		  man_state(struct roff_man *, struct roff_node *);
void		  man_unscope(struct roff_man *, const struct roff_node *);
