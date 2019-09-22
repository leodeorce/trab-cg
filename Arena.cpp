/*
 * Arquivo: Arena.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#include "Arena.h"

using namespace std;

void Arena:: setArquivo(string& arquivo) { this->arquivo = arquivo; }
void Arena:: setCirculo(Circulo& circulo) { this->circulo = new Circulo(circulo); }

string Arena:: getArquivo(void) const { return arquivo; }
Circulo* Arena:: getCirculo(void) const { return circulo; }

Arena:: ~Arena() {
	delete circulo;
}