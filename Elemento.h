/*
 * Arquivo: Elemento.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <GL/glut.h>

enum Cor {
	RED = 0,
	GREEN = 1,
	BLUE = 2,
	ORANGE = 3
};

class Elemento {
	GLfloat corR;
	GLfloat corG;
	GLfloat corB;
public:
	Elemento(GLfloat&, GLfloat&, GLfloat&);
	Elemento() { }
	GLfloat getCorR(void) const;
	GLfloat getCorG(void) const;
	GLfloat getCorB(void) const;
	void setCorR(GLfloat&);
	void setCorG(GLfloat&);
	void setCorB(GLfloat&);
};

#endif /* ELEMENTO_H */
