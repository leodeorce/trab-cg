/*
 * Arquivo: Janela.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#ifndef JANELA_H
#define JANELA_H

#include <GL/glut.h>
#include <string>

using namespace std;

class Janela {
	GLint xInicial, xFinal;
	GLint yInicial, yFinal;
	string titulo;
public:
	GLint getXInicial(void) const;
	GLint getXFinal(void) const;
	GLint getYInicial(void) const;
	GLint getYFinal(void) const;
	string getTitulo(void) const;
	void setXInicial(GLint);
	void setXFinal(GLint);
	void setYInicial(GLint);
	void setYFinal(GLint);
	void setTitulo(string);
};

#endif /* JANELA_H */
