/*
 * Arquivo: Elemento.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#include "Elemento.h"

Elemento:: Elemento(GLfloat corR, GLfloat corG, GLfloat corB) {
	this->corR = corR;
	this->corG = corG;
	this->corB = corB;
}

GLfloat Elemento:: getCorR(void) const { return corR; }
GLfloat Elemento:: getCorG(void) const { return corG; }
GLfloat Elemento:: getCorB(void) const { return corB; }

void Elemento:: setCorR(GLfloat corR) { this->corR = corR; }
void Elemento:: setCorG(GLfloat corG) { this->corG = corG; }
void Elemento:: setCorB(GLfloat corB) { this->corB = corB; }
