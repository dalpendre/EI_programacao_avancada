# Makefile que facilmente se adapta a qualquer tipo de exercicio
# author Vitor Carreira
# date 2009-09-23
#

# Bibliotecas a incluir
LIBS=-pthread 

# Flags para o compilador
CFLAGS=-Wall -W -g -Wmissing-prototypes

# Flags para a indentacao de codigo 
IFLAGS=-br -brs -npsl -ce -cli4


# nome do executavel 
PROGRAM=lab6

# Nome do ficheiro de opcoes do gengetopt (caso exista)
PROGRAM_OPT=#args

# Lista de objectos necessarios para criar o executavel
PROGRAM_OBJS=main.o debug.o # ${PROGRAM_OPT}.o

.PHONY: clean

all: ${PROGRAM}

# compilar com depuracao
depuracao: CFLAGS += -D SHOW_DEBUG 
depuracao: ${PROGRAM}

${PROGRAM}: ${PROGRAM_OBJS}
	${CC} -o $@ ${PROGRAM_OBJS} ${LIBS}

# Dependencias 
main.o: main.c debug.h #${PROGRAM_OPT}.h
${PROGRAM_OPT}.o: ${PROGRAM_OPT}.c ${PROGRAM_OPT}.h

debug.o: debug.c debug.h

#como compilar .o a partir de .c
.c.o:
	${CC} ${CFLAGS} -c $<

# Como gerar os ficheiros do gengetopt 
${PROGRAM_OPT}.h: ${PROGRAM_OPT}.ggo
	gengetopt < ${PROGRAM_OPT}.ggo --file-name=${PROGRAM_OPT}

clean:
	rm -f *.o core.* *~ ${PROGRAM} *.bak

docs: Doxyfile
	doxygen Doxyfile

Doxyfile:
	doxygen -g Doxyfile

indent:
	dos2unix *.c *.h
	indent ${IFLAGS} *.c *.h
