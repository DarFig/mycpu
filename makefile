OBJ = ./c_modules/bin/main.o
BIN = ./c_modules/bin/main
OBJT = ./herramientas/interpretar.o
SRC = ./c_modules/src/main.c
SRCT = ./herramientas/interpretar.cpp

all: build tools

run:
	$(BIN)

build: $(BIN)
	g++ -std=c++11 $(SRC) -o $(BIN)

tools: $(BINT)
	g++ -std=c++11 -O3 $(SRCT) -o ./herramientas/interpretar

clean:
	rm -f $(OBJ)
	rm -f $(OBJT)

help:
	@echo ---- make       -- lanza las ordenes build y tools
	@echo ---- make build -- construye ./c_modules/bin/main
	@echo ---- make tools -- construye las herramientas, por ahora ./herramientas/interpretar
	@echo ---- make run   -- lanza ./c_modules/ bin/main
