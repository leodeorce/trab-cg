/*
 * Arquivo: Jogador.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#include <cmath>
#include "Jogador.h"

void Jogador:: setMultiplicador(GLfloat multiplicador) {
	this->multiplicador = multiplicador;
}

GLfloat Jogador:: getMultiplicador(void) const {
	return multiplicador;
}

bool Jogador:: getDecolou(void) const {
	return decolou;
}

GLfloat Jogador:: getVXFinal(void) const {
	return vXFinal;
}

GLfloat Jogador:: getVYFinal(void) const {
	return vYFinal;
}

void Jogador:: MoverCorrigidoX(GLfloat frametime) {
	GLfloat dX = vXFinal * frametime;
	this->MoverX(dX);
}

void Jogador:: MoverCorrigidoY(GLfloat frametime) {
	GLfloat dY = vYFinal * frametime;
	this->MoverY(dY);
}

void Jogador:: Decolar(GLint frametime, GLfloat xFinal, GLfloat yFinal) {
	
	static const GLfloat xInicial = this->getGX();
	static const GLfloat yInicial = this->getGY();
	static const GLfloat deltaX = xFinal - xInicial;
	static const GLfloat deltaY = yFinal - yInicial;
		
	if(decolou == false) {
						
		// Unidades por ms.
		GLfloat vX = deltaX / 4000.0f;
		GLfloat vY = deltaY / 4000.0f;
		
		GLfloat dX = vX * frametime;
		GLfloat dY = vY * frametime;
		
		this->MoverX(dX);
		this->MoverY(dY);
		
		GLfloat gX = this->getGX();
		GLfloat gY = this->getGY();
		
		if(abs(gX - xInicial) >= abs(deltaX) / 2) {
			
			Circulo* circulo = this->getCirculo();
			
			static const GLfloat raioInicial = circulo->getRaio();
			GLfloat raioAtual = circulo->getRaio();
			
			GLfloat vR = raioInicial / 2000.0f;
			GLfloat dR = vR * frametime;
			
			circulo->setRaio(raioAtual + dR);
		}
		
		GLint sinalX = deltaX / abs(deltaX);
		GLint sinalY = deltaY / abs(deltaY);
		
		bool xChegou = false;
		bool yChegou = false;
		
		switch(sinalX) {
			
			case 1:
				if(gX >= xFinal) {
					xChegou = true;
				}
				break;
				
			case -1:
				if(gX <= xFinal) {
					xChegou = true;
				}
				break;
		}
		
		switch(sinalY) {
			
			case 1:
				if(gY >= xFinal) {
					yChegou = true;
				}
				break;
				
			case -1:
				if(gY <= xFinal) {
					yChegou = true;
				}
				break;
		}
		
		if(xChegou == true && yChegou == true) {
			
			decolou = true;
			
			GLfloat vResultante = sqrt(pow(vX, 2) + pow(vY, 2));
						
			vXFinal = vResultante * cos(45.0f * 3.141593f / 180.0f);
			vYFinal = vXFinal;
			
			vXFinal = vXFinal * multiplicador;
			vYFinal = vYFinal * multiplicador;
		}
	}
}
