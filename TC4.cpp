/*
 * Arquivo: TC4.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC4
*/

#include <iostream>
#include <cmath>
#include <string>
#include "TC4.h"

Erros TC4:: LeituraArquivos(const char* chArqConfig) {
	
	XMLDocument xmlConfig;
	XMLError erroLoad = xmlConfig.LoadFile(chArqConfig);

	// erroLoad recebe XML_SUCCESS se "LoadFile" for bem sucedida.
	if( erroLoad != XML_SUCCESS ) {
		return ERRO_ABERTURA_CONFIG_XML;
	}
	
	Erros erroRead = LeituraConfig(xmlConfig);
	
	if( erroRead != SUCESSO ) {
		return erroRead;
	}
	
	XMLDocument xmlArena;
	string strArqArena = arena->getNomeArquivo();
	const char* chArqArena = strArqArena.c_str();
	erroLoad = xmlArena.LoadFile(chArqArena);
	
	if( erroLoad != XML_SUCCESS ) {
		return ERRO_ABERTURA_ARENA_SVG;
	}
	
	erroRead = LeituraArena(xmlArena);
	
	if( erroRead != SUCESSO ) {
		return erroRead;
	}
	
	return SUCESSO;
}

Erros TC4:: LeituraConfig(XMLDocument& xmlConfig) {

	XMLNode* raiz = xmlConfig.FirstChild();

	/*
	 * Lendo a configuracao do arquivo a ser lido:
	 */

	XMLElement* elemento1 = raiz->FirstChildElement("arquivoDaArena");
	if(elemento1 == 0) return ERRO_LEITURA_CONFIG_XML;

	XMLElement* elemento2 = elemento1->FirstChildElement("nome");
	if(elemento2 == 0) return ERRO_LEITURA_CONFIG_XML;
	const char* nome = elemento2->GetText();
	if(nome[0] == '\0') return ERRO_LEITURA_CONFIG_XML;

	elemento2 = elemento1->FirstChildElement("tipo");
	if(elemento2 == 0) return ERRO_LEITURA_CONFIG_XML;
	const char* tipo = elemento2->GetText();
	if(tipo[0] == '\0') return ERRO_LEITURA_CONFIG_XML;

	elemento2 = elemento1->FirstChildElement("caminho");
	if(elemento2 == 0) return ERRO_LEITURA_CONFIG_XML;
	const char* caminho = elemento2->GetText();
	if(caminho[0] == '\0') return ERRO_LEITURA_CONFIG_XML;

	string strNome(nome);
	string strTipo(tipo);
	string strCaminho(caminho);
	string arquivo = strCaminho + strNome + "." + strTipo;
	
	janela = new Janela();
	janela->setTitulo(strNome);
	
	arena = new Arena();
	arena->setNomeArquivo(arquivo);
	
	/*
	 * Lendo o multiplicador da velocidade do aviao jogador:
	 */

	elemento1 = raiz->FirstChildElement("jogador");
	if(elemento1 == 0) return ERRO_LEITURA_CONFIG_XML;

	GLfloat multVelAviao;
	if(elemento1->QueryFloatAttribute("vel", &multVelAviao)) return ERRO_LEITURA_CONFIG_XML;
	
	jogador = new Jogador();
	jogador->setMultVelAviao(multVelAviao);
	
	/*
	 * Lendo o multiplicador da velocidade do tiro do jogador:
	 */

	GLfloat multVelTiro;
	if(elemento1->QueryFloatAttribute("velTiro", &multVelTiro)) return ERRO_LEITURA_CONFIG_XML;
	
	jogador->setMultVelTiro(multVelTiro);
	
	/*
	 * Lendo os dados dos inimigos:
	 */
	
	elemento1 = raiz->FirstChildElement("inimigo");
	if(elemento1 == 0) return ERRO_LEITURA_CONFIG_XML;
	
	if(elemento1->QueryFloatAttribute("freqTiro", &inimFreqTiro)) return ERRO_LEITURA_CONFIG_XML;
	if(elemento1->QueryFloatAttribute("vel", &inimVel)) return ERRO_LEITURA_CONFIG_XML;
	if(elemento1->QueryFloatAttribute("velTiro", &inimVelTiro)) return ERRO_LEITURA_CONFIG_XML;
	
	return SUCESSO;
}

