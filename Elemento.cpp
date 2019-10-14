/*
 * Arquivo: Elemento.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC3
*/

#include "Elemento.h"

void Elemento:: setGX(GLfloat gX) {
	this->gX = gX;
}

void Elemento:: setGY(GLfloat gY) {
	this->gY = gY;
}

void Elemento:: setCirculo(Circulo* circulo) {
	this->circulo = circulo;
}

GLfloat Elemento:: getGX(void) const {
	return gX;
}

GLfloat Elemento:: getGY(void) const {
	return gY;
}

Circulo* Elemento:: getCirculo(void) const {
	return circulo;
}

void Elemento:: Desenhar(void) {
	
	glPushMatrix();
	
	glTranslatef(gX, gY, 0.0f);
	circulo->Desenhar();
	
	glPopMatrix();
}

void Elemento:: MoverX(GLfloat dX) {
	gX = gX + dX;
}

void Elemento:: MoverY(GLfloat dY) {
	gY = gY + dY;
}

Elemento:: ~Elemento() {
	delete circulo;
}
