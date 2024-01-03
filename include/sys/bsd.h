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

#ifndef _SYS_BSD_H_
#define _SYS_BSD_H_

/* Types for `void *' pointers.  */
#ifdef __linux__
#if __WORDSIZE == 64
typedef unsigned long int	__uintptr_t;
#else
typedef unsigned int		__uintptr_t;
#endif
#endif

/*
 * Fill the gaps in the Linux sysent table.
 * Long ago deprecated system calls are prefered.
 */
#define	LINUX_AMD64_SYS_kqueue		174	/* Was create_module till 2.6 */
#define	LINUX_AMD64_SYS_kevent		177	/* Was get_kernel_syms till 2.6 */
#define	LINUX_AMD64_SYS_sysctl		156	/* sysctl */
#define	LINUX_AMD64_SYS_sysctlbyname	183	/* Was afs_syscall */
#define	LINUX_I386_SYS_kqueue		127	/* Was create_module till 2.6 */
#define	LINUX_I386_SYS_kevent		130	/* Was get_kernel_syms till 2.6 */
#define	LINUX_I386_SYS_sysctl		149	/* sysctl */
#define	LINUX_I386_SYS_sysctlbyname	137	/* Was afs_syscall */

#if defined (__x86_64__)
#define	BSD_SYS_kqueue		LINUX_AMD64_SYS_kqueue
#define	BSD_SYS_kevent		LINUX_AMD64_SYS_kevent
#define	BSD_SYS_sysctl		LINUX_AMD64_SYS_sysctl
#define	BSD_SYS_sysctlbyname	LINUX_AMD64_SYS_sysctlbyname
#elif defined(__i386__)
#define	BSD_SYS_kqueue		LINUX_I386_SYS_kqueue
#define	BSD_SYS_kevent		LINUX_I386_SYS_kevent
#define	BSD_SYS_sysctl		LINUX_I386_SYS_sysctl
#define	BSD_SYS_sysctlbyname	LINUX_I386_SYS_sysctlbyname
#endif

#endif	/* _SYS_BSD_H_ */
