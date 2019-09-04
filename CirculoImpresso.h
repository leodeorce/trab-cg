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
	CirculoImpresso(const int&, const int&);
	int getX() const;
	int getY() const;
};

#endif /* CIRCULOIMPRESSO_H */
