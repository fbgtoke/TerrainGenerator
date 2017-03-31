CC = g++

INC = inc
SRC = src
BIN = bin

#LIBS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio
LIBS =

CFLAGS = -std=c++14 -Wall -I$(INC)
LFLAGS = $(LIBS)

_DEPS = 
DEPS  =$(patsubst %,$(INC)/%,$(_DEPS)) 

_OBJ = main.o terrain.o terrainchunk.o terrainchunkloader.o terrainchunkgenerator.o simplexgenerator.o
OBJ  = $(patsubst %,$(BIN)/%,$(_OBJ))

OUT  = main

$(BIN)/%.o: $(SRC)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUT): $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS)

.PHONY: clean

clean:
	rm -rf $(BIN)/*.o $(OUT)
