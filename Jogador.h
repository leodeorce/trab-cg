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
	bool decolou = false;
	GLfloat multVelAviao;
	GLfloat multVelTiro;
	GLfloat vFinal = 0.0f;
	GLfloat anguloCanhao = 0.0f;
	GLdouble anguloAviaoGraus = 0.0f;
	GLdouble anguloAviaoRadianos = 0.0f;
	const GLfloat proporcaoAviao = 0.3f;
	Retangulo* retangulo = new Retangulo(0.0f, 0.0f, 0.0f);
public:
	void setMultVelAviao(GLfloat);
	void setMultVelTiro(GLfloat);
	void setAnguloAviaoGraus(GLdouble);
	void setAnguloAviaoRadianos(GLdouble);
	GLfloat getMultVelAviao(void) const;
	GLfloat getMultVelTiro(void) const;
	GLdouble getAnguloAviaoGraus(void) const;
	GLdouble getAnguloAviaoRadianos(void) const;
	bool getDecolou(void) const;
	GLfloat getVFinal(void) const;
	void Mover(GLint);
	void AjustarAnguloAviao(GLint);
	void Decolar(GLint, GLfloat, GLfloat);
	void Desenhar(void);
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
	void DesenharHelices(GLfloat, GLfloat, GLfloat, GLfloat);
	void DesenharHelice(GLfloat, GLfloat, GLfloat, GLfloat);
};

#endif /* JOGADOR_H */
