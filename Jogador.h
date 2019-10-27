/*
 * Arquivo: Jogador.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC3
*/

#ifndef JOGADOR_H
#define JOGADOR_H

#include <GL/glut.h>
#include "Elemento.h"
#include "Retangulo.h"

using namespace std;

class Jogador : public Elemento {
	bool emDecolagem = false;
	bool decolou = false;
	GLfloat multVelAviao = 1.0f;
	GLfloat multVelTiro = 1.0f;
	GLfloat velAviao = 0.0f;
	GLfloat anguloCanhaoGraus = 0.0f;
	GLfloat anguloCanhaoRadianos = 0.0f;
	GLdouble anguloAviaoGrausInicial = 0.0f;
	GLdouble anguloAviaoGraus = 0.0f;
	GLdouble anguloAviaoRadianos = 0.0f;
	const GLfloat proporcaoAviao = 0.3f;
	Retangulo* retangulo = new Retangulo(0.0f, 0.0f, 0.0f);
public:
	void setMultVelAviao(GLfloat);
	void setMultVelTiro(GLfloat);
	void setAnguloAviaoGrausInicial(GLdouble);
	void setAnguloAviaoGraus(GLdouble);
	void setAnguloAviaoRadianos(GLdouble);
	void setDecolou(bool);
	void setEmDecolagem(bool);
	void setVelAviao(GLfloat);
	GLfloat getMultVelAviao(void) const;
	GLfloat getMultVelTiro(void) const;
	GLdouble getAnguloAviaoGrausInicial(void) const;
	GLdouble getAnguloAviaoGraus(void) const;
	GLdouble getAnguloAviaoRadianos(void) const;
	bool getDecolou(void) const;
	GLfloat getVelAviao(void) const;
	void Mover(GLint);
	void AjustarAnguloAviao(GLint);
	void AjustarAnguloCanhao(GLint);
	void Decolar(GLint, GLfloat, GLfloat);
	void Desenhar(GLint);
	~Jogador();
private:
	void MoverCorrigidoX(GLint);
	void MoverCorrigidoY(GLint);
	void DesenharCanhao(GLfloat, GLfloat, GLfloat);
	void DesenharCorpo(Circulo*);
	void DesenharCabine(Circulo*);
	void DesenharTurbinas(GLfloat, GLfloat, GLfloat);
	void DesenharTurbina(GLfloat, GLfloat, GLfloat);
	void DesenharAsas(GLfloat, GLfloat, GLfloat, GLfloat);
	void DesenharAsa(GLfloat, GLfloat, GLfloat, GLfloat);
	void DesenharCalda(GLfloat, GLfloat, GLfloat);
	void DesenharHelices(GLfloat, GLfloat, GLfloat, GLfloat, GLint);
	void DesenharHelice(GLfloat, GLfloat, GLfloat, GLfloat, GLdouble);
};

#endif /* JOGADOR_H */
