/*
 * Arquivo: Arena.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC4
*/

#include <cmath>
#include "Arena.h"

using namespace std;

void Arena:: setNomeArquivo(string arquivo) {
	this->arquivo = arquivo;
}

string Arena:: getNomeArquivo(void) const {
	return arquivo;
}

void Arena:: DesenharCirculo(void) {
	this->Desenhar();
}

void Arena:: DesenharContorno(void) {
	
	Circulo* circuloArena = this->getCirculo();
	GLfloat raio = circuloArena->getRaio();
	GLint step = circuloArena->getStep();
	GLint gX = this->getGX();
	GLint gY = this->getGY();
	
	glPushMatrix();
	
		glTranslatef(gX, gY, 0.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
				
		glBegin(GL_TRIANGLE_STRIP);
		
			int i;
			int voltaCompleta = 360;
			
			for(i = 0; i <= voltaCompleta; i += voltaCompleta / (4.0f * step)) {
				
				GLfloat angulo = 2.0f * 3.141593f * ((GLfloat) i / voltaCompleta);
				
				GLfloat x = raio * cos(angulo);
				GLfloat y = raio * (- sin(angulo));
				glVertex2f(x, y);
				
				x = 2.0f * raio * cos(angulo);
				y = 2.0f * raio * (- sin(angulo));
				glVertex2f(x, y);
			}
			
		glEnd();
	
	glPopMatrix();
}

bool Arena:: ExisteConflito(GLfloat raio, GLfloat x, GLfloat y, bool objetoSairArena) const {
	
	GLfloat gX = this->getGX();
	GLfloat gY = this->getGY();
	Circulo* circuloArena = this->getCirculo();
	
	GLfloat distCentros = sqrt(pow(gX - x, 2) + pow(gY - y, 2));
	
	GLfloat multiplicador = - 1.0f;
	if(objetoSairArena == true) {
		multiplicador = 1.0f;
	}
	
	GLfloat distCentrosLimite = circuloArena->getRaio() + (multiplicador * raio);
	
	if(distCentros > distCentrosLimite) {
		return true;
	} else {
		return false;
	}
}