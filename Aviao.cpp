/*
 * Arquivo: Aviao.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC4
 */

#include <iostream>
#include <cmath>
#include "Aviao.h"

using namespace std;

void Aviao:: setDecolou(bool decolou) { this->decolou = decolou; }
void Aviao:: setEmDecolagem(bool emDecolagem) { this->emDecolagem = emDecolagem; }
void Aviao:: setMultVelAviaoInicial(GLfloat multVelAviaoInicial) { this->multVelAviaoInicial = multVelAviaoInicial; }
void Aviao:: setMultVelAviao(GLfloat multVelAviao) { this->multVelAviao = multVelAviao; }
void Aviao:: setMultVelTiroInicial(GLfloat multVelTiroInicial) { this->multVelTiroInicial = multVelTiroInicial; }
void Aviao:: setMultVelTiro(GLfloat multVelTiro) { this->multVelTiro = multVelTiro; }
void Aviao:: setVelAviao(GLfloat velAviao) { this->velAviao = velAviao; }
void Aviao:: setAnguloAviaoGrausInicial(GLdouble anguloAviaoGrausInicial) { this->anguloAviaoGrausInicial = anguloAviaoGrausInicial; }
void Aviao:: setAnguloAviaoGraus(GLdouble anguloAviaoGraus) { this->anguloAviaoGraus = anguloAviaoGraus; }
void Aviao:: setAnguloAviaoRadianos(GLdouble anguloAviaoRadianos) { this->anguloAviaoRadianos = anguloAviaoRadianos; }

bool Aviao:: getDecolou(void) const { return decolou; }
bool Aviao:: getEmDecolagem(void) const { return emDecolagem; }
GLfloat Aviao:: getMultVelAviaoInicial(void) const { return multVelAviaoInicial; }
GLfloat Aviao:: getMultVelAviao(void) const { return multVelAviao; }
GLfloat Aviao:: getMultVelTiroInicial(void) const { return multVelTiroInicial; }
GLfloat Aviao:: getMultVelTiro(void) const { return multVelTiro; }
GLfloat Aviao:: getVelAviao(void) const { return velAviao; }
GLdouble Aviao:: getAnguloCanhaoGraus(void) const { return anguloCanhaoGraus; }
GLdouble Aviao:: getAnguloCanhaoRadianos(void) const { return anguloCanhaoRadianos; }
GLdouble Aviao:: getAnguloAviaoGraus(void) const { return anguloAviaoGraus; }
GLdouble Aviao:: getAnguloAviaoGrausInicial(void) const { return anguloAviaoGrausInicial; }
GLdouble Aviao:: getAnguloAviaoRadianos(void) const { return anguloAviaoRadianos; }

void Aviao:: AjustarAnguloAviao(GLint frametime)
{
	GLfloat vAngAviao = 0.1 + velAviao / 2.5;
	GLfloat dA = vAngAviao * (GLfloat) frametime;
	
	anguloAviaoGraus += dA;
	
	if(anguloAviaoGraus > 360.0) {
		
		GLfloat correcao = anguloAviaoGraus - 360.0;
		anguloAviaoGraus = correcao;
		
	} else if(anguloAviaoGraus < 0.0) {
		anguloAviaoGraus = 360.0 + anguloAviaoGraus;
	}
	
	anguloAviaoRadianos = anguloAviaoGraus * 3.14159 / 180.0;
}

void Aviao:: AjustarAnguloCanhao(GLint dX)
{
	GLfloat vAngCanhao = 0.5;
	GLfloat dA = vAngCanhao * (GLfloat) dX;
	
	anguloCanhaoGraus += dA;
	
	if(anguloCanhaoGraus > 45.0) {
		anguloCanhaoGraus = 45.0;
	} else if(anguloCanhaoGraus < -45.0) {
		anguloCanhaoGraus = -45.0;
	}
	
	anguloCanhaoRadianos = anguloCanhaoGraus * 3.14159 / 180.0;
}

void Aviao:: AjustarMultVelAviao(GLfloat dM)
{
	if((multVelAviao + dM) >= 0.1) {
		multVelAviao += dM;
	}
}

void Aviao:: AjustarMultVelTiro(GLfloat dM)
{
	if((multVelTiro + dM) >= 0.1) {
		multVelTiro += dM;
	}
}

