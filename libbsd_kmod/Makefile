# Copyright (c) 2021 Vladimir Kondratyev <vladimir@kondratyev.su>

KMOD=		linux_libbsd
SRCS=		linux_libbsd.c
CFLAGS+=	-I${.CURDIR}/../include
NO_XREF=	yes

.if ${MACHINE_ARCH} == "amd64"
CFLAGS+=-DCOMPAT_FREEBSD32 -DCOMPAT_LINUX32
.endif

.include <bsd.kmod.mk>
