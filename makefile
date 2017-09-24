OBJ = ./c_modules/bin/main.o
BIN = ./c_modules/bin/main
OBJT = ./herramientas/interpretar.o
SRC = ./c_modules/src/main.c
SRCT = ./herramientas/interpretar.cpp

all: build tools

run:
	$(BIN)

build: $(OBJ)
	g++ $(SRC) -o $(BIN)

./c_modules/bin/%.o: ./c_modules/src/%.c
	g++ -c $< -O3 -o $@


tools: $(OBJT)
	g++ -std=c++11 -O3 $(SRCT) -o ./herramientas/interpretar

./herramientas/%.o: ./herramientas/%.c
	g++ -c $< -O3 -o $@

clean:
	rm -f $(OBJ)
	rm -f $(OBJT)
