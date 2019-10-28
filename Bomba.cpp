/*
 * Arquivo: Bomba.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC3
*/

#include <cmath>
#include "Bomba.h"

void Bomba:: setVel(GLfloat vel) {
	this->vel = vel;
}

void Bomba:: setMultVel(GLfloat multVel) {
	this->multVel = multVel;
}

void Bomba:: setAcel(GLfloat acel) {
	this->acel = acel;
}

void Bomba:: setAnguloTrajetoriaRad(GLdouble anguloTrajetoriaRad) {
	this->anguloTrajetoriaRad = anguloTrajetoriaRad;
}

GLfloat Bomba:: getVel(void) {
	return vel;
}

GLfloat Bomba:: getMultVel(void) {
	return multVel;
}

GLfloat Bomba:: getAcel(void) {
	return acel;
}

GLdouble Bomba:: getAnguloTrajetoriaRad(void) {
	return anguloTrajetoriaRad;
}

void Bomba:: Mover(GLint frametime) {
	this->MoverBombaX(frametime);
	this->MoverBombaY(frametime);
}

void Bomba:: MoverBombaX(GLint frametime) {
	GLdouble vX = cos(anguloTrajetoriaRad) * (GLdouble) vel * (GLdouble) multVel;
	GLdouble dX = vX * (GLdouble) frametime;
	this->MoverX(dX);
}

void Bomba:: MoverBombaY(GLint frametime) {
	GLdouble vY = - sin(anguloTrajetoriaRad) * (GLdouble) vel * (GLdouble) multVel;
	GLdouble dY = vY * (GLdouble) frametime;
	this->MoverY(dY);
}
