/*
 * Arquivo: Circulo.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#ifndef CIRCULO_H
#define CIRCULO_H

#include <GL/glut.h>
#include "Elemento.h"

class Circulo : public Elemento {
	GLint raio;
	GLint cX;
	GLint cY;
public:
	Circulo(GLfloat, GLfloat, GLfloat);
	GLint getRaio(void) const;
	GLint getCX(void) const;
	GLint getCY(void) const;
	void setRaio(GLint);
	void setCX(GLint);
	void setCY(GLint);
	void Desenha(void) const;
};

#endif /* CIRCULO_H */
