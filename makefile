### Makefile ###

# Leonardo Deorce Lima de Oliveira
# TC1 - Computacao Grafica - 2019/2

CC = g++

FLAGS = -lGL -lGLU -lglut

PARAMETROS = /cfg/

FONTES = $(wildcard *.cpp)

OBJETOS = $(FONTES:.cpp=.o)

EXECUTAVEL = trabalhocg

all: $(EXECUTAVEL)

$(EXECUTAVEL): $(OBJETOS)
	$(CC) $^ $(FLAGS) -o $@

%.o: %.cpp
	$(CC) -c $^

clean:
	rm -rf *.o

run:
	./$(EXECUTAVEL) $(PARAMETROS)
