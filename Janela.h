/*
 * Arquivo: Janela.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#ifndef JANELA_H
#define JANELA_H

#include <string>
#include "Elemento.h"

using namespace std;

class Janela {
	int xInicial, xFinal;
	int yInicial, yFinal;
	string titulo;
public:
	int getXInicial(void) const;
	int getXFinal(void) const;
	int getYInicial(void) const;
	int getYFinal(void) const;
	string getTitulo(void) const;
	void setXInicial(int);
	void setXFinal(int);
	void setYInicial(int);
	void setYFinal(int);
	void setTitulo(string);
};

#endif /* JANELA_H */
