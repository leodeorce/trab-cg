/*
 * Arquivo: Elemento.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC1
*/

#ifndef ELEMENTO_H
#define ELEMENTO_H

class Elemento {
	float corR, corG, corB;
public:
	float getCorR() const;
	float getCorG() const;
	float getCorB() const;
	void setCorR(const float&);
	void setCorG(const float&);
	void setCorB(const float&);
};

#endif /* ELEMENTO_H */
