PROG_SERVER=server

CMDLINE_DIR=../cmdline
DEBUG_DIR=../debug
OBJS_SERVER=${CMDLINE_DIR}/${PROG_SERVER}_cmdline.o ${DEBUG_DIR}/debug.o ${PROG_SERVER}.o

LIBS=#-lpthread
CC=gcc
CFLAGS=-Wall -W

.PHONY: clean

all: ${PROG_SERVER}

${PROG_SERVER}: ${OBJS_SERVER}
	${CC} -o $@ ${OBJS_SERVER} ${LIBS}

.c.o:
	${CC} ${CFLAGS} -c $< -o $@
	
clean:
	rm -f *.o ${PROG_SERVER} ${CMDLINE_DIR}/${PROG_SERVER}_cmdline.o ${DEBUG_DIR}/debug.o
	

