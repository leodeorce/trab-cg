/*
 * Arquivo: InimigoAviao.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC4
 */

#ifndef INIMIGOAVIAO_H
#define INIMIGOAVIAO_H

#include <GL/glut.h>
#include "Aviao.h"

using namespace std;

class InimigoAviao : public Aviao {

protected:
	GLfloat freqTiro = 0.0f;
	
public:
	void setFreqTiro(GLfloat);
	GLfloat getFreqTiro(void) const;
};

#endif /* INIMIGOAVIAO_H */