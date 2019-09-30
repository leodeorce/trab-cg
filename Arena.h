/*
 * Arquivo: Arena.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#ifndef ARENA_H
#define ARENA_H

#include <GL/glut.h>
#include <string>
#include "Elemento.h"

using namespace std;

class Arena : public Elemento {
	string arquivo;
public:
	void setNomeArquivo(string);
	string getNomeArquivo(void) const;
	bool ExisteConflito(GLfloat, GLfloat, GLfloat) const;
};

#endif /* ARENA_H */
