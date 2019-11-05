/*
 * Arquivo: Elemento.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC4
*/

#include "Elemento.h"

void Elemento:: setGXInicial(GLfloat gXInicial) {
	this->gXInicial = gXInicial;
}

void Elemento:: setGX(GLfloat gX) {
	this->gX = gX;
}

void Elemento:: setGYInicial(GLfloat gYInicial) {
	this->gYInicial = gYInicial;
}

void Elemento:: setGY(GLfloat gY) {
	this->gY = gY;
}

void Elemento:: setCirculo(Circulo* circulo) {
	this->circulo = circulo;
}

GLfloat Elemento:: getGXInicial(void) const {
	return gXInicial;
}

GLfloat Elemento:: getGX(void) const {
	return gX;
}

GLfloat Elemento:: getGYInicial(void) const {
	return gYInicial;
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

bool Elemento:: ExisteConflito(GLfloat raio, GLfloat x, GLfloat y) const {
	return circulo->ExisteConflito(raio, x, y, gX, gY);
}

Elemento:: ~Elemento() {
	delete circulo;
}
