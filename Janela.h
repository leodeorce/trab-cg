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
	int largura, altura;
	string titulo;
public:
	int getLargura(void) const;
	int getAltura(void) const;
	string getTitulo(void) const;
	void setLargura(int&);
	void setAltura(int&);
	void setTitulo(string);
};

#endif /* JANELA_H */
