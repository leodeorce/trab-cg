/*
 * Arquivo: Arena.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#include "Arena.h"

using namespace std;

void Arena:: setNomeArquivo(string arquivo) { this->arquivo = arquivo; }
void Arena:: setCirculo(Circulo* circulo) { this->circulo = circulo; }

string Arena:: getNomeArquivo(void) const { return arquivo; }
Circulo* Arena:: getCirculo(void) const { return circulo; }

void Arena:: Desenha(void) const {
	
	glPushMatrix();
	
	glTranslatef(circulo->getCX(), circulo->getCY(), 0.0f);
	circulo->Desenha();
	
	glPopMatrix();
}

Arena:: ~Arena() {
	delete circulo;
}
