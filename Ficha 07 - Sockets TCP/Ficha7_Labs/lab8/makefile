PROG_CLIENT=client
PROG_SERVER=server

CMDLINE_DIR=../cmdline
DEBUG_DIR=../debug
OBJS_CLIENT=${CMDLINE_DIR}/${PROG_CLIENT}_cmdline.o ${DEBUG_DIR}/debug.o ${PROG_CLIENT}.o
OBJS_SERVER=${CMDLINE_DIR}/${PROG_SERVER}_cmdline.o ${DEBUG_DIR}/debug.o ${PROG_SERVER}.o

LIBS=#-lpthread
CC=gcc
CFLAGS=-Wall -W

.PHONY: clean

all: ${PROG_CLIENT} ${PROG_SERVER}

${PROG_CLIENT}: ${OBJS_CLIENT}
	${CC} -o $@ ${OBJS_CLIENT} ${LIBS}

${PROG_SERVER}: ${OBJS_SERVER}
	${CC} -o $@ ${OBJS_SERVER} ${LIBS}

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -f *.o ${PROG_CLIENT} ${PROG_SERVER} ${CMDLINE_DIR}/${PROG_SERVER}_cmdline.o  ${CMDLINE_DIR}/${PROG_CLIENT}_cmdline.o ${DEBUG_DIR}/debug.o
	