void Aviao:: Decolar(GLint frametime, GLfloat xFinal, GLfloat yFinal)
{
	emDecolagem = true;
	static const GLfloat xInicial = this->getGX();
	static const GLfloat yInicial = this->getGY();
	static const GLfloat deltaX = xFinal - xInicial;
	static const GLfloat deltaY = yFinal - yInicial;
		
	if(decolou == false) {
						
		// Unidades por ms.
		GLfloat vX = deltaX / 4000.0;
		GLfloat vY = deltaY / 4000.0;
		
		GLfloat dX = vX * frametime;
		GLfloat dY = vY * frametime;
		
		this->MoverX(dX);
		this->MoverY(dY);
		
		GLfloat gX = this->getGX();
		GLfloat gY = this->getGY();
		
		if(abs(gX - xInicial) >= abs(deltaX) / 2.0) {
			
			Circulo* circulo = this->getCirculo();
			
			static const GLfloat raioInicial = circulo->getRaio();
			GLfloat raioAtual = circulo->getRaio();
			
			GLfloat vR = raioInicial / 2000.0;
			GLfloat dR = vR * frametime;
			
			circulo->setRaio(raioAtual + dR);
		}
		
		GLint sinalX = deltaX / abs(deltaX);
		GLint sinalY = deltaY / abs(deltaY);
		
		bool xChegou = false;
		bool yChegou = false;
		
		switch(sinalX) {
			
			case 1:
				if(gX >= xFinal) {
					xChegou = true;
				}
				break;
				
			case -1:
				if(gX <= xFinal) {
					xChegou = true;
				}
				break;
		}
		
		switch(sinalY) {
			
			case 1:
				if(gY >= xFinal) {
					yChegou = true;
				}
				break;
				
			case -1:
				if(gY <= xFinal) {
					yChegou = true;
				}
				break;
		}
		
		if(xChegou == true && yChegou == true) {
			decolou = true;
			emDecolagem = false;
		}

		GLfloat vResultante = sqrt(pow(vX, 2) + pow(vY, 2));
		velAviao = vResultante;
	}
}

void Aviao:: Mover(GLint frametime)
{
	this->MoverAviaoX(frametime);
	this->MoverAviaoY(frametime);
}

void Aviao:: MoverAviaoX(GLint frametime)
{
	GLdouble vX = cos(anguloAviaoRadianos) * (GLdouble) velAviao * (GLdouble) multVelAviao;
	GLdouble dX = vX * (GLdouble) frametime;
	this->MoverX(dX);
}

void Aviao:: MoverAviaoY(GLint frametime)
{
	GLdouble vY = - sin(anguloAviaoRadianos) * (GLdouble) velAviao * (GLdouble) multVelAviao;
	GLdouble dY = vY * (GLdouble) frametime;
	this->MoverY(dY);
}

Tiro* Aviao:: Atirar(GLfloat corR, GLfloat corG, GLfloat corB)
{
	GLfloat aviaoX = this->getGX();
	GLfloat aviaoY = this->getGY();
	
	GLfloat correcaoAnguloCanhao = anguloAviaoRadianos - anguloCanhaoRadianos;
	
	GLfloat correcaoXAviao = cos(anguloAviaoRadianos) * offsetYCanhao;
	GLfloat correcaoXCanhao = cos(correcaoAnguloCanhao) * (alturaCanhao / 2.0);
	
	GLfloat correcaoYAviao = - sin(anguloAviaoRadianos) * offsetYCanhao;
	GLfloat correcaoYCanhao = - sin(correcaoAnguloCanhao) * (alturaCanhao / 2.0);
	
	GLfloat tiroX = aviaoX + correcaoXAviao + correcaoXCanhao;
	GLfloat tiroY = aviaoY + correcaoYAviao + correcaoYCanhao;
	
	Tiro* tiro = new Tiro();
	
	tiro->setGXInicial(tiroX);
	tiro->setGX(tiroX);
	tiro->setGYInicial(tiroY);
	tiro->setGY(tiroY);
	tiro->setVel(velAviao);
	tiro->setMultVel(multVelTiro);
	tiro->setAnguloTrajetoriaRad(correcaoAnguloCanhao);
	
	Circulo* circulo = new Circulo(corR, corG, corB);
	
	circulo->setRaioInicial(larguraCanhao);
	circulo->setRaio(larguraCanhao);
	
	tiro->setCirculo(circulo);
	
	return tiro;
}

