/*
 * Arquivo: Linha.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#include "Linha.h"

Linha:: Linha(float corR, float corG, float corB)
	: Elemento(corR, corG, corB) { }

int Linha:: getX1(void) const { return x1; }
int Linha:: getY1(void) const { return y1; }
int Linha:: getX2(void) const { return x2; }
int Linha:: getY2(void) const { return y2; }

void Linha:: setX1(int x1) { this->x1 = x1; }
void Linha:: setY1(int y1) { this->y1 = y1; }
void Linha:: setX2(int x2) { this->x2 = x2; }
void Linha:: setY2(int y2) { this->y2 = y2; }
