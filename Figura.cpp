/*
 * Arquivo: Figura.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC4
*/

#include "Figura.h"

Figura:: Figura(GLfloat corR, GLfloat corG, GLfloat corB)
{
	this->corR = corR;
	this->corG = corG;
	this->corB = corB;
}

void Figura:: setCorR(GLfloat corR) { this->corR = corR; }
void Figura:: setCorG(GLfloat corG) { this->corG = corG; }
void Figura:: setCorB(GLfloat corB) { this->corB = corB; }

GLfloat Figura:: getCorR(void) const { return corR; }
GLfloat Figura:: getCorG(void) const { return corG; }
GLfloat Figura:: getCorB(void) const { return corB; }
