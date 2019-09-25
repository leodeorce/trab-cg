/*
 * Arquivo: Janela.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#include "Janela.h"

int Janela:: getXInicial(void) const { return xInicial; }
int Janela:: getXFinal(void) const { return xFinal; }
int Janela:: getYInicial(void) const { return yInicial; }
int Janela:: getYFinal(void) const { return yFinal; }
string Janela:: getTitulo(void) const { return titulo; }

void Janela:: setXInicial(int xInicial) { this->xInicial = xInicial; }
void Janela:: setXFinal(int xFinal) { this->xFinal = xFinal; }
void Janela:: setYInicial(int yInicial) { this->yInicial = yInicial; }
void Janela:: setYFinal(int yFinal) { this->yFinal = yFinal; }
void Janela:: setTitulo(string titulo) { this->titulo = titulo; }
