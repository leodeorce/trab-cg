/*
 * Arquivo: Circulo.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC4
*/

#ifndef CIRCULO_H
#define CIRCULO_H

#include <GL/glut.h>
#include "Figura.h"

class Circulo : public Figura {
	GLint step;
	GLfloat raioInicial = 0.0f;
	GLfloat raio = 0.0f;
public:
	Circulo(GLfloat, GLfloat, GLfloat);
	GLfloat getRaioInicial(void) const;
	GLfloat getRaio(void) const;
	GLint getStep(void) const;
	void setRaioInicial(GLfloat);
	void setRaio(GLfloat);
	void setStep(GLint);
	void Desenhar(void) const;
};

#endif /* CIRCULO_H */
