/*
 * Arquivo: Tiro.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC3
*/

#include <cmath>
#include "Tiro.h"

void Tiro:: setVel(GLfloat vel) {
	this->vel = vel;
}

void Tiro:: setMultVel(GLfloat multVel) {
	this->multVel = multVel;
}

void Tiro:: setAnguloTrajetoriaRad(GLdouble anguloTrajetoriaRad) {
	this->anguloTrajetoriaRad = anguloTrajetoriaRad;
}

GLfloat Tiro:: getVel(void) {
	return vel;
}

GLfloat Tiro:: getMultVel(void) {
	return multVel;
}

GLdouble Tiro:: getAnguloTrajetoriaRad(void) {
	return anguloTrajetoriaRad;
}

void Tiro:: Mover(GLint frametime) {
	this->MoverTiroX(frametime);
	this->MoverTiroY(frametime);
}

void Tiro:: MoverTiroX(GLint frametime) {
	GLdouble vX = cos(anguloTrajetoriaRad) * (GLdouble) vel * (GLdouble) multVel;
	GLdouble dX = vX * (GLdouble) frametime;
	this->MoverX(dX);
}

void Tiro:: MoverTiroY(GLint frametime) {
	GLdouble vY = - sin(anguloTrajetoriaRad) * (GLdouble) vel * (GLdouble) multVel;
	GLdouble dY = vY * (GLdouble) frametime;
	this->MoverY(dY);
}
