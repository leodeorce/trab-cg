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
	bool decolou = false;
	GLfloat multiplicador;
	GLfloat vXFinal;
	GLfloat vYFinal;
public:
	void setMultiplicador(GLfloat);
	GLfloat getMultiplicador(void) const;
	bool getDecolou(void) const;
	GLfloat getVXFinal(void) const;
	GLfloat getVYFinal(void) const;
	void MoverCorrigidoX(GLfloat);
	void MoverCorrigidoY(GLfloat);
	void Decolar(GLint, GLfloat, GLfloat);
};

#endif /* JOGADOR_H */
