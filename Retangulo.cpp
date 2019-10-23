/*
 * Arquivo: Retangulo.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC3
*/

#include <cmath>
#include "Retangulo.h"

Retangulo:: Retangulo(GLfloat corR, GLfloat corG, GLfloat corB)
	: Figura(corR, corG, corB) {
}

GLfloat Retangulo:: getLargura(void) const {
	return largura;
}

GLfloat Retangulo:: getAltura(void) const {
	return altura;
}

void Retangulo:: setLargura(GLfloat largura) {
	this->largura = largura;
}

void Retangulo:: setAltura(GLfloat altura) {
	this->altura = altura;
}

void Retangulo:: Desenhar(void) const {
	
	GLfloat x = largura / 2.0f;
	GLfloat y = altura / 2.0f;
	
	glColor3f(corR, corG, corB);
	glBegin(GL_QUADS);
	
		glVertex2f( +x, +y);
		glVertex2f( +x, -y);
		glVertex2f( -x, -y);
		glVertex2f( -x, +y);
		
	glEnd();
}

void Retangulo:: DesenharCisalhado(void) const {
	
	GLfloat x = largura / 2.0f;
	GLfloat y = altura / 2.0f;
	
	glColor3f(corR, corG, corB);
	glBegin(GL_POLYGON);
		
		glVertex2f( +x, + 0.25f * y);
		glVertex2f( +x, - 0.75f * y);
		glVertex2f( -x, - 0.25f * y);
		glVertex2f( -x, + 0.75f * y);
		
	glEnd();
}

void Retangulo:: DesenharHelice(void) const {
	
	GLfloat x = largura / 2.0f;
	GLfloat y = altura / 2.0f;
	
	glColor3f(corR, corG, corB);
	glBegin(GL_POLYGON);
	
		glVertex2f( -x, -y);
		glVertex2f( -x, +y);
		glVertex2f( 0.0f, 0.0f);
		
	glEnd();
	glBegin(GL_POLYGON);
	
		glVertex2f( +x, -y);
		glVertex2f( 0.0f, 0.0f);
		glVertex2f( +x, +y);
		
	glEnd();
}