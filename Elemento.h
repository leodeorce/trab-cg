/*
 * Arquivo: Elemento.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC3
*/

#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <GL/glut.h>
#include "Circulo.h"

class Elemento {
	Circulo* circulo;
	GLfloat gX = 0.0f;
	GLfloat gY = 0.0f;
public:
	void setGX(GLfloat);
	void setGY(GLfloat);
	void setCirculo(Circulo*);
	GLfloat getGX(void) const;
	GLfloat getGY(void) const;
	Circulo* getCirculo(void) const;
	void Desenhar(void);
	void MoverX(GLfloat);
	void MoverY(GLfloat);
	~Elemento();
};

#endif /* ELEMENTO_H */
