/*
 * Arquivo: Inimigo.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC3
 */

#include <cmath>
#include "Inimigo.h"

bool Inimigo:: ExisteConflito(GLfloat raio, GLfloat x, GLfloat y) {
	
	GLfloat gX = this->getGX();
	GLfloat gY = this->getGY();
	Circulo* circulo = this->getCirculo();
	
	GLfloat distCentros = sqrt(pow(gX - x, 2) + pow(gY - y, 2));
	
	if(distCentros > circulo->getRaio() + raio) {
		return false;
	} else {
		return true;
	}
}
