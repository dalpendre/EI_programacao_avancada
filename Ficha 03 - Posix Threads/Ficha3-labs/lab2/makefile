CC=gcc

CFLAGS=-Wall -W

PROG=lab2
OBJS=debug.o ${PROG}.o

.PHONY: clean

${PROG}: ${OBJS}
	${CC} -o $@ ${OBJS}

debug.o: debug.c debug.h
${PROG}.o: ${PROG}.c debug.h

.c.o:
	${CC} ${CFLAGS} -c $<

clean:
	rm -f *.o ${PROG}
