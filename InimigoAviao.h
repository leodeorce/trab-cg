/*
 * Arquivo: InimigoAviao.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC4
 */

#ifndef INIMIGOAVIAO_H
#define INIMIGOAVIAO_H

#include <GL/glut.h>
#include "Aviao.h"

using namespace std;

class InimigoAviao : public Aviao {
	GLint estado = 1;
public:
	void setEstado(GLint);
	GLint getEstado(void) const;
	void Mover(GLint);
private:
	void MoverLinhaReta(GLint);
	void MoverCirculo(GLint);
	void MoverZigueZague(GLint);
};

#endif /* INIMIGOAVIAO_H */