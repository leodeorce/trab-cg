/*
 * Arquivo: Aviao.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC4
 */

#ifndef AVIAO_H
#define AVIAO_H

#include <GL/glut.h>
#include "Bomba.h"
#include "Elemento.h"
#include "Retangulo.h"
#include "Tiro.h"

using namespace std;

class Aviao : public Elemento {
	
protected:
	bool emDecolagem = false;
	bool decolou = false;
	GLfloat multVelAviaoInicial = 1.0f;
	GLfloat multVelAviao = 1.0f;
	GLfloat multVelTiroInicial = 1.0f;
	GLfloat multVelTiro = 1.0f;
	GLfloat velAviao = 1.0f;
	GLdouble anguloAviaoGrausInicial = 0.0f;
	GLdouble anguloAviaoGraus = 0.0f;
	GLdouble anguloAviaoRadianos = 0.0f;
	GLdouble anguloCanhaoGraus = 0.0f;
	GLdouble anguloCanhaoRadianos = 0.0f;
	GLfloat offsetYCanhao = 0.0f;
	GLfloat alturaCanhao = 0.0f;
	GLfloat larguraCanhao = 0.0f;
	const GLfloat proporcaoAviao = 0.3f;
	Retangulo* retangulo = new Retangulo(0.0f, 0.0f, 0.0f);
	
public:
	void setDecolou(bool);
	void setEmDecolagem(bool);
	void setMultVelAviaoInicial(GLfloat);
	void setMultVelAviao(GLfloat);
	void setMultVelTiroInicial(GLfloat);
	void setMultVelTiro(GLfloat);
	void setVelAviao(GLfloat);
	void setAnguloAviaoGrausInicial(GLdouble);
	void setAnguloAviaoGraus(GLdouble);
	void setAnguloAviaoRadianos(GLdouble);
	bool getDecolou(void) const;
	bool getEmDecolagem(void) const;
	GLfloat getMultVelAviaoInicial(void) const;
	GLfloat getMultVelAviao(void) const;
	GLfloat getMultVelTiroInicial(void) const;
	GLfloat getMultVelTiro(void) const;
	GLfloat getVelAviao(void) const;
	GLdouble getAnguloCanhaoGraus(void) const;
	GLdouble getAnguloCanhaoRadianos(void) const;
	GLdouble getAnguloAviaoGrausInicial(void) const;
	GLdouble getAnguloAviaoGraus(void) const;
	GLdouble getAnguloAviaoRadianos(void) const;
	void AjustarAnguloAviao(GLint);
	void AjustarAnguloCanhao(GLint);
	void AjustarMultVelAviao(GLfloat);
	void AjustarMultVelTiro(GLfloat);
	void Decolar(GLint, GLfloat, GLfloat);
	void Mover(GLint);
	Tiro* Atirar(void);
	Bomba* Bombardear(void);
	void Desenhar(GLint);
	~Aviao();
	
private:
	void MoverAviaoX(GLint);
	void MoverAviaoY(GLint);
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

#endif /* AVIAO_H */