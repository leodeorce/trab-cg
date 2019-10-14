/*
 * Arquivo: Inimigo.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC3
 */

#ifndef INIMIGO_H
#define INIMIGO_H

#include <GL/glut.h>
#include "Elemento.h"

using namespace std;

class Inimigo : public Elemento {
public:
	bool ExisteConflito(GLfloat raio, GLfloat x, GLfloat y);
};

#endif /* INIMIGO_H */