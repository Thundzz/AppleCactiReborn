CC=gcc
CFLAGS_DEBUG=  -O0 -g3
CFLAGS_RELEASE= -O3

LIBS= -lSDL -lSDL_ttf
CFLAGS= -pedantic -W -Wall -std=c99 $(CFLAGS_DEBUG)

OBJS=main.o gui/gui.o game/game.o game/player.o game/cursor.o game/tile.o
OBJnames=main.o gui.o game.o player.o cursor.o tile.o
BIN= applecacti.exe


all: $(BIN)

$(BIN): $(OBJS)
	gcc $(OBJnames) -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o *~
