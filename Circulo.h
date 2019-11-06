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

protected:
	GLint step;
	GLfloat raioInicial = 0.0;
	GLfloat raio = 0.0;
	
public:
	Circulo(GLfloat, GLfloat, GLfloat);
	void setRaioInicial(GLfloat);
	void setRaio(GLfloat);
	void setStep(GLint);
	GLfloat getRaioInicial(void) const;
	GLfloat getRaio(void) const;
	GLint getStep(void) const;
	bool ExisteConflito(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat) const;
	void Desenhar(void) const;
};

#endif /* CIRCULO_H */
