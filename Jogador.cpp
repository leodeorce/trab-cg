/*
 * Arquivo: Jogador.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC3
*/

#include <iostream>
#include <cmath>
#include "Jogador.h"

using namespace std;

void Jogador:: setMultVelAviao(GLfloat multVelAviao) {
	this->multVelAviao = multVelAviao;
}

void Jogador:: setMultVelTiro(GLfloat multVelTiro) {
	this->multVelTiro = multVelTiro;
}

void Jogador:: setAnguloAviaoGraus(GLdouble anguloAviaoGraus) {
	this->anguloAviaoGraus = anguloAviaoGraus;
}

void Jogador:: setAnguloAviaoRadianos(GLdouble anguloAviaoRadianos) {
	this->anguloAviaoRadianos = anguloAviaoRadianos;
}

GLfloat Jogador:: getMultVelAviao(void) const {
	return multVelAviao;
}

GLfloat Jogador:: getMultVelTiro(void) const {
	return multVelTiro;
}

GLdouble Jogador:: getAnguloAviaoGraus(void) const {
	return anguloAviaoGraus;
}

GLdouble Jogador:: getAnguloAviaoRadianos(void) const {
	return anguloAviaoRadianos;
}

bool Jogador:: getDecolou(void) const {
	return decolou;
}

GLfloat Jogador:: getVelAviao(void) const {
	return velAviao;
}

void Jogador:: Mover(GLint frametime) {
	this->MoverCorrigidoX(frametime);
	this->MoverCorrigidoY(frametime);
}

void Jogador:: AjustarAnguloAviao(GLint frametime) {
	
	GLfloat vAngAviao = 1.0f / 10.0f;
	GLfloat dA = vAngAviao * (GLfloat) frametime;
	
	anguloAviaoGraus += dA;
	
	if(anguloAviaoGraus > 360.0f) {
		
		GLfloat correcao = anguloAviaoGraus - 360.0f;
		anguloAviaoGraus = correcao;
		
	} else if(anguloAviaoGraus < 0.0f) {
		anguloAviaoGraus = 360.0f + anguloAviaoGraus;
	}
	
	anguloAviaoRadianos = anguloAviaoGraus * 3.14159f / 180.0f;
}

