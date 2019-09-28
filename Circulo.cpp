/*
 * Arquivo: Circulo.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#include <cmath>
#include "Circulo.h"

Circulo:: Circulo(GLfloat corR, GLfloat corG, GLfloat corB)
	: Elemento(corR, corG, corB) { }

GLint Circulo:: getCX(void) const { return cX; }
GLint Circulo:: getCY(void) const { return cY; }
GLint Circulo:: getRaio(void) const { return raio; }

void Circulo:: setCX(GLint cX) { this->cX = cX; }
void Circulo:: setCY(GLint cY) { this->cY = cY; }

void Circulo:: setRaio(GLint raio) {
	this->raio = raio;
	step = round((9.0f * (float) raio / 70.0f) + (108.0f / 7.0f));
}

void Circulo:: Desenha(void) const {
	
	glColor3f(corR, corG, corB);
	glBegin(GL_POLYGON);
	
		GLint i;
		GLint voltaCompleta = 360;
		
		for(i = 0; i < voltaCompleta; i += voltaCompleta / step) {
			
			GLfloat angulo = 2.0f * 3.141593f * ((GLfloat) i / voltaCompleta);
			GLfloat x = raio * cos(angulo);
			GLfloat y = raio * sin(angulo);
			
			glVertex2f(x, y);
		}
		
	glEnd();
}
