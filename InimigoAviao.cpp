/*
 * Arquivo: InimigoAviao.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC4
 */

#include <iostream>
#include <cmath>
#include "InimigoAviao.h"

using namespace std;

void InimigoAviao:: setEstado(GLint estado) { this->estado = estado; }

GLint InimigoAviao:: getEstado(void) const { return estado; }

void InimigoAviao:: Mover(GLint frametime)
{
	switch(estado) {
		
		case 1:
			this->MoverLinhaReta(frametime);
			break;
		
		case 2:
			this->MoverCirculo(frametime);
			break;
		
		case 3:
			this->MoverZigueZague(frametime);
			break;
		
		default:
			break;
	}
}

void InimigoAviao:: MoverLinhaReta(GLint frametime)
{
	Aviao::Mover(frametime);
}

void InimigoAviao:: MoverCirculo(GLint frametime)
{
	this->AjustarAnguloAviao( frametime / 2 );
	Aviao::Mover(frametime);
}

void InimigoAviao:: MoverZigueZague(GLint frametime)
{
	static GLint multiplicador = 1;
	static GLint tempoCorrido = 0;
	tempoCorrido += frametime;
	
	if(tempoCorrido > 5000) {
		tempoCorrido = 0;
		multiplicador = - multiplicador;
	}
	
	this->AjustarAnguloAviao( multiplicador * (frametime / 2) );
	Aviao::Mover(frametime);
}