Erros TC4:: LeituraArena(XMLDocument& xmlArena) {

	XMLNode* raiz = xmlArena.FirstChild();
	XMLNode* svg = raiz->NextSibling();

	GLfloat cX;
	GLfloat cY;
	GLfloat r;
	const char* fill;
	XMLElement* elemento;

	elemento = svg->FirstChildElement("circle");
	if(elemento == 0) return ERRO_LEITURA_ARENA_SVG;

	do {

		elemento->QueryFloatAttribute("cx", &cX);
		elemento->QueryFloatAttribute("cy", &cY);
		elemento->QueryFloatAttribute("r", &r);
		fill = elemento->Attribute("fill");

		Cor cor;
		if(strcmp(fill, "red") == 0) cor = RED;
		if(strcmp(fill, "green") == 0) cor = GREEN;
		if(strcmp(fill, "blue") == 0) cor = BLUE;
		if(strcmp(fill, "orange") == 0) cor = ORANGE;

		GLfloat rgb[3];
		switch(cor) {
			case RED:
				rgb[0] = 1.0f; rgb[1] = 0.0f; rgb[2] = 0.0f; break;
			case GREEN:
				rgb[0] = 0.0f; rgb[1] = 1.0f; rgb[2] = 0.0f; break;
			case BLUE:
				rgb[0] = 0.0f; rgb[1] = 0.0f; rgb[2] = 1.0f; break;
			case ORANGE:
				rgb[0] = 1.0f; rgb[1] = 0.647f; rgb[2] = 0.0f; break;
			default:
				return ERRO_LEITURA_ARENA_SVG;
		}

		Circulo* circulo = new Circulo(rgb[0], rgb[1], rgb[2]);
		circulo->setRaioInicial(r);
		circulo->setRaio(r);

		switch(cor) {

			case RED: {
				InimigoAviao* inimigoAviao = new InimigoAviao();
				inimigoAviao->setCirculo(circulo);
				inimigoAviao->setGX(cX);
				inimigoAviao->setGY(cY);
				inimigoAviao->setFreqTiro(inimFreqTiro);
				inimigoAviao->setMultVelAviao(inimVel);
				inimigoAviao->setMultVelTiro(inimVelTiro);
				AdicionarInimigoAviao(inimigoAviao);
				break;
			}

			case GREEN:
				jogador->setCirculo(circulo);
				jogador->setGXInicial(cX);
				jogador->setGX(cX);
				jogador->setGYInicial(cY);
				jogador->setGY(cY);
				break;

			case BLUE:
				arena->setCirculo(circulo);
				arena->setGX(cX);
				arena->setGY(cY);
				janela->setXI(cX - circulo->getRaio());
				janela->setXF(cX + circulo->getRaio());
				janela->setYI(cY + circulo->getRaio());
				janela->setYF(cY - circulo->getRaio());
				break;

			case ORANGE: {
				InimigoBase* inimigoBase = new InimigoBase();
				inimigoBase->setCirculo(circulo);
				inimigoBase->setGX(cX);
				inimigoBase->setGY(cY);
				AdicionarInimigoBase(inimigoBase);
				break;
			}

			default:
				delete circulo;
				return ERRO_LEITURA_ARENA_SVG;
		}

		elemento = elemento->NextSiblingElement("circle");

	} while(elemento != 0);

	elemento = svg->FirstChildElement("line");
	if(elemento == 0) return ERRO_LEITURA_ARENA_SVG;

	GLfloat x1, y1;
	GLfloat x2, y2;

	elemento->QueryFloatAttribute("x1", &x1);
	elemento->QueryFloatAttribute("y1", &y1);
	elemento->QueryFloatAttribute("x2", &x2);
	elemento->QueryFloatAttribute("y2", &y2);
	
	GLdouble tangente = 0.0f;
	GLdouble anguloLinhaRadianos;
	GLdouble anguloLinhaGraus;
	
	if(x1 <= x2 && y1 <= y2) {
		tangente = - (y2 - y1) / (x2 - x1);
		anguloLinhaRadianos = 360.0f + atan(tangente);
	}
	if(x1 <= x2 && y1  > y2) {
		tangente = + (y1 - y2) / (x2 - x1);
		anguloLinhaRadianos = atan(tangente);
	}
	if(x1  > x2 && y1 <= y2) {
		tangente = - (y2 - y1) / (x1 - x2);
		anguloLinhaRadianos = 180.0f + atan(tangente);
	}
	if(x1  > x2 && y1  > y2) {
		tangente = + (y1 - y2) / (x1 - x2);
		anguloLinhaRadianos = 180.0f + atan(tangente);
	}
	
	anguloLinhaGraus = anguloLinhaRadianos * 180.0f / 3.14159f;
	
	GLdouble anguloAviaoRadianos = anguloLinhaRadianos;
	GLdouble anguloAviaoGraus = anguloLinhaGraus;
	jogador->setAnguloAviaoGrausInicial(anguloAviaoGraus);
	jogador->setAnguloAviaoGraus(anguloAviaoGraus);
	jogador->setAnguloAviaoRadianos(anguloAviaoRadianos);
	
	pista = new Pista(0.0f, 0.0f, 0.0f);
	pista->setX1(x1);
	pista->setY1(y1);
	pista->setX2(x2);
	pista->setY2(y2);

	return SUCESSO;
}

