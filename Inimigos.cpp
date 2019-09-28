/*
 * Arquivo: Inimigos.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
 */

#include "Inimigos.h"

void Inimigos:: Adicionar(Circulo* inimigo) {
	inimigos.push_back(inimigo);
}

void Inimigos:: Desenha(void) const {
	
	list<Circulo*>::const_iterator itr;
	
	for(itr = inimigos.begin(); itr != inimigos.end(); ++itr) {
		
		Circulo* circulo = *itr;
		
		glPushMatrix();
		
		glTranslatef(circulo->getCX(), circulo->getCY(), 0.0f);
		circulo->Desenha();
		
		glPopMatrix();
	}
}

Inimigos:: ~Inimigos() {
	list<Circulo*>::iterator itr;	
	for(itr = inimigos.begin(); itr != inimigos.end(); ++itr) {		
		delete *itr;
	}
}