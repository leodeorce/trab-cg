/*
 * Arquivo: Jogador.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#include "Jogador.h"

void Jogador:: setMultiplicador(GLfloat multiplicador) {
	this->multiplicador = multiplicador;
}

GLfloat Jogador:: getMultiplicador(void) const {
	return multiplicador;
}

void Jogador:: Decolar(void) {
	
	if(Decolou == false) {
		
		GLfloat dX;
		GLfloat dY;
		
		MoverX(dX);
		MoverY(dY);
		
		// if()
		Decolou = true;
	}
}
