# Easily adaptable makefile
# Note: remove comments (#) to activate some features
#
# author Vitor Carreira
# date 2010-09-26 / updated: 2016-03-15 (Patricio)

# Libraries to include (if any)
LIBS=-lm #-pthread

# Compiler flags
CFLAGS=-Wall -Wextra -ggdb -std=c11 -pedantic -D_POSIX_C_SOURCE=200809L #-pg

# Linker flags
LDFLAGS=#-pg

# Indentation flags
# IFLAGS=-br -brs -brf -npsl -ce -cli4 -bli4 -nut
IFLAGS=-linux -brs -brf -br

# name of the server executable
SERVER=recebe_pacote_UDP

# Prefix for the server's gengetopt file
SERVER_OPT=server_opt

# Object files required to build the server executable
SERVER_OBJS=server.o debug.o memory.o $(SERVER_OPT).o

# name of the client executable
CLIENT=envia_pacote_UDP

# Prefix for the client's gengetopt file
CLIENT_OPT=client_opt

# Object files required to build the client executable
CLIENT_OBJS=client.o debug.o memory.o $(CLIENT_OPT).o

# Specifies which targets are not files
.PHONY: clean all docs indent debugon

all: $(SERVER) $(CLIENT)

# activate DEBUG, defining the SHOW_DEBUG macro
debugon: CFLAGS += -D SHOW_DEBUG -g
debugon: $(SERVER) $(CLIENT)

# activate optimization (-O...)
OPTIMIZE_FLAGS=-O2 # possible values (for gcc): -O2 -O3 -Os -Ofast
optimize: CFLAGS += $(OPTIMIZE_FLAGS)
optimize: LDFLAGS += $(OPTIMIZE_FLAGS)
optimize: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJS)
	$(CC) -o $@ $(SERVER_OBJS) $(LIBS)

$(CLIENT): $(CLIENT_OBJS)
	$(CC) -o $@ $(CLIENT_OBJS) $(LIBS)

# Dependencies
server.o: server.c debug.h memory.h common.h $(SERVER_OPT).h
$(SERVER_OPT).o: $(SERVER_OPT).c $(SERVER_OPT).h

client.o: client.c debug.h memory.h common.h $(CLIENT_OPT).h
$(CLIENT_OPT).o: $(CLIENT_OPT).c $(CLIENT_OPT).h

debug.o: debug.c debug.h
memory.o: memory.c memory.h

# disable warnings from gengetopt generated files
$(SERVER_OPT).o: $(SERVER_OPT).c $(SERVER_OPT).h
	$(CC) -ggdb -std=c11 -pedantic -c $<

$(CLIENT_OPT).o: $(CLIENT_OPT).c $(CLIENT_OPT).h
	$(CC) -ggdb -std=c11 -pedantic -c $<


#how to create an object file (.o) from C file (.c)
.c.o:
	$(CC) $(CFLAGS) -c $<

# Generates command line arguments code from gengetopt configuration file
$(SERVER_OPT).c $(SERVER_OPT).h: $(SERVER_OPT).ggo
	gengetopt < $(SERVER_OPT).ggo --file-name=$(SERVER_OPT)

$(CLIENT_OPT).c $(CLIENT_OPT).h: $(CLIENT_OPT).ggo
	gengetopt < $(CLIENT_OPT).ggo --file-name=$(CLIENT_OPT)

clean:
	rm -f *.o core.* *~ .*~ $(SERVER) $(CLIENT) *.bak $(SERVER_OPT).h $(SERVER_OPT).c $(CLIENT_OPT).h $(CLIENT_OPT).c

docs: Doxyfile
	doxygen Doxyfile

# entry to create the list of dependencies
depend:
	$(CC) -MM *.c

# entry 'indent' requires the application indent (sudo apt-get install indent)
indent:
	indent $(IFLAGS) *.c *.h

# entry to run the pmccabe utility (computes the "complexity" of the code)
# Requires the application pmccabe (sudo apt-get install pmccabe)
pmccabe:
	pmccabe -v *.c

# entry to run the cppcheck tool
cppcheck:
	cppcheck --enable=all --verbose *.c *.h
