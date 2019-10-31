/*
 * Arquivo: Jogador.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC4
*/

#include <cmath>
#include "Jogador.h"

using namespace std;

void Jogador:: setMultVelAviaoInicial(GLfloat multVelAviaoInicial) {
	this->multVelAviaoInicial = multVelAviaoInicial;
}

void Jogador:: setMultVelAviao(GLfloat multVelAviao) {
	this->multVelAviao = multVelAviao;
}

void Jogador:: setMultVelTiroInicial(GLfloat multVelTiroInicial) {
	this->multVelTiroInicial = multVelTiroInicial;
}

void Jogador:: setMultVelTiro(GLfloat multVelTiro) {
	this->multVelTiro = multVelTiro;
}

void Jogador:: setAnguloAviaoGrausInicial(GLdouble anguloAviaoGrausInicial) {
	this->anguloAviaoGrausInicial = anguloAviaoGrausInicial;
}

void Jogador:: setAnguloAviaoGraus(GLdouble anguloAviaoGraus) {
	this->anguloAviaoGraus = anguloAviaoGraus;
}

void Jogador:: setAnguloAviaoRadianos(GLdouble anguloAviaoRadianos) {
	this->anguloAviaoRadianos = anguloAviaoRadianos;
}

void Jogador:: setDecolou(bool decolou) {
	this->decolou = decolou;
}

void Jogador:: setEmDecolagem(bool emDecolagem) {
	this->emDecolagem = emDecolagem;
}

void Jogador:: setVelAviao(GLfloat velAviao) {
	this->velAviao = velAviao;
}

GLfloat Jogador:: getMultVelAviaoInicial(void) const {
	return multVelAviaoInicial;
}

GLfloat Jogador:: getMultVelAviao(void) const {
	return multVelAviao;
}

GLfloat Jogador:: getMultVelTiroInicial(void) const {
	return multVelTiroInicial;
}

GLfloat Jogador:: getMultVelTiro(void) const {
	return multVelTiro;
}

GLdouble Jogador:: getAnguloCanhaoGraus(void) const {
	return anguloCanhaoGraus;
}

GLdouble Jogador:: getAnguloCanhaoRadianos(void) const {
	return anguloCanhaoRadianos;
}

GLdouble Jogador:: getAnguloAviaoGraus(void) const {
	return anguloAviaoGraus;
}

GLdouble Jogador:: getAnguloAviaoGrausInicial(void) const {
	return anguloAviaoGrausInicial;
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
	this->MoverAviaoX(frametime);
	this->MoverAviaoY(frametime);
}

void Jogador:: AjustarAnguloAviao(GLint frametime) {
	
	GLfloat vAngAviao = 0.1f + velAviao / 2.5f;
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

void Jogador:: AjustarAnguloCanhao(GLint dX) {
	
	GLfloat vAngCanhao = 0.5f;
	GLfloat dA = vAngCanhao * (GLfloat) dX;
	
	anguloCanhaoGraus += dA;
	
	if(anguloCanhaoGraus > 45.0f) {
		anguloCanhaoGraus = 45.0f;
	} else if(anguloCanhaoGraus < -45.0f) {
		anguloCanhaoGraus = -45.0f;
	}
	
	anguloCanhaoRadianos = anguloCanhaoGraus * 3.14159f / 180.0f;
}

void Jogador:: AjustarMultVelAviao(GLfloat dM) {
	if((multVelAviao + dM) >= 0.1f) {
		multVelAviao += dM;
	}
}

void Jogador:: AjustarMultVelTiro(GLfloat dM) {
	if((multVelTiro + dM) >= 0.1f) {
		multVelTiro += dM;
	}
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
		velAviao = vResultante;
	}
}

void Jogador:: MoverAviaoX(GLint frametime) {
	GLdouble vX = cos(anguloAviaoRadianos) * (GLdouble) velAviao * (GLdouble) multVelAviao;
	GLdouble dX = vX * (GLdouble) frametime;
	this->MoverX(dX);
}

void Jogador:: MoverAviaoY(GLint frametime) {
	GLdouble vY = - sin(anguloAviaoRadianos) * (GLdouble) velAviao * (GLdouble) multVelAviao;
	GLdouble dY = vY * (GLdouble) frametime;
	this->MoverY(dY);
}

Tiro* Jogador:: Atirar(void) {
	
	GLfloat aviaoX = this->getGX();
	GLfloat aviaoY = this->getGY();
	
	GLfloat correcaoAnguloCanhao = anguloAviaoRadianos - anguloCanhaoRadianos;
	
	GLfloat correcaoXAviao = cos(anguloAviaoRadianos) * offsetYCanhao;
	GLfloat correcaoXCanhao = cos(correcaoAnguloCanhao) * (alturaCanhao / 2.0f);
	
	GLfloat correcaoYAviao = - sin(anguloAviaoRadianos) * offsetYCanhao;
	GLfloat correcaoYCanhao = - sin(correcaoAnguloCanhao) * (alturaCanhao / 2.0f);
	
	GLfloat tiroX = aviaoX + correcaoXAviao + correcaoXCanhao;
	GLfloat tiroY = aviaoY + correcaoYAviao + correcaoYCanhao;
	
	Tiro* tiro = new Tiro();
	
	tiro->setGXInicial(tiroX);
	tiro->setGX(tiroX);
	tiro->setGYInicial(tiroY);
	tiro->setGY(tiroY);
	tiro->setVel(1.25f * velAviao);
	tiro->setMultVel(multVelTiro);
	tiro->setAnguloTrajetoriaRad(correcaoAnguloCanhao);
	
	Circulo* circulo = new Circulo(1.0f, 1.0f, 1.0f);
	
	circulo->setRaioInicial(larguraCanhao);
	circulo->setRaio(larguraCanhao);
	
	tiro->setCirculo(circulo);
	
	return tiro;
}

Bomba* Jogador:: Bombardear(void) {
	
	GLfloat aviaoX = this->getGX();
	GLfloat aviaoY = this->getGY();
	
	Circulo* circuloBomba = new Circulo(1.0f, 1.0f, 1.0f);
	Circulo* circuloJogador = this->getCirculo();
	GLfloat raioBomba = circuloJogador->getRaio() / 2.0f;
	
	circuloBomba->setRaioInicial(raioBomba);
	circuloBomba->setRaio(raioBomba);
	
	GLfloat acel = - velAviao / 4000.0f;
	
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

void Jogador:: Desenhar(GLint frametime) {
	
	Circulo* circulo = this->getCirculo();
	GLfloat raio = circulo->getRaio();
	GLfloat raioProp = proporcaoAviao * raio;
		
	larguraCanhao = raio / 7.0f;
	alturaCanhao = 2.5f * larguraCanhao;
	offsetYCanhao = raio + (0.5f * alturaCanhao);
	
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
		glRotatef(anguloCanhaoGraus, 0.0f, 0.0f, 1.0f);
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

	GLdouble grausPorFrame;
	
	if(decolou == true || emDecolagem == true) {
		grausPorFrame = 360.0f * (velAviao * multVelAviao) / 1000.0f;
	} else {
		grausPorFrame = 0.0f;
	}

	GLdouble fpsAlvo = 30;
	GLdouble grausPorSegundo = fpsAlvo * grausPorFrame;
	GLdouble dG = grausPorSegundo * ((GLdouble) frametime);
	static GLdouble anguloGiro = dG;
	
	anguloGiro += dG;
	
	if(decolou == false && emDecolagem == false) {
		anguloGiro = 0.0f;
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
