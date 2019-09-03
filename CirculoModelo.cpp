/*
 * Arquivo: CirculoModelo.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC1
*/

#include "CirculoModelo.h"

float CirculoModelo:: getCorSobreposicaoR() const { return corSobreposicaoR; }
float CirculoModelo:: getCorSobreposicaoG() const { return corSobreposicaoG; }
float CirculoModelo:: getCorSobreposicaoB() const { return corSobreposicaoB; }

void CirculoModelo:: setCorSobreposicaoR(float& corSobreposicaoR) { this->corSobreposicaoR = corSobreposicaoR; }
void CirculoModelo:: setCorSobreposicaoG(float& corSobreposicaoG) { this->corSobreposicaoG = corSobreposicaoG; }
void CirculoModelo:: setCorSobreposicaoB(float& corSobreposicaoB) { this->corSobreposicaoB = corSobreposicaoB; }
