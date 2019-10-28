/*
 * Arquivo: Bomba.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC3
*/

#ifndef BOMBA_H
#define BOMBA_H

#include <GL/glut.h>
#include "Elemento.h"

using namespace std;

class Bomba : public Elemento {
	GLfloat vel = 0.0f;
	GLfloat multVel = 0.0f;
	GLfloat acel = 0.0f;
	GLdouble anguloTrajetoriaRad = 0.0f;
public:
	void setVel(GLfloat);
	void setMultVel(GLfloat);
	void setAcel(GLfloat);
	void setAnguloTrajetoriaRad(GLdouble);
	GLfloat getVel(void);
	GLfloat getMultVel(void);
	GLfloat getAcel(void);
	GLdouble getAnguloTrajetoriaRad(void);
	void Mover(GLint);
private:
	void MoverBombaX(GLint);
	void MoverBombaY(GLint);
};

#endif /* BOMBA_H */
