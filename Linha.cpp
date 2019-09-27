/*
 * Arquivo: Linha.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#include "Linha.h"

Linha:: Linha(GLfloat corR, GLfloat corG, GLfloat corB)
	: Elemento(corR, corG, corB) { }

GLint Linha:: getX1(void) const { return x1; }
GLint Linha:: getY1(void) const { return y1; }
GLint Linha:: getX2(void) const { return x2; }
GLint Linha:: getY2(void) const { return y2; }

void Linha:: setX1(GLint x1) { this->x1 = x1; }
void Linha:: setY1(GLint y1) { this->y1 = y1; }
void Linha:: setX2(GLint x2) { this->x2 = x2; }
void Linha:: setY2(GLint y2) { this->y2 = y2; }

void Linha:: Desenha(void) const {
	glColor3f(corR, corG, corB);
	glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	glEnd();
}