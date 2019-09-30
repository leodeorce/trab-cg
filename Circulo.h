/*
 * Arquivo: Circulo.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#ifndef CIRCULO_H
#define CIRCULO_H

#include <GL/glut.h>
#include "Figura.h"

class Circulo : public Figura {
	GLint step;
	GLfloat raio = 0.0f;
public:
	Circulo(GLfloat, GLfloat, GLfloat);
	GLfloat getRaio(void) const;
	void setRaio(GLfloat);
	void Desenhar(void) const;
};

#endif /* CIRCULO_H */
