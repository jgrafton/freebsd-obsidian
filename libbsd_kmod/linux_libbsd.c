/*-
 * SPDX-License-Identifier: BSD-2-Clause-FreeBSD
 *
 * Copyright (c) 2021 Vladimir Kondratyev <vladimir@kondratyev.su>
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
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

#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include <sys/param.h>
#include <sys/module.h>
#include <sys/kernel.h>
#include <sys/syscall.h>
#include <sys/sysent.h>
#include <sys/systm.h>

#include <compat/freebsd32/freebsd32_util.h>

#include "sys/bsd.h"

//#undef	COMPAT_LINUX32

#define DPRINTF(fmt, ...) do {					\
	printf("%s: " fmt "\n", __FUNCTION__ ,##__VA_ARGS__);	\
} while (0)

extern struct sysent linux_sysent[];
#ifdef COMPAT_LINUX32
extern struct sysent linux32_sysent[];
#endif

static const struct sysent_map {
	size_t fbsd_sy;
	size_t lnx_sy;
	size_t lnx32_sy;
	bool can_overload;	/* Can overload implemented syscalls */
} sy_map[] = {{
	.fbsd_sy = SYS_kqueue,
	.lnx_sy = LINUX_AMD64_SYS_kqueue,
	.lnx32_sy = LINUX_I386_SYS_kqueue,
}, {
	.fbsd_sy = SYS_kevent,
	.lnx_sy = LINUX_AMD64_SYS_kevent,
	.lnx32_sy = LINUX_I386_SYS_kevent,
}, {
	.fbsd_sy = SYS___sysctl,
	.lnx_sy = LINUX_AMD64_SYS_sysctl,
	.lnx32_sy = LINUX_I386_SYS_sysctl,
	.can_overload = true, 
#if __FreeBSD_version >= 1300045
}, {
	.fbsd_sy = SYS___sysctlbyname,
	.lnx_sy = LINUX_AMD64_SYS_sysctlbyname,
	.lnx32_sy = LINUX_I386_SYS_sysctlbyname,
#endif
}};
static struct sysent save[nitems(sy_map)];
#ifdef COMPAT_LINUX32
static struct sysent save32[nitems(sy_map)];
#endif

static int
linux_libbsd_set_sysent(void)
{
	size_t i;

	/*
	 * XXX: Syscall implementation check is disabled due to linux_nosys
	 *      symbol clash between 64 and 32 bit platforms.
	 */
	for (i = 0; i < nitems(sy_map); i++) {
		if (linux_sysent[sy_map[i].lnx_sy].sy_thrcnt !=
		    SY_THR_ABSENT && !sy_map[i].can_overload) {
			DPRINTF("syscall #%ju is already implemented",
			    sy_map[i].lnx_sy);
			return (EEXIST);
		}
#ifdef COMPAT_LINUX32
		if (linux32_sysent[sy_map[i].lnx32_sy].sy_thrcnt !=
		    SY_THR_ABSENT && !sy_map[i].can_overload) {
			DPRINTF("syscall32 #%ju is already implemented",
			    sy_map[i].lnx32_sy);
			return (EEXIST);
		}
#endif
	}

	for (i = 0; i < nitems(sy_map); i++) {
		save[i] = linux_sysent[sy_map[i].lnx_sy];
		linux_sysent[sy_map[i].lnx_sy] =
		    sysent[sy_map[i].fbsd_sy];
		/* Linuxolator does not use SYF_CAPENABLED flag */
		linux_sysent[sy_map[i].lnx_sy].sy_flags &= ~SYF_CAPENABLED;
#ifdef COMPAT_LINUX32
		save32[i] = linux32_sysent[sy_map[i].lnx32_sy];
		linux32_sysent[sy_map[i].lnx32_sy] =
		    freebsd32_sysent[sy_map[i].fbsd_sy];
		linux32_sysent[sy_map[i].lnx32_sy].sy_flags &= ~SYF_CAPENABLED;
#endif
	}

	return (0);
}

static int
linux_libbsd_unset_sysent(void)
{
	size_t i;

	for (i = 0; i < nitems(sy_map); i++) {
		if (linux_sysent[sy_map[i].lnx_sy].sy_call !=
		    sysent[sy_map[i].fbsd_sy].sy_call) {
			DPRINTF("syscall #%ju has changed since module load",
			    sy_map[i].lnx_sy);
			continue;
		}
		linux_sysent[sy_map[i].lnx_sy] = save[i];
	}
#ifdef COMPAT_LINUX32
	for (i = 0; i < nitems(sy_map); i++) {
		if (linux32_sysent[sy_map[i].lnx32_sy].sy_call !=
		    freebsd32_sysent[sy_map[i].fbsd_sy].sy_call) {
			DPRINTF("syscall32 #%ju has changed since module load",
			    sy_map[i].lnx32_sy);
			continue;
		}
		linux32_sysent[sy_map[i].lnx32_sy] = save32[i];
	}
#endif
	return (0);
}

static int
linux_libbsd_load(struct module *module, int cmd, void *arg)
{
	static bool initialized;
	int error = 0;

	switch (cmd) {
	case MOD_LOAD:
		error = linux_libbsd_set_sysent();
		initialized = error == 0;
		break;
	case MOD_UNLOAD:
		if (!initialized)
			break;
		error = linux_libbsd_unset_sysent();
		break;
	default:
		error = EOPNOTSUPP;
		break;
	}

	return (error);
}

static moduledata_t linux_libbsd_moddata = {
	"linux_libbsd",
	linux_libbsd_load,
	NULL,
};

DECLARE_MODULE(linux_libbsd, linux_libbsd_moddata, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);
MODULE_VERSION(linux_libbsd, 1);
MODULE_DEPEND(linux_libbsd, linux64, 1, 1, 1);
#ifdef COMPAT_LINUX32
MODULE_DEPEND(linux_libbsd, linux, 1, 1, 1);
#endif
