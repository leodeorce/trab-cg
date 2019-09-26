/*
 * Arquivo: Jogador.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#ifndef JOGADOR_H
#define JOGADOR_H

#include <GL/glut.h>
#include "Circulo.h"

using namespace std;

class Jogador {
	GLfloat multiplicador;
	Circulo* circulo;
public:
	void setMultiplicador(GLfloat);
	void setCirculo(Circulo&);
	GLfloat getMultiplicador(void) const;
	Circulo* getCirculo(void) const;
	~Jogador();
};

#endif /* JOGADOR_H */
