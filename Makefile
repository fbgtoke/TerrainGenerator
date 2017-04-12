CC = g++

INC = inc
SRC = src
BIN = bin

LIBS = -lGLEW -lglut -lGL

CFLAGS = -std=c++14 -Wall -I$(INC)
LFLAGS = $(LIBS)

_DEPS = 
DEPS  =$(patsubst %,$(INC)/%,$(_DEPS)) 

_OBJ = main.o simplex.o game.o shaderloader.o terrain.o terrainchunk.o camera.o
OBJ  = $(patsubst %,$(BIN)/%,$(_OBJ))

OUT  = simplex

$(BIN)/%.o: $(SRC)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUT): $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS)

.PHONY: clean

clean:
	rm -rf $(BIN)/*.o $(OUT)