Bomba* Aviao:: Bombardear(void)
{
	GLfloat aviaoX = this->getGX();
	GLfloat aviaoY = this->getGY();
	
	Circulo* circuloBomba = new Circulo(1.0, 1.0, 1.0);
	Circulo* circuloAviao = this->getCirculo();
	GLfloat raioBomba = circuloAviao->getRaio() / 2.0;
	
	circuloBomba->setRaioInicial(raioBomba);
	circuloBomba->setRaio(raioBomba);
	
	GLfloat acel = - velAviao / 4000.0;
	
	Bomba* bomba = new Bomba();
	
	bomba->setCirculo(circuloBomba);
	bomba->setGXInicial(aviaoX);
	bomba->setGX(aviaoX);
	bomba->setGYInicial(aviaoY);
	bomba->setGY(aviaoY);
	bomba->setVel(velAviao);
	bomba->setMultVel(multVelAviao);
	bomba->setAnguloTrajetoriaRad(anguloAviaoRadianos);
	bomba->setAcel(acel);
	
	return bomba;
}

void Aviao:: Desenhar(GLint frametime)
{
	Circulo* circulo = this->getCirculo();
	GLfloat raio = circulo->getRaio();
	GLfloat raioProp = proporcaoAviao * raio;
		
	larguraCanhao = raio / 7.0;
	alturaCanhao = 2.5 * larguraCanhao;
	offsetYCanhao = raio + (0.5 * alturaCanhao);
	
	glPushMatrix();
	
		glTranslatef(this->getGX(), this->getGY(), 0.0);
		
		this->DesenharCanhao(offsetYCanhao, larguraCanhao, alturaCanhao);
		this->DesenharCorpo(circulo);
		this->DesenharCabine(circulo);
		
		GLfloat larguraTurbina = larguraCanhao;
		GLfloat alturaTurbina = 4.4 * larguraTurbina;
		GLfloat offsetXTurbina = 2.35 * raioProp;
		
		this->DesenharTurbinas(offsetXTurbina, alturaTurbina, larguraTurbina);
		
		GLfloat larguraAsa = 2.25 * raioProp;
		GLfloat alturaAsa = 1.5 * larguraAsa;
		GLfloat offsetXAsa = 2.125 * raioProp;
		GLfloat offsetYAsa = 0.25 * raioProp;
		
		this->DesenharAsas(offsetXAsa, offsetYAsa, larguraAsa, alturaAsa);
		
		GLfloat larguraCalda = larguraCanhao;
		GLfloat alturaCalda = 4.25 * larguraCalda;
		GLfloat offsetY = raio - (alturaCalda / 2.0);
		
		this->DesenharCalda(offsetY, larguraCalda, alturaCalda);
		
		GLfloat larguraHelice = 1.4 * raioProp;
		GLfloat alturaHelice = raio / 5.0;
		GLfloat offsetXHelice = 2.35 * raioProp;
		GLfloat offsetYHelice = 2.125 * raio / 7.0;
		
		this->DesenharHelices(offsetXHelice, offsetYHelice, larguraHelice, alturaHelice, frametime);
	
	glPopMatrix();
}

void Aviao:: DesenharCanhao(GLfloat offsetY, GLfloat largura, GLfloat altura)
{
	glPushMatrix();
		
		glRotatef(anguloAviaoGraus - 90, 0.0, 0.0, -1.0);
		glTranslatef(0.0, -offsetY, 0.0);
		
		glTranslatef(0.0, +altura / 2.0, 0.0);
		glRotatef(anguloCanhaoGraus, 0.0, 0.0, 1.0);
		glTranslatef(0.0, -altura / 2.0, 0.0);
		
		glScalef(largura, altura, 1.0);
		
		retangulo->Desenhar();
	
	glPopMatrix();
}

void Aviao:: DesenharCorpo(Circulo* circulo)
{
	glPushMatrix();
	
		glRotatef(anguloAviaoGraus - 90, 0.0, 0.0, -1.0);
		glScalef(proporcaoAviao, 1.0, 1.0);
		circulo->Desenhar();
	
	glPopMatrix();
}

