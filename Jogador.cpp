/*
 * Arquivo: Jogador.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#include "Jogador.h"

void Jogador:: setMultiplicador(GLfloat multiplicador) { this->multiplicador = multiplicador; }
void Jogador:: setCirculo(Circulo* circulo) { this->circulo = circulo; }

GLfloat Jogador:: getMultiplicador(void) const { return multiplicador; }
Circulo* Jogador:: getCirculo(void) const { return circulo; }

void Jogador:: Desenha(void) const {
	
	glPushMatrix();
	
	glTranslatef(circulo->getCX(), circulo->getCY(), 0.0f);
	circulo->Desenha();
	
	glPopMatrix();
}

Jogador:: ~Jogador() {
	delete circulo;
}
