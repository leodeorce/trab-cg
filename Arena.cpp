/*
 * Arquivo: Arena.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC3
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

bool Arena:: ExisteConflito(GLfloat raio, GLfloat x, GLfloat y) const {
	
	GLfloat gX = this->getGX();
	GLfloat gY = this->getGY();
	Circulo* circulo = this->getCirculo();
	
	GLfloat distCentros = sqrt(pow(gX - x, 2) + pow(gY - y, 2));
	
	if(distCentros > circulo->getRaio() - raio) {
		return true;
	} else {
		return false;
	}
}