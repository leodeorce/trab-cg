/*
 * Arquivo: Jogador.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#ifndef JOGADOR_H
#define JOGADOR_H

#include <GL/glut.h>
#include "Elemento.h"

using namespace std;

class Jogador : public Elemento {
	bool Decolou = false;
	GLfloat multiplicador;
public:
	void setMultiplicador(GLfloat);
	GLfloat getMultiplicador(void) const;
	void Decolar(void);
};

#endif /* JOGADOR_H */
