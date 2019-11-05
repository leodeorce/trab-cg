/*
 * Arquivo: Elemento.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC4
*/

#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <GL/glut.h>
#include "Circulo.h"

class Elemento {

protected:
	Circulo* circulo;
	GLfloat gXInicial = 0.0f;
	GLfloat gX = 0.0f;
	GLfloat gYInicial = 0.0f;
	GLfloat gY = 0.0f;
	
public:
	void setGXInicial(GLfloat);
	void setGX(GLfloat);
	void setGYInicial(GLfloat);
	void setGY(GLfloat);
	void setCirculo(Circulo*);
	GLfloat getGXInicial(void) const;
	GLfloat getGX(void) const;
	GLfloat getGYInicial(void) const;
	GLfloat getGY(void) const;
	Circulo* getCirculo(void) const;
	void Desenhar(void);
	void MoverX(GLfloat);
	void MoverY(GLfloat);
	bool ExisteConflito(GLfloat, GLfloat, GLfloat) const;
	~Elemento();
};

#endif /* ELEMENTO_H */
