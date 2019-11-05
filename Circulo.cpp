/*
 * Arquivo: Circulo.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC4
*/

#include <cmath>
#include "Circulo.h"

Circulo:: Circulo(GLfloat corR, GLfloat corG, GLfloat corB)
	: Figura(corR, corG, corB) {
}

GLfloat Circulo:: getRaio(void) const {
	return raio;
}

GLint Circulo:: getStep(void) const {
	return step;
}

GLfloat Circulo:: getRaioInicial(void) const {
	return raioInicial;
}

void Circulo:: setRaio(GLfloat raio) {
	this->raio = raio;
	step = round((9.0f * (float) raio / 70.0f) + (108.0f / 7.0f));
}

void Circulo:: setStep(GLint step) {
	this->step = step;
}

void Circulo:: setRaioInicial(GLfloat raioInicial) {
	this->raioInicial = raioInicial;
}

void Circulo:: Desenhar(void) const {
	
	glColor3f(corR, corG, corB);
	glBegin(GL_POLYGON);
	
		GLint i;
		GLint voltaCompleta = 360;
		
		for(i = voltaCompleta; i > 0; i -= voltaCompleta / step) {
			
			GLfloat angulo = 2.0f * 3.141593f * ((GLfloat) i / voltaCompleta);
			GLfloat x = raio * cos(angulo);
			GLfloat y = raio * sin(angulo);
			
			glVertex2f(x, y);
		}
		
	glEnd();
}

bool Circulo:: ExisteConflito(GLfloat raio, GLfloat x, GLfloat y, GLfloat gX, GLfloat gY) const {
	
	GLfloat distCentros = sqrt(pow(gX - x, 2) + pow(gY - y, 2));
	GLfloat distCentrosLimite = this->raio + raio;
	
	if(distCentros < distCentrosLimite) {
		return true;
	} else {
		return false;
	}
}
