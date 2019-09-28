/*
 * Arquivo: Inimigos.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
 */

#ifndef INIMIGOS_H
#define INIMIGOS_H

#include <list>
#include "Circulo.h"

using namespace std;

class Inimigos {
	list<Circulo*> inimigos;
public:
	void Adicionar(Circulo*);
	void Desenha(void) const;
	~Inimigos();
};

#endif /* INIMIGOS_H */