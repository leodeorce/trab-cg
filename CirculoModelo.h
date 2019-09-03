/*
 * Arquivo: CirculoModelo.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC1
*/

#ifndef CIRCULOMODELO_H
#define CIRCULOMODELO_H

#include "Circulo.h"

class CirculoModelo : public Circulo {
	float corSobreposicaoR, corSobreposicaoG, corSobreposicaoB;
public:
	float getCorSobreposicaoR() const;
	float getCorSobreposicaoG() const;
	float getCorSobreposicaoB() const;
	void setCorSobreposicaoR(float&);
	void setCorSobreposicaoG(float&);
	void setCorSobreposicaoB(float&);
};

#endif /* CIRCULOMODELO_H */
