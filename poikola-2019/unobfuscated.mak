#!/usr/bin/env make
SHELL= /bin/bash

X11_LIBDIR= /opt/X11/lib
X11_INCDIR= /opt/X11/include
CWARN= -Wall -Wextra -pedantic ${CSILENCE}
CSILENCE= -Wno-gnu-label-as-value -Wno-sign-compare -Wno-unsequenced \
    -Wno-dollar-in-identifier-extension -Wno-sometimes-uninitialized
CSTD= -std=c11
ARCH=
CDEFINE=
CINCLUDE=
OPT= -O3
CFLAGS= ${CSTD} ${CWARN} ${ARCH} ${CDEFINE} ${CINCLUDE} ${OPT}
LIBS=
CC= cc
MAY_NEED_GCC= gcc


OBJ= prog.o
TARGET= prog

all: ${TARGET}
	@${TRUE}

prog: prog.c
	${CC} ${CFLAGS} $< -o $@ ${LIBS}

clean:
	rm -f ${OBJ}

clobber: clean
	rm -f ${TARGET}
	@-if [ -e sandwich ]; then \
	    rm -f sandwich; \
	    echo 'ate sandwich'; \
	fi
