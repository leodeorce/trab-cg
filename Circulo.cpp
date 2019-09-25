/*
 * Arquivo: Circulo.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#include "Circulo.h"

Circulo:: Circulo(float corR, float corG, float corB)
	: Elemento(corR, corG, corB) { }

Circulo:: Circulo(Circulo& circulo) {

	float corR = circulo.getCorR();
	float corG = circulo.getCorG();
	float corB = circulo.getCorB();
	int raio = circulo.getRaio();
	int cX = circulo.getCX();
	int cY = circulo.getCY();

	this->setCorR(corR);
	this->setCorG(corG);
	this->setCorB(corB);
	this->setRaio(raio);
	this->setCX(cX);
	this->setCY(cY);
}

int Circulo:: getRaio(void) const { return raio; }
int Circulo:: getCX(void) const { return cX; }
int Circulo:: getCY(void) const { return cY; }

void Circulo:: setRaio(int raio) { this->raio = raio; }
void Circulo:: setCX(int cX) { this->cX = cX; }
void Circulo:: setCY(int cY) { this->cY = cY; }
