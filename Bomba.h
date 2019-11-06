/*
 * Arquivo: Bomba.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC4
*/

#ifndef BOMBA_H
#define BOMBA_H

#include <GL/glut.h>
#include "Elemento.h"

using namespace std;

class Bomba : public Elemento {

protected:
	GLfloat vel = 0.0;
	GLfloat multVel = 0.0;
	GLfloat acel = 0.0;
	GLdouble anguloTrajetoriaRad = 0.0;
	
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
