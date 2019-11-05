/*
 * Arquivo: Retangulo.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC4
*/

#ifndef RETANGULO_H
#define RETANGULO_H

#include <GL/glut.h>
#include "Figura.h"

class Retangulo : public Figura {

protected:
	GLfloat largura = 1.0f;
	GLfloat altura = 1.0f;
	
public:
	Retangulo(GLfloat, GLfloat, GLfloat);
	GLfloat getLargura(void) const;
	GLfloat getAltura(void) const;
	void setLargura(GLfloat);
	void setAltura(GLfloat);
	void Desenhar(void) const;
	void DesenharCisalhado(void) const;
	void DesenharHelice(void) const;
};

#endif /* RETANGULO_H */
