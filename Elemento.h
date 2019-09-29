/*
 * Arquivo: Elemento.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <GL/glut.h>
#include "Circulo.h"

class Elemento {
	Circulo* circulo;
	GLint gX = 0;
	GLint gY = 0;
public:
	void setCirculo(Circulo*);
	void Desenhar(void);
	void setGX(GLint);
	void setGY(GLint);
	void MoverX(GLfloat);
	void MoverY(GLfloat);
	~Elemento();
};

#endif /* ELEMENTO_H */
