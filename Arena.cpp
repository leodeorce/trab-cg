/*
 * Arquivo: Arena.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC3
*/

#include <iostream>
#include <cmath>
#include "Arena.h"

using namespace std;

void Arena:: setNomeArquivo(string arquivo) {
	this->arquivo = arquivo;
}

string Arena:: getNomeArquivo(void) const {
	return arquivo;
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