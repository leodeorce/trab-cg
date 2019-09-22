/*
 * Arquivo: Elemento.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#ifndef ELEMENTO_H
#define ELEMENTO_H

enum Cor {
	RED = 0,
	GREEN = 1,
	BLUE = 2,
	ORANGE = 3
};

class Elemento {
	float corR;
	float corG;
	float corB;
public:
	Elemento(float&, float&, float&);
	Elemento() { }
	float getCorR(void) const;
	float getCorG(void) const;
	float getCorB(void) const;
	void setCorR(float&);
	void setCorG(float&);
	void setCorB(float&);
};

#endif /* ELEMENTO_H */
