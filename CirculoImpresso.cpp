/*
 * Arquivo: CirculoImpresso.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC1
*/

#include "CirculoImpresso.h"

CirculoImpresso:: CirculoImpresso(const int& x, const int& y) {
	this->x = x;
	this->y = y;
}

int CirculoImpresso:: getX() const {
	return x;
}

int CirculoImpresso:: getY() const {
	return y;
}