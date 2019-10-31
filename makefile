### Makefile ###

# Leonardo Deorce Lima de Oliveira
# TC3 - Computacao Grafica - 2019/2

CC = g++

LFLAGS = -lGL -lGLU -lglut

CFLAGS = -std=c++11

FONTES = $(wildcard *.cpp)

OBJETOS = $(FONTES:.cpp=.o)

EXECUTAVEL = trabalhocg

all: $(EXECUTAVEL)

$(EXECUTAVEL): $(OBJETOS)
	$(CC) $^ $(LFLAGS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^

clean:
	rm -rf *.o

run:
	./$(EXECUTAVEL) ../cfg/

