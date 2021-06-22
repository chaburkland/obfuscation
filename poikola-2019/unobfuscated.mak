#!/usr/bin/env make
SHELL= /bin/bash

X11_LIBDIR= /opt/X11/lib
X11_INCDIR= /opt/X11/include
CSILENCE= -Wno-sign-compare -Wsequence-point -Wunused-parameter
CWARN= -Wall -Wextra -pedantic ${CSILENCE}
CSTD= -std=c11
ARCH=
CDEFINE=
CINCLUDE=
OPT= -O3
CFLAGS= ${CSTD} ${CWARN} ${ARCH} ${CDEFINE} ${CINCLUDE} ${OPT}
LIBS=
CC= cc
MAY_NEED_GCC= gcc

TARGET= prog
SRC=prog.c

all: ${TARGET}
	@${TRUE}

prog: ${SRC}
	${CC} ${CFLAGS} $< -o $@ ${LIBS}

clean:
	rm -f ${TARGET}
