/*
 * Arquivo: Arena.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#ifndef ARENA_H
#define ARENA_H

#include <GL/glut.h>
#include <string>
#include "Circulo.h"

using namespace std;

class Arena {
	string arquivo;
	Circulo* circulo;
public:
	void setNomeArquivo(string);
	void setCirculo(Circulo&);
	string getNomeArquivo(void) const;
	Circulo* getCirculo(void) const;
	void Desenha(void) const;
	~Arena();
};

#endif /* ARENA_H */
