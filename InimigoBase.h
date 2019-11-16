/*
 * Arquivo: InimigoBase.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC4
 */

#ifndef INIMIGOBASE_H
#define INIMIGOBASE_H

#include <GL/glut.h>
#include "Elemento.h"

using namespace std;

class InimigoBase : public Elemento {

protected:
	GLint estado = 1;
	
public:
	void setEstado(GLint);
	GLint getEstado(void) const;
	void Desenhar(void);
};

#endif /* INIMIGOBASE_H */