void TC4:: AdicionarInimigoAviao(InimigoAviao* inimigoAviao) {
	inimigosAviao.push_back(inimigoAviao);
}

void TC4:: AdicionarInimigoBase(InimigoBase* inimigoBase) {
	inimigosBase.push_back(inimigoBase);
}

void TC4:: setFrametime(GLint frametime) {
	this->frametime = frametime;
}

void TC4:: setColisaoInimigo(bool colisaoInimigo) {
	this->colisaoInimigo = colisaoInimigo;
}

bool TC4:: getColisaoInimigo(void) {
	return colisaoInimigo;
}

void TC4:: DesenharArenaCirculo(void) {
	arena->DesenharCirculo();
}

void TC4:: DesenharArenaContorno(void) {
	arena->DesenharContorno();
}

void TC4:: DesenharJogador(void) {
	jogador->Desenhar(frametime);
}

void TC4:: DesenharPista(void) {
	pista->Desenhar();
}

void TC4:: DesenharInimigosAviao(void) {
	list<InimigoAviao*>::iterator itr;
	for(itr = inimigosAviao.begin(); itr != inimigosAviao.end(); ++itr) {
		(*itr)->Desenhar(frametime);
	}
}

void TC4:: DesenharInimigosBase(void) {
	list<InimigoBase*>::iterator itr;
	for(itr = inimigosBase.begin(); itr != inimigosBase.end(); ++itr) {
		(*itr)->Desenhar();
	}
}

void TC4:: DesenharTiros(void) {
	vector<Tiro*>::iterator itr;
	for(itr = tiros.begin(); itr != tiros.end(); itr++) {
		(*itr)->Desenhar();
	}
}

void TC4:: DesenharBombas(void) {
	vector<Bomba*>::iterator itr;
	for(itr = bombas.begin(); itr != bombas.end(); itr++) {
		(*itr)->Desenhar();
	}
}

void TC4:: KeyDown(unsigned char key) {
	keyStatus[key] = 1;
}

void TC4:: KeyUp(unsigned char key) {
	if(key != keyDecolar) {
		keyStatus[key] = 0;
	}
}

bool TC4:: PossivelConflito(GLint tipo) {
	
	GLfloat gX = jogador->getGX();
	GLfloat gY = jogador->getGY();
	GLfloat anguloAviaoRadianos = jogador->getAnguloAviaoRadianos();
	GLfloat multVelAviao = jogador->getMultVelAviao();
	GLfloat vX = multVelAviao * jogador->getVelAviao() * cos(anguloAviaoRadianos);
	GLfloat vY = multVelAviao * jogador->getVelAviao() * (- sin(anguloAviaoRadianos));
	GLfloat dX = vX * frametime;
	GLfloat dY = vY * frametime;
	
	GLfloat possivelGX = gX + dX;
	GLfloat possivelGY = gY + dY;
	
	Circulo* circulo = jogador->getCirculo();
	GLfloat raio = circulo->getRaio();
	
	switch(tipo) {
		case 1:
			return PossivelConflitoInimigos(raio, possivelGX, possivelGY);
			break;
		case 2:
			return PossivelConflitoArena(raio, possivelGX, possivelGY);
			break;
	}
}

bool TC4:: PossivelConflitoArena(GLfloat raio, GLfloat x, GLfloat y) {
	
	if(arena->ExisteConflito(raio, x, y) == true) {
		return true;
	} else {
		return false;
	}
}

