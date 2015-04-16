CC=gcc
CFLAGS_DEBUG=  -O0 -g3
CFLAGS_RELEASE= -O3

LIBS= -lSDL -lSDL_ttf
CFLAGS= -pedantic -W -Wall $(CFLAGS_DEBUG)

OBJS=main.o 
OBJnames=main.o 
BIN= applecacti


all: $(BIN)

$(BIN): $(OBJS)
	gcc $(OBJnames) -o $@ $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -r *.o *~ */*~
