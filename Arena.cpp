/*
 * Arquivo: Arena.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC4
*/

#include <cmath>
#include "Arena.h"

using namespace std;

void Arena:: setNomeArquivo(string arquivo) { this->arquivo = arquivo; }

string Arena:: getNomeArquivo(void) const { return arquivo; }

void Arena:: DesenharCirculo(void)
{
	this->Desenhar();
}

void Arena:: DesenharContorno(void)
{
	Circulo* circuloArena = this->getCirculo();
	GLfloat raio = circuloArena->getRaio();
	GLint step = circuloArena->getStep();
	GLint gX = this->getGX();
	GLint gY = this->getGY();
	
	glPushMatrix();
	
		glTranslatef(gX, gY, 0.0);
		glColor3f(0.0, 0.0, 0.0);
				
		glBegin(GL_TRIANGLE_STRIP);
		
			int i;
			int voltaCompleta = 360;
			
			for(i = 0; i <= voltaCompleta; i += voltaCompleta / (4.0 * step)) {
				
				GLfloat angulo = 2.0 * 3.141593 * ((GLfloat) i / voltaCompleta);
				
				GLfloat x = raio * cos(angulo);
				GLfloat y = raio * (- sin(angulo));
				glVertex2f(x, y);
				
				x = 2.0 * raio * cos(angulo);
				y = 2.0 * raio * (- sin(angulo));
				glVertex2f(x, y);
			}
			
		glEnd();
	
	glPopMatrix();
}
