/*
 * Arquivo: Pista.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC3
*/

#include "Pista.h"

Pista:: Pista(GLfloat corR, GLfloat corG, GLfloat corB)
	: Figura(corR, corG, corB) { }

GLfloat Pista:: getX1(void) const { return x1; }
GLfloat Pista:: getY1(void) const { return y1; }
GLfloat Pista:: getX2(void) const { return x2; }
GLfloat Pista:: getY2(void) const { return y2; }

void Pista:: setX1(GLfloat x1) { this->x1 = x1; }
void Pista:: setY1(GLfloat y1) { this->y1 = y1; }
void Pista:: setX2(GLfloat x2) { this->x2 = x2; }
void Pista:: setY2(GLfloat y2) { this->y2 = y2; }

void Pista:: Desenhar(void) const {
	
	glColor3f(corR, corG, corB);
	
	glBegin(GL_LINES);
	
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		
	glEnd();
}