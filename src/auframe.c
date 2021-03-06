/**
 * @file auframe.c  Audio frame
 *
 * Copyright (C) 2010 - 2020 Creytiv.com
 */

#include <string.h>
#include <re.h>
#include <rem.h>
#include <baresip.h>


void auframe_init(struct auframe *af, int fmt, void *sampv, size_t sampc)
{
	if (!af)
		return;

	info("auframe: init: fmt=%s, %zu samples\n",
	     aufmt_name(fmt), sampc);

	if (0 == aufmt_sample_size(fmt)) {
		warning("auframe: init: unsupported sample format %d (%s)\n",
			fmt, aufmt_name(fmt));
	}

	memset(af, 0, sizeof(*af));

	af->fmt = fmt;
	af->sampv = sampv;
	af->sampc = sampc;
}


size_t auframe_size(const struct auframe *af)
{
	size_t sz;

	if (!af)
		return 0;

	sz = aufmt_sample_size(af->fmt);
	if (sz == 0) {
		warning("auframe: size: illegal format %d (%s)\n",
			af->fmt, aufmt_name(af->fmt));
	}

	return af->sampc * sz;
}


void auframe_mute(struct auframe *af)
{
	if (!af)
		return;

	memset(af->sampv, 0, auframe_size(af));
}
