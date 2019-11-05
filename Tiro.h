/*
 * Arquivo: Tiro.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC4
*/

#ifndef TIRO_H
#define TIRO_H

#include <GL/glut.h>
#include "Elemento.h"

using namespace std;

class Tiro : public Elemento {
	
protected:
	GLfloat vel = 0.0f;
	GLfloat multVel = 0;
	GLdouble anguloTrajetoriaRad = 0.0f;
	
public:
	void setVel(GLfloat);
	void setMultVel(GLfloat);
	void setAnguloTrajetoriaRad(GLdouble);
	GLfloat getVel(void);
	GLfloat getMultVel(void);
	GLdouble getAnguloTrajetoriaRad(void);
	void Mover(GLint);
	
private:
	void MoverTiroX(GLint);
	void MoverTiroY(GLint);
};

#endif /* TIRO_H */
