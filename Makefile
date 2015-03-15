CC=gcc
CFLAGS=-O3 -Wall -pedantic -D_GNU_SOURCE

LDFLAGS=
LIBS=

MAKEDEPEND=${CC} -MM
PROGRAM=password_generator

OBJS =	password_generator.o

DEPS:= ${OBJS:%.o=%.d}

all: $(PROGRAM)

${PROGRAM}: ${OBJS}
	${CC} ${CFLAGS} ${LDFLAGS} ${OBJS} ${LIBS} -o $@

clean:
	rm -f ${PROGRAM} ${OBJS} ${DEPS}

${OBJS} ${DEPS} ${PROGRAM} : Makefile

.PHONY : all clean

%.d : %.c
	${MAKEDEPEND} ${CFLAGS} $< -MT ${@:%.d=%.o} > $@

%.o : %.c
	${CC} ${CFLAGS} -c -o $@ $<

-include ${DEPS}
