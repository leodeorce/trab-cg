/*
 * Arquivo: Elemento.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC1
*/

#include "Elemento.h"

float Elemento:: getCorR() const { return corR; }
float Elemento:: getCorG() const { return corG; }
float Elemento:: getCorB() const { return corB; }

void Elemento:: setCorR(const float& corR) { this->corR = corR; }
void Elemento:: setCorG(const float& corG) { this->corG = corG; }
void Elemento:: setCorB(const float& corB) { this->corB = corB; }
