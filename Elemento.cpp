/*
 * Arquivo: Elemento.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#include "Elemento.h"

Elemento:: Elemento(float& corR, float& corG, float& corB) {
	this->corR = corR;
	this->corG = corG;
	this->corB = corB;
}

float Elemento:: getCorR(void) const { return corR; }
float Elemento:: getCorG(void) const { return corG; }
float Elemento:: getCorB(void) const { return corB; }

void Elemento:: setCorR(float& corR) { this->corR = corR; }
void Elemento:: setCorG(float& corG) { this->corG = corG; }
void Elemento:: setCorB(float& corB) { this->corB = corB; }
