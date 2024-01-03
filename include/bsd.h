/*-
 * Copyright (c) 2021 Vladimir Kondratyev <vladimir@kondratyev.su>.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY Bill Paul AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL Bill Paul OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _BSD_H_
#define _BSD_H_

#include <sys/types.h>
#include <sys/bsd.h>

/*
 * Reset feature.h after last #include. Otherwise all extensions like
 * _GNU_SOURCES will be broken if bsd.h is included from command line with
 * specifying CFLAGS="-include bsd.h" option.
 */
#undef _FEATURES_H

#define	__FBSDID(s)
#define	__SCCSID(s)

__BEGIN_DECLS

char *	devname(dev_t dev, mode_t type);
char *	devname_r(dev_t dev, mode_t type, char *buf, int len);

size_t	strlcat(char * __restrict, const char * __restrict, size_t);
size_t	strlcpy(char * __restrict, const char * __restrict, size_t);

int	sysctlnametomib(const char *name, int *mibp, size_t *sizep);
int	sysctlbyname(const char *name, void *oldp, size_t *oldlenp,
	    const void *newp, size_t newlen);

__END_DECLS

#endif	/* _BSD_H_ */
