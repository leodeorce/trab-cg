/*
 * Arquivo: Janela.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC1
*/

#ifndef JANELA_H
#define JANELA_H

#include <string>
#include "Elemento.h"

using namespace std;

class Janela : public Elemento {
	int largura, altura;
	string titulo;
public:
	int getLargura() const;
	int getAltura() const;
	string getTitulo() const;
	void setLargura(int&);
	void setAltura(int&);
	void setTitulo(string&);
};

#endif /* JANELA_H */
