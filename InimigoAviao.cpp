/*
 * Arquivo: InimigoAviao.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC4
 */

#include <cmath>
#include "InimigoAviao.h"

using namespace std;

void InimigoAviao:: setFreqTiro(GLfloat freqTiro) {
	this->freqTiro = freqTiro;
}

GLfloat InimigoAviao:: getFreqTiro(void) const {
	return freqTiro;
}
