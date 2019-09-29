/*
 * Arquivo: Elemento.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#include "Elemento.h"

void Elemento:: setCirculo(Circulo* circulo) {
	this->circulo = circulo;
}

void Elemento:: Desenhar(void) {
	
	glPushMatrix();
	
	glTranslatef(gX, gY, 0.0f);
	circulo->Desenhar();
	
	glPopMatrix();
}

void Elemento:: setGX(GLint gX) {
	this->gX = gX;
}

void Elemento:: setGY(GLint gY) {
	this->gY = gY;
}

void Elemento:: MoverX(GLfloat dX) {
	gX = gX + (GLint) dX;
}

void Elemento:: MoverY(GLfloat dY) {
	gY = gY + (GLint) dY;
}

Elemento:: ~Elemento() {
	delete circulo;
}
