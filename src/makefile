CC=gcc
CFLAGS_DEBUG=  -O0 -g3
CFLAGS_RELEASE= -O3

LIBS= -lSDL -lSDL_ttf
CFLAGS= -pedantic -W -Wall -std=c99 $(CFLAGS_DEBUG)

OBJS=main.o gui.o game.o
BIN= applecacti.exe


all: $(BIN)

$(BIN): $(OBJS)
	gcc $^ -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o *~
