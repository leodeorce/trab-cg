/*
 * Arquivo: Circulo.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#ifndef CIRCULO_H
#define CIRCULO_H

#include "Elemento.h"

class Circulo : public Elemento {
	int raio;
	int cX;
	int cY;
public:
	Circulo(float&, float&, float&);
	Circulo(Circulo&);
	int getRaio(void) const;
	int getCX(void) const;
	int getCY(void) const;
	void setRaio(int&);
	void setCX(int&);
	void setCY(int&);
};

#endif /* CIRCULO_H */