bool TC4:: PossivelConflitoInimigos(GLfloat raio, GLfloat x, GLfloat y) {
	
	list<InimigoAviao*>::iterator itr;
	for(itr = inimigosAviao.begin(); itr != inimigosAviao.end(); ++itr) {
			
		InimigoAviao* inimigoAviao = *itr;
		if(inimigoAviao->ExisteConflito(raio, x, y) == true) {
			return true;
		}
	}
	
	return false;
}

void TC4:: AtualizarJogador(void) {
	
	if(keyStatus[keyReset] == 0) {
	
		if(jogador->getDecolou() == true && colisaoInimigo == false) {
			
			if((keyStatus[keyVelUp] == 1 || keyStatus[keyNumpadVelUp] == 1)
				&& (keyStatus[keyVelDown] == 0 || keyStatus[keyNumpadVelDown] == 0)) {
				jogador->AjustarMultVelAviao( +ajusteMult);
				jogador->AjustarMultVelTiro( +ajusteMult);
			}
			
			if((keyStatus[keyVelUp] == 0 || keyStatus[keyNumpadVelUp] == 0)
				&& (keyStatus[keyVelDown] == 1 || keyStatus[keyNumpadVelDown] == 1)) {
				jogador->AjustarMultVelAviao( -ajusteMult);
				jogador->AjustarMultVelTiro( -ajusteMult);
			}
			
			if(this->PossivelConflito(2) == true) {
				
				if(keyStatus[keyEsquerda] == 1 && keyStatus[keyDireita] == 0) {
					jogador->AjustarAnguloAviao( +frametime);
					
				} else if(keyStatus[keyEsquerda] == 0 && keyStatus[keyDireita] == 1){
					jogador->AjustarAnguloAviao( -frametime);
				}
				
				jogador->Mover(frametime);
				
			} else {
				this->TeleportarJogador();
			}
					
		} else {
			
			if(keyStatus[keyDecolar] == 1) {
				jogador->Decolar(frametime, pista->getX2(), pista->getY2());
			}
		}
		
	} else {
		this->Reset();
	}
}

void TC4:: AtualizarTiros(void) {
	
	if(tiros.size() > 0) {
		
		vector<Tiro*>::iterator itr = tiros.begin();
		
		while(itr != tiros.end()) {
			
			Tiro* tiro = *itr;
			Circulo* circulo = tiro->getCirculo();
			GLfloat raio = circulo->getRaio();
			GLfloat x = tiro->getGX();
			GLfloat y = tiro->getGY();
			
			if(arena->ExisteConflito(raio, x, y) == true) {
				tiro->Mover(frametime);
				itr++;
			} else {
				delete(*itr);
				itr = tiros.erase(itr);
			}
		}
	}
}

void TC4:: AtualizarBombas(void) {
	
	if(bombas.size() > 0) {
		
		vector<Bomba*>::iterator itr = bombas.begin();
		
		while(itr != bombas.end()) {
			
			Bomba* bomba = *itr;
			Circulo* circulo = bomba->getCirculo();
			GLfloat raioAtual = circulo->getRaio();
			GLfloat vel = bomba->getVel();
			GLfloat acel = bomba->getAcel();
			GLfloat x = bomba->getGX();
			GLfloat y = bomba->getGY();
			
			bomba->Mover(frametime);
			
			GLfloat novaVel = vel + (acel * frametime);
			
			if(novaVel > 0.0f && arena->ExisteConflito(raioAtual, x, y) == true) {
				
				GLfloat raioInicial = circulo->getRaioInicial();
				
				GLfloat vR = raioInicial / 8000.0f;
				GLfloat dR = vR * frametime;
				
				circulo->setRaio(raioAtual - dR);
				bomba->setVel(novaVel);
				
				itr++;
				
			} else {
				delete bomba;
				itr = bombas.erase(itr);
			}
		}
	}
}

void TC4:: AtualizarMousePosicao(GLint x, GLint y) {
	
	GLint dX = x - mX;
	
	if(dX != 0) {
		jogador->AjustarAnguloCanhao(dX);
	}
	
	this->mX = x;
	this->mY = y;
}

