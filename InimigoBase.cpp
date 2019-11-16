/*
 * Arquivo: InimigoBase.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC4
 */

#include <cmath>
#include "InimigoBase.h"

using namespace std;

void InimigoBase:: setEstado(GLint estado) { this->estado = estado; }

GLint InimigoBase:: getEstado(void) const { return estado; }

void InimigoBase:: Desenhar(void)
{
	glPushMatrix();
	
		glTranslatef(gX, gY, 0.0);
		circulo->Desenhar();
		
		GLfloat raio = circulo->getRaio();
		
		Circulo circuloPreto = Circulo(0.0, 0.0, 0.0);
		circuloPreto.setRaio((5.0 / 6.0) * raio);
		circuloPreto.Desenhar();
		
		Circulo circuloLaranja = Circulo(1.0, 0.647, 0.0);
		circuloLaranja.setRaio((4.0 / 6.0) * raio);
		circuloLaranja.Desenhar();
		
		circuloPreto.setRaio((3.0 / 6.0) * raio);
		circuloPreto.Desenhar();
		
		circuloLaranja.setRaio((2.0 / 6.0) * raio);
		circuloLaranja.Desenhar();
		
	glPopMatrix();
}