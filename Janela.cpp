/*
 * Arquivo: Janela.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#include "Janela.h"

GLint Janela:: getXInicial(void) const { return xInicial; }
GLint Janela:: getXFinal(void) const { return xFinal; }
GLint Janela:: getYInicial(void) const { return yInicial; }
GLint Janela:: getYFinal(void) const { return yFinal; }
string Janela:: getTitulo(void) const { return titulo; }

void Janela:: setXInicial(GLint xInicial) { this->xInicial = xInicial; }
void Janela:: setXFinal(GLint xFinal) { this->xFinal = xFinal; }
void Janela:: setYInicial(GLint yInicial) { this->yInicial = yInicial; }
void Janela:: setYFinal(GLint yFinal) { this->yFinal = yFinal; }
void Janela:: setTitulo(string titulo) { this->titulo = titulo; }
