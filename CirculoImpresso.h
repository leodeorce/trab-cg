/*
 * Arquivo: CirculoImpresso.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC1
*/

#ifndef CIRCULOIMPRESSO_H
#define CIRCULOIMPRESSO_H

#include "Circulo.h"

class CirculoImpresso : public Circulo {
	int x, y;
public:
	CirculoImpresso() { }
	CirculoImpresso(const CirculoImpresso*);
	void setX(const int&);
	void setY(const int&);
	int getX() const;
	int getY() const;
};

#endif /* CIRCULOIMPRESSO_H */
