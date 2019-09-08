/*
 * Arquivo: CirculoImpresso.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC1
*/

#include "CirculoImpresso.h"

CirculoImpresso:: CirculoImpresso(const CirculoImpresso* circulo) {
	this->x = circulo->x;
	this->y = circulo->y;
	this->setRaio( circulo->getRaio() );
	this->setCorR( circulo->getCorR() );
	this->setCorG( circulo->getCorG() );
	this->setCorB( circulo->getCorB() );
}

void CirculoImpresso:: setX(const int& x) { this->x = x; }
void CirculoImpresso:: setY(const int& y) { this->y = y; }

int CirculoImpresso:: getX() const { return x; }
int CirculoImpresso:: getY() const { return y; }