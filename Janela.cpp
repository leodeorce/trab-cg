/*
 * Arquivo: Janela.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC1
*/

#include "Janela.h"

int Janela:: getLargura() const { return largura; }
int Janela:: getAltura() const { return altura; }
string Janela:: getTitulo() const { return titulo; }

void Janela:: setLargura(int& largura) { this->largura = largura; }
void Janela:: setAltura(int& altura) { this->altura = altura; }
void Janela:: setTitulo(string& titulo) { this->titulo = titulo; }
