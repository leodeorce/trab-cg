/*
 * Arquivo: Jogador.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#ifndef JOGADOR_H
#define JOGADOR_H

#include "Circulo.h"

using namespace std;

class Jogador {
	float multiplicador;
	Circulo* circulo;
public:
	void setMultiplicador(float);
	void setCirculo(Circulo&);
	float getMultiplicador(void) const;
	Circulo* getCirculo(void) const;
	~Jogador();
};

#endif /* JOGADOR_H */
