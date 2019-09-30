### Makefile ###

# Leonardo Deorce Lima de Oliveira
# TC2 - Computacao Grafica - 2019/2

CC = g++

FLAGS = -lGL -lGLU -lglut

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
