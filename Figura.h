/*
 * Arquivo: Figura.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC4
*/

#ifndef FIGURA_H
#define FIGURA_H

#include <GL/glut.h>

enum Cor {
	RED = 0,
	GREEN = 1,
	BLUE = 2,
	ORANGE = 3
};

class Figura {
	
protected:
	GLfloat corR;
	GLfloat corG;
	GLfloat corB;
	
public:
	Figura(GLfloat, GLfloat, GLfloat);
	GLfloat getCorR(void) const;
	GLfloat getCorG(void) const;
	GLfloat getCorB(void) const;
	void setCorR(GLfloat);
	void setCorG(GLfloat);
	void setCorB(GLfloat);
};

#endif /* FIGURA_H */
