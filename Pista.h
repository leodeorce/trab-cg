/*
 * Arquivo: Pista.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#ifndef PISTA_H
#define PISTA_H

#include "Figura.h"

class Pista : public Figura {
	GLint x1 = 0;
	GLint y1 = 0;
    GLint x2 = 0;
	GLint y2 = 0;
public:
	Pista(GLfloat, GLfloat, GLfloat);
	GLint getX1(void) const;
	GLint getY1(void) const;
	GLint getX2(void) const;
	GLint getY2(void) const;
	void setX1(GLint);
	void setY1(GLint);
	void setX2(GLint);
	void setY2(GLint);
	void Desenhar(void) const;
};

#endif /* PISTA_H */
