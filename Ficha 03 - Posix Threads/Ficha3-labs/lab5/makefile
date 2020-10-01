CC=gcc

CFLAGS=-Wall -W

PROG=lab5
OBJS=debug.o ${PROG}.o

LIBS=-lpthread

.PHONY: clean

${PROG}: ${OBJS}
	${CC} -o $@ ${OBJS} ${LIBS}

debug.o: debug.c debug.h
${PROG}.o: ${PROG}.c debug.h

.c.o:
	${CC} ${CFLAGS} -c $<

clean:
	rm -f *.o ${PROG}
