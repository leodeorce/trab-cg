/*
 * Arquivo: Janela.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#include <cmath>
#include "Janela.h"

GLint Janela:: getXI(void) const { return xI; }
GLint Janela:: getXF(void) const { return xF; }
GLint Janela:: getYI(void) const { return yI; }
GLint Janela:: getYF(void) const { return yF; }
string Janela:: getTitulo(void) const { return titulo; }

void Janela:: setXI(GLint xI) { this->xI = xI; }
void Janela:: setXF(GLint xF) { this->xF = xF; }
void Janela:: setYI(GLint yI) { this->yI = yI; }
void Janela:: setYF(GLint yF) { this->yF = yF; }
void Janela:: setTitulo(string titulo) { this->titulo = titulo; }

GLint Janela:: Largura(void) const {
	return abs(xF - xI);
}

GLint Janela:: Altura(void) const {
	return abs(yF - yI);
}