void TC4:: AtualizarMouseBotoes(GLint button, GLint state) {
	
	if(jogador->getDecolou() == true && colisaoInimigo == false) {
		
		if(state == GLUT_DOWN) {
			
			if(button == GLUT_LEFT_BUTTON) {
				Tiro* tiro = jogador->Atirar();
				tiros.push_back(tiro);
			}
			
			if(button == GLUT_RIGHT_BUTTON) {
				Bomba* bomba = jogador->Bombardear();
				bombas.push_back(bomba);
			}
		}
	}
}

void TC4:: TeleportarJogador(void) {
	
	Circulo* circuloArena = arena->getCirculo();
	GLfloat centroXArena = arena->getGX();
	GLfloat centroYArena = arena->getGY();
	GLfloat raioArena = circuloArena->getRaio();
	
	Circulo* circuloJogador = jogador->getCirculo();
	GLfloat raioJogador = circuloJogador->getRaio();
	
	GLdouble anguloAviaoRadianos = jogador->getAnguloAviaoRadianos();
	GLfloat gX = - (centroXArena - jogador->getGX());
	GLfloat gY = centroYArena - jogador->getGY();
	
	GLfloat tangenteAnguloAviao = tan(anguloAviaoRadianos);
	GLfloat a = tangenteAnguloAviao;
	GLfloat b = - 1.0f;
	GLfloat c = 0;
	
	GLfloat distRetaAviao = DistanciaPontoAReta(gX, gY, a, b, c);
	
	GLfloat distCentroAviao = raioArena + raioJogador;
	GLfloat pitagoras = (GLfloat) sqrt(pow(distCentroAviao, 2) - pow(distRetaAviao, 2));
	
	GLfloat velAviao = jogador->getVelAviao();
	GLfloat multVelAviao = jogador->getMultVelAviao();
	GLfloat deslocamento = - ((2.0f * pitagoras) / (velAviao * multVelAviao)) + 10.0f;
	
	jogador->Mover(deslocamento);
}

GLfloat TC4:: DistanciaPontoAReta(GLfloat x, GLfloat y, GLfloat a, GLfloat b, GLfloat c) {
	GLfloat num = abs((a * x) + (b * y) + c);
	GLfloat den = (GLfloat) sqrt(pow(a, 2) + pow(b, 2));
	GLfloat resultado = num / den;
	return resultado;
}

void TC4:: Reset(void) {
	
	keyStatus[keyDecolar] = 0;
	colisaoInimigo = false;
	
	jogador->setEmDecolagem(false);
	jogador->setDecolou(false);
	jogador->setVelAviao(0.0f);
	jogador->setMultVelAviao(jogador->getMultVelAviaoInicial());
	jogador->setMultVelTiro(jogador->getMultVelTiroInicial());
	
	Circulo* circulo = jogador->getCirculo();
	circulo->setRaio( circulo->getRaioInicial() );
	
	jogador->setGX( jogador->getGXInicial() );
	jogador->setGY( jogador->getGYInicial() );
	
	jogador->setAnguloAviaoGraus( jogador->getAnguloAviaoGrausInicial() );
	jogador->setAnguloAviaoRadianos( jogador->getAnguloAviaoGrausInicial() * 3.14159f / 180.0f);
	
	this->LiberarTiros();
	this->LiberarBombas();
	tiros.clear();
	bombas.clear();
}

void TC4:: LiberarTiros(void) {
	
	if(tiros.size() > 0) {
		
		vector<Tiro*>::iterator itr = tiros.begin();
		
		while(itr != tiros.end()) {
			delete *itr;
			itr = tiros.erase(itr);
		}
	}
}

void TC4:: LiberarBombas(void) {
	
	if(bombas.size() > 0) {
		
		vector<Bomba*>::iterator itr = bombas.begin();
		
		while(itr != bombas.end()) {
			delete *itr;
			itr = bombas.erase(itr);
		}
	}
}

TC4:: ~TC4() {
	
	delete janela;
	delete jogador;
	delete arena;
	delete pista;
	
	this->LiberarTiros();
	this->LiberarBombas();
	
	if(inimigosAviao.size() > 0) {
		
		list<InimigoAviao*>::iterator itr = inimigosAviao.begin();
		
		while(itr != inimigosAviao.end()) {
			delete *itr;
			itr = inimigosAviao.erase(itr);
		}
	}
	
	if(inimigosBase.size() > 0) {
		
		list<InimigoBase*>::iterator itr = inimigosBase.begin();
		
		while(itr != inimigosBase.end()) {
			delete *itr;
			itr = inimigosBase.erase(itr);
		}
	}
}
