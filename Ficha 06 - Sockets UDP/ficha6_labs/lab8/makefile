# Makefile que facilmente se adapta a qualquer tipo de exercicio client/servidor
# author Vitor Carreira (atualizado por rui.ferreira)
# date 2017-10-29
#

# Bibliotecas a incluir
LIBS=#-pthread #-lm

# Flags para o compilador
CFLAGS=-Wall -W -g -Wmissing-prototypes -ggdb #-pg
# Linker flags
LDFLAGS=#-pg

# Flags para a indentacao de codigo
# IFLAGS=-br -brs -npsl -ce -cli4
IFLAGS=-linux -brs -brf -br

# nome do executavel
SERVER=server

# Nome do ficheiro de opcoes do gengetopt (caso exista)
SERVER_ARGS=server_args

# Lista de objectos necessarios para criar o executavel
SERVER_OBJS=${SERVER_ARGS}.o server.o debug.o memory.o

# nome do executavel
CLIENT=client

# Nome do ficheiro de opcoes do gengetopt (caso exista)
CLIENT_ARGS=client_args

# Lista de objectos necessarios para criar o executavel
CLIENT_OBJS=${CLIENT_ARGS}.o client.o debug.o memory.o

.PHONY: clean

all: ${SERVER} ${CLIENT}

# compilar com depuracao
depuracao: CFLAGS += -D SHOW_DEBUG
depuracao: ${SERVER} ${CLIENT}

${SERVER}: ${SERVER_OBJS}
	${CC} -o $@ ${SERVER_OBJS} ${LIBS}

${CLIENT}: ${CLIENT_OBJS}
	${CC} -o $@ ${CLIENT_OBJS} ${LIBS}

# Dependencias
server.o: server.c debug.h memory.h common.h ${SERVER_ARGS}.h
${SERVER_ARGS}.o: ${SERVER_ARGS}.c ${SERVER_ARGS}.h

client.o: client.c debug.h memory.h common.h ${CLIENT_ARGS}.h
${CLIENT_ARGS}.o: ${CLIENT_ARGS}.c ${CLIENT_ARGS}.h

debug.o: debug.c debug.h
memory.o: memory.c memory.h

#como compilar .o a partir de .c
.c.o:
	${CC} ${CFLAGS} -c $<

# Como gerar os ficheiros do gengetopt
${SERVER_ARGS}.c ${SERVER_ARGS}.h: ${SERVER_ARGS}.ggo
	gengetopt < ${SERVER_ARGS}.ggo --file-name=${SERVER_ARGS}

${CLIENT_ARGS}.c ${CLIENT_ARGS}.h: ${CLIENT_ARGS}.ggo
	gengetopt < ${CLIENT_ARGS}.ggo --file-name=${CLIENT_ARGS}

clean:
	rm -f *.o core.* *~ .*~ ${SERVER} ${CLIENT} *.bak ${SERVER_ARGS}.h ${SERVER_ARGS}.c ${CLIENT_ARGS}.h ${CLIENT_ARGS}.c

docs: Doxyfile
	doxygen Doxyfile

Doxyfile:
	doxygen -g Doxyfile

indent:
	dos2unix *.c *.h
	indent ${IFLAGS} *.c *.h

# entry to run the pmccabe utility (computes the "complexity" of the code)
# Requires the application pmccabe (sudo apt-get install pmccabe)
pmccabe:
	pmccabe -v *.c

# entry to run the cppcheck tool
cppcheck:
	cppcheck --enable=all --verbose *.c *.h