void Aviao:: DesenharCabine(Circulo* circulo)
{
	GLfloat corOriginalR = circulo->getCorR();
	GLfloat corOriginalG = circulo->getCorG();
	GLfloat corOriginalB = circulo->getCorB();
	
	circulo->setCorR(0.0);
	circulo->setCorG(0.0);
	circulo->setCorB(0.0);
	
	glPushMatrix();
	
		glRotatef(anguloAviaoGraus - 90, 0.0, 0.0, -1.0);
		glTranslatef(0.0, -circulo->getRaio() / 2.0, 0.0);
		glScalef(proporcaoAviao / 2.5, 1.25 * proporcaoAviao, 1.0);
		circulo->Desenhar();
	
	glPopMatrix();
	
	circulo->setCorR(corOriginalR);
	circulo->setCorG(corOriginalG);
	circulo->setCorB(corOriginalB);
}

void Aviao:: DesenharTurbinas(GLfloat offsetX, GLfloat largura, GLfloat altura)
{
	this->DesenharTurbina(-offsetX, largura, altura);
	this->DesenharTurbina(offsetX, largura, altura);
}

void Aviao:: DesenharTurbina(GLfloat offsetX, GLfloat largura, GLfloat altura)
{
	glPushMatrix();
	
		glRotatef(anguloAviaoGraus - 90, 0.0, 0.0, -1.0);
		glTranslatef(offsetX, 0.0, 0.0);
		glScalef(altura, largura, 1.0);
		retangulo->Desenhar();
	
	glPopMatrix();
}

void Aviao:: DesenharAsas(GLfloat offsetX, GLfloat offsetY, GLfloat largura, GLfloat altura)
{
	this->DesenharAsa( -offsetX, offsetY, +largura, altura);
	this->DesenharAsa( +offsetX, offsetY, -largura, altura);
}

void Aviao:: DesenharAsa(GLfloat offsetX, GLfloat offsetY, GLfloat largura, GLfloat altura)
{
	glPushMatrix();
	
		glRotatef(anguloAviaoGraus - 90, 0.0, 0.0, -1.0);
		glTranslatef(offsetX, offsetY, 0.0);
		glScalef(largura, altura, 1.0);
		retangulo->DesenharCisalhado();
	
	glPopMatrix();
}

void Aviao:: DesenharCalda(GLfloat offsetY, GLfloat largura, GLfloat altura)
{
	glPushMatrix();
	
		glRotatef(anguloAviaoGraus - 90, 0.0, 0.0, -1.0);
		glTranslatef(0.0, offsetY, 0.0);
		glScalef(largura, altura, 1.0);
		retangulo->Desenhar();
	
	glPopMatrix();
}

void Aviao:: DesenharHelices(GLfloat offsetX, GLfloat offsetY, GLfloat largura, GLfloat altura, GLint frametime)
{
	GLfloat corOriginalR = retangulo->getCorR();
	GLfloat corOriginalG = retangulo->getCorG();
	GLfloat corOriginalB = retangulo->getCorB();
	
	retangulo->setCorR(1.0);
	retangulo->setCorG(1.0);
	retangulo->setCorB(0.0);

	GLdouble grausPorFrame;
	
	if(decolou == true || emDecolagem == true) {
		grausPorFrame = 360.0 * (velAviao * multVelAviao) / 1000.0;
	} else {
		grausPorFrame = 0.0;
	}

	GLdouble fpsAlvo = 30;
	GLdouble grausPorSegundo = fpsAlvo * grausPorFrame;
	GLdouble dG = grausPorSegundo * ((GLdouble) frametime);
	static GLdouble anguloGiro = dG;
	
	anguloGiro += dG;
	
	if(decolou == false && emDecolagem == false) {
		anguloGiro = 0.0;
	}

	this->DesenharHelice( -offsetX, -offsetY, largura, altura, anguloGiro);
	this->DesenharHelice( +offsetX, -offsetY, largura, altura, anguloGiro);

	if(anguloGiro > 360) {
		anguloGiro = 0;
	}

	retangulo->setCorR(corOriginalR);
	retangulo->setCorG(corOriginalG);
	retangulo->setCorB(corOriginalB);
}

void Aviao:: DesenharHelice(GLfloat offsetX, GLfloat offsetY, GLfloat largura, GLfloat altura, GLdouble dG)
{
	glPushMatrix();
	
		glRotatef(anguloAviaoGraus - 90, 0.0, 0.0, -1.0);
		glTranslatef(offsetX, offsetY, 0.0);
		glRotatef(dG, 0.0, 0.0, 1.0);
		glScalef(largura, altura, 1.0);

		retangulo->DesenharHelice();
	
	glPopMatrix();
}

Aviao:: ~Aviao()
{
	delete retangulo;
}
