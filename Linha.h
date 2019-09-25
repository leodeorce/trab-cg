/*
 * Arquivo: Linha.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#ifndef LINHA_H
#define LINHA_H

#include "Elemento.h"

class Linha : public Elemento {
	int x1, y1;
    int x2, y2;
public:
	Linha(float, float, float);
	int getX1(void) const;
	int getY1(void) const;
	int getX2(void) const;
	int getY2(void) const;
	void setX1(int);
	void setY1(int);
	void setX2(int);
	void setY2(int);
};

#endif /* LINHA_H */
