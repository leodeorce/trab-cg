/*
 * Arquivo: Circulo.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC1
*/

#ifndef CIRCULO_H
#define CIRCULO_H

#include "Elemento.h"

class Circulo : public Elemento {
	int raio;
public:
	int getRaio() const;
};

#endif /* CIRCULO_H */
