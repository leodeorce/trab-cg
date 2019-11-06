/*
 * Arquivo: Retangulo.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC4
*/

#include <cmath>
#include "Retangulo.h"

Retangulo:: Retangulo(GLfloat corR, GLfloat corG, GLfloat corB) : Figura(corR, corG, corB) { }

void Retangulo:: setLargura(GLfloat largura) { this->largura = largura; }
void Retangulo:: setAltura(GLfloat altura) { this->altura = altura; }

GLfloat Retangulo:: getLargura(void) const { return largura; }
GLfloat Retangulo:: getAltura(void) const { return altura; }

void Retangulo:: Desenhar(void) const
{
	GLfloat x = largura / 2.0;
	GLfloat y = altura / 2.0;
	
	glColor3f(corR, corG, corB);
	glBegin(GL_QUADS);
	
		glVertex2f( +x, +y);
		glVertex2f( +x, -y);
		glVertex2f( -x, -y);
		glVertex2f( -x, +y);
		
	glEnd();
}

void Retangulo:: DesenharCisalhado(void) const
{
	GLfloat x = largura / 2.0;
	GLfloat y = altura / 2.0;
	
	glColor3f(corR, corG, corB);
	glBegin(GL_POLYGON);
		
		glVertex2f( +x, + 0.25 * y);
		glVertex2f( +x, - 0.75 * y);
		glVertex2f( -x, - 0.25 * y);
		glVertex2f( -x, + 0.75 * y);
		
	glEnd();
}

void Retangulo:: DesenharHelice(void) const
{
	GLfloat x = largura / 2.0;
	GLfloat y = altura / 2.0;
	
	glColor3f(corR, corG, corB);
	glBegin(GL_POLYGON);
	
		glVertex2f( -x, -y);
		glVertex2f( -x, +y);
		glVertex2f( 0.0, 0.0);
		
	glEnd();
	glBegin(GL_POLYGON);
	
		glVertex2f( +x, -y);
		glVertex2f( 0.0, 0.0);
		glVertex2f( +x, +y);
		
	glEnd();
}