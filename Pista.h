/*
 * Arquivo: Pista.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC4
*/

#ifndef PISTA_H
#define PISTA_H

#include "Figura.h"

class Pista : public Figura {

protected:
	GLfloat x1 = 0.0f;
	GLfloat y1 = 0.0f;
    GLfloat x2 = 0.0f;
	GLfloat y2 = 0.0f;
	
public:
	Pista(GLfloat, GLfloat, GLfloat);
	GLfloat getX1(void) const;
	GLfloat getY1(void) const;
	GLfloat getX2(void) const;
	GLfloat getY2(void) const;
	void setX1(GLfloat);
	void setY1(GLfloat);
	void setX2(GLfloat);
	void setY2(GLfloat);
	void Desenhar(void) const;
};

#endif /* PISTA_H */
