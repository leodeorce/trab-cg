/*
 * Arquivo: Janela.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC1
*/

#ifndef JANELA_H
#define JANELA_H

#include "Elemento.h"

using namespace std;

class Janela : public Elemento {
	int largura, altura;
	const char* titulo;
public:
	int getLargura() const;
	int getAltura() const;
	const char* getTitulo() const;
	void setLargura(int&);
	void setAltura(int&);
	void setTitulo(const char*);
};

#endif /* JANELA_H */
