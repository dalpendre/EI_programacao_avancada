PROG_CLIENT=client

CMDLINE_DIR=../cmdline
DEBUG_DIR=../debug
OBJS_CLIENT=${CMDLINE_DIR}/${PROG_CLIENT}_cmdline.o ${DEBUG_DIR}/debug.o ${PROG_CLIENT}.o

LIBS=#-lpthread
CC=gcc
CFLAGS=-Wall -W

.PHONY: clean

all: ${PROG_CLIENT}

${PROG_CLIENT}: ${OBJS_CLIENT}
	${CC} -o $@ ${OBJS_CLIENT} ${LIBS}

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -f *.o ${PROG_CLIENT} ${CMDLINE_DIR}/${PROG_CLIENT}_cmdline.o ${DEBUG_DIR}/debug.o
	
