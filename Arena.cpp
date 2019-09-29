/*
 * Arquivo: Arena.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#include "Arena.h"

using namespace std;

void Arena:: setNomeArquivo(string arquivo) {
	this->arquivo = arquivo;
}

string Arena:: getNomeArquivo(void) const {
	return arquivo;
}
