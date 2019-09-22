/*
 * Arquivo: Jogador.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#include "Jogador.h"

void Jogador:: setMultiplicador(float& multiplicador) { this->multiplicador = multiplicador; }
void Jogador:: setCirculo(Circulo& circulo) { this->circulo = new Circulo(circulo); }

float Jogador:: getMultiplicador(void) const { return multiplicador; }
Circulo* Jogador:: getCirculo(void) const { return circulo; }

Jogador:: ~Jogador() {
	delete circulo;
}
