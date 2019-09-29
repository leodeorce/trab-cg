/*
 * Arquivo: Inimigo.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
 */

#ifndef INIMIGO_H
#define INIMIGO_H

#include <GL/glut.h>
#include "Elemento.h"

using namespace std;

class Inimigo : public Elemento {
public:
	bool existeConflito(GLint raio, GLint x, GLint y);
};

#endif /* INIMIGO_H */