/*
 * Arquivo: Janela.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC4
*/

#ifndef JANELA_H
#define JANELA_H

#include <GL/glut.h>
#include <string>

using namespace std;

class Janela {

protected:
	GLint xI = 0;
	GLint xF = 0;
	GLint yI = 0;
	GLint yF = 0;
	string titulo;
	
public:
	void setXI(GLint);
	void setXF(GLint);
	void setYI(GLint);
	void setYF(GLint);
	void setTitulo(string);
	GLint getXI(void) const;
	GLint getXF(void) const;
	GLint getYI(void) const;
	GLint getYF(void) const;
	string getTitulo(void) const;
	GLint Largura(void) const;
	GLint Altura(void) const;
};

#endif /* JANELA_H */