void Jogador:: Decolar(GLint frametime, GLfloat xFinal, GLfloat yFinal) {
	
	emDecolagem = true;
	static const GLfloat xInicial = this->getGX();
	static const GLfloat yInicial = this->getGY();
	static const GLfloat deltaX = xFinal - xInicial;
	static const GLfloat deltaY = yFinal - yInicial;
		
	if(decolou == false) {
						
		// Unidades por ms.
		GLfloat vX = deltaX / 4000.0f;
		GLfloat vY = deltaY / 4000.0f;
		
		GLfloat dX = vX * frametime;
		GLfloat dY = vY * frametime;
		
		this->MoverX(dX);
		this->MoverY(dY);
		
		GLfloat gX = this->getGX();
		GLfloat gY = this->getGY();
		
		if(abs(gX - xInicial) >= abs(deltaX) / 2) {
			
			Circulo* circulo = this->getCirculo();
			
			static const GLfloat raioInicial = circulo->getRaio();
			GLfloat raioAtual = circulo->getRaio();
			
			GLfloat vR = raioInicial / 2000.0f;
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
		velAviao = vResultante * multVelAviao;
	}
}

void Jogador:: MoverCorrigidoX(GLint frametime) {
	GLdouble vX = cos(anguloAviaoRadianos) * (GLdouble) velAviao;
	GLdouble dX = vX * (GLdouble) frametime;
	this->MoverX(dX);
}

void Jogador:: MoverCorrigidoY(GLint frametime) {
	GLdouble vY = - sin(anguloAviaoRadianos) * (GLdouble) velAviao;
	GLdouble dY = vY * (GLdouble) frametime;
	this->MoverY(dY);
}

void Jogador:: Desenhar(GLint frametime) {
	
	Circulo* circulo = this->getCirculo();
	GLfloat raio = circulo->getRaio();
	GLfloat raioProp = proporcaoAviao * raio;
		
	GLfloat larguraCanhao = raio / 7.0f;
	GLfloat alturaCanhao = 2.5f * larguraCanhao;
	GLfloat offsetYCanhao = raio + (0.5f * alturaCanhao);
	
	glPushMatrix();
	
		glTranslatef(this->getGX(), this->getGY(), 0.0f);
		
		this->DesenharCanhao(offsetYCanhao, larguraCanhao, alturaCanhao);
		this->DesenharCorpo(circulo);
		this->DesenharCabine(circulo);
		
		GLfloat larguraTurbina = larguraCanhao;
		GLfloat alturaTurbina = 4.4f * larguraTurbina;
		GLfloat offsetXTurbina = 2.35f * raioProp;
		
		this->DesenharTurbinas(offsetXTurbina, alturaTurbina, larguraTurbina);
		
		GLfloat larguraAsa = 2.25f * raioProp;
		GLfloat alturaAsa = 1.5f * larguraAsa;
		GLfloat offsetXAsa = 2.125f * raioProp;
		GLfloat offsetYAsa = 0.25f * raioProp;
		
		this->DesenharAsas(offsetXAsa, offsetYAsa, larguraAsa, alturaAsa);
		
		GLfloat larguraCalda = larguraCanhao;
		GLfloat alturaCalda = 4.25f * larguraCalda;
		GLfloat offsetY = raio - (alturaCalda / 2.0f);
		
		this->DesenharCalda(offsetY, larguraCalda, alturaCalda);
		
		GLfloat larguraHelice = 1.4f * raioProp;
		GLfloat alturaHelice = raio / 5.0f;
		GLfloat offsetXHelice = 2.35f * raioProp;
		GLfloat offsetYHelice = 2.125f * raio / 7.0f;
		
		this->DesenharHelices(offsetXHelice, offsetYHelice, larguraHelice, alturaHelice, frametime);
	
	glPopMatrix();
}

void Jogador:: DesenharCanhao(GLfloat offsetY, GLfloat largura, GLfloat altura) {
			
	glPushMatrix();
		
		glRotatef(anguloAviaoGraus - 90, 0.0f, 0.0f, -1.0f);
		glTranslatef(0.0f, -offsetY, 0.0f);
		
		glTranslatef(0.0f, +altura / 2.0f, 0.0f);
		glRotatef(anguloCanhao, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, -altura / 2.0f, 0.0f);
		
		glScalef(largura, altura, 1.0f);
		
		retangulo->Desenhar();
	
	glPopMatrix();
}

void Jogador:: DesenharCorpo(Circulo* circulo) {
		
	glPushMatrix();
	
		glRotatef(anguloAviaoGraus - 90, 0.0f, 0.0f, -1.0f);
		glScalef(proporcaoAviao, 1.0f, 1.0f);
		circulo->Desenhar();
	
	glPopMatrix();
}

void Jogador:: DesenharCabine(Circulo* circulo) {
		
	GLfloat corOriginalR = circulo->getCorR();
	GLfloat corOriginalG = circulo->getCorG();
	GLfloat corOriginalB = circulo->getCorB();
	
	circulo->setCorR(0.0f);
	circulo->setCorG(0.0f);
	circulo->setCorB(0.0f);
	
	glPushMatrix();
	
		glRotatef(anguloAviaoGraus - 90, 0.0f, 0.0f, -1.0f);
		glTranslatef(0.0f, -circulo->getRaio() / 2.0f, 0.0f);
		glScalef(proporcaoAviao / 2.5f, 1.25f * proporcaoAviao, 1.0f);
		circulo->Desenhar();
	
	glPopMatrix();
	
	circulo->setCorR(corOriginalR);
	circulo->setCorG(corOriginalG);
	circulo->setCorB(corOriginalB);
}

void Jogador:: DesenharTurbinas(GLfloat offsetX, GLfloat largura, GLfloat altura) {
	this->DesenharTurbina(-offsetX, largura, altura);
	this->DesenharTurbina(offsetX, largura, altura);
}

void Jogador:: DesenharTurbina(GLfloat offsetX, GLfloat largura, GLfloat altura) {
	
	glPushMatrix();
	
		glRotatef(anguloAviaoGraus - 90, 0.0f, 0.0f, -1.0f);
		glTranslatef(offsetX, 0.0f, 0.0f);
		glScalef(altura, largura, 1.0f);
		retangulo->Desenhar();
	
	glPopMatrix();
}

void Jogador:: DesenharAsas(GLfloat offsetX, GLfloat offsetY, GLfloat largura, GLfloat altura) {
	this->DesenharAsa( -offsetX, offsetY, +largura, altura);
	this->DesenharAsa( +offsetX, offsetY, -largura, altura);
}

void Jogador:: DesenharAsa(GLfloat offsetX, GLfloat offsetY, GLfloat largura, GLfloat altura) {
	
	glPushMatrix();
	
		glRotatef(anguloAviaoGraus - 90, 0.0f, 0.0f, -1.0f);
		glTranslatef(offsetX, offsetY, 0.0f);
		glScalef(largura, altura, 1.0f);
		retangulo->DesenharCisalhado();
	
	glPopMatrix();
}

void Jogador:: DesenharCalda(GLfloat offsetY, GLfloat largura, GLfloat altura) {
	
	glPushMatrix();
	
		glRotatef(anguloAviaoGraus - 90, 0.0f, 0.0f, -1.0f);
		glTranslatef(0.0f, offsetY, 0.0f);
		glScalef(largura, altura, 1.0f);
		retangulo->Desenhar();
	
	glPopMatrix();
}

void Jogador:: DesenharHelices(GLfloat offsetX, GLfloat offsetY, GLfloat largura, GLfloat altura, GLint frametime) {
		
	GLfloat corOriginalR = retangulo->getCorR();
	GLfloat corOriginalG = retangulo->getCorG();
	GLfloat corOriginalB = retangulo->getCorB();
	
	retangulo->setCorR(1.0f);
	retangulo->setCorG(1.0f);
	retangulo->setCorB(0.0f);

	static int i = 0;
	GLdouble grausPorFrame;

	if(decolou == true || emDecolagem == true) {
		grausPorFrame = 360.0f / (velAviao * 1000000.0f);
	} else {
		grausPorFrame = 0.0f;
	}

	GLdouble fpsAlvo = 30;
	GLdouble grausPorSegundo = fpsAlvo * grausPorFrame;
	GLdouble dG = grausPorSegundo * ((GLdouble) frametime);
	static GLdouble anguloGiro = dG;
	anguloGiro += dG;

	this->DesenharHelice( -offsetX, -offsetY, largura, altura, anguloGiro);
	this->DesenharHelice( +offsetX, -offsetY, largura, altura, anguloGiro);

	if(anguloGiro > 360) {
		anguloGiro = 0;
	}

	retangulo->setCorR(corOriginalR);
	retangulo->setCorG(corOriginalG);
	retangulo->setCorB(corOriginalB);
}

void Jogador:: DesenharHelice(GLfloat offsetX, GLfloat offsetY, GLfloat largura, GLfloat altura, GLdouble dG) {
	
	glPushMatrix();
	
		glRotatef(anguloAviaoGraus - 90, 0.0f, 0.0f, -1.0f);
		glTranslatef(offsetX, offsetY, 0.0f);
		glRotatef(dG, 0.0f, 0.0f, 1.0f);
		glScalef(largura, altura, 1.0f);

		retangulo->DesenharHelice();
	
	glPopMatrix();
}

Jogador:: ~Jogador() {
	delete retangulo;
}
