/*
 * Arquivo: TC3.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC3
*/

#include <iostream>
#include <cmath>
#include <string>
#include "TC3.h"

Erros TC3:: LeituraArquivos(const char* chArqConfig) {
	
	XMLDocument xmlConfig;
	XMLError erroLoad = xmlConfig.LoadFile(chArqConfig);

	// erroLoad recebe XML_SUCCESS se "LoadFile" for bem sucedida.
	if( erroLoad != XML_SUCCESS ) {
		return ERRO_ABERTURA_CONFIG_XML;
	}
	
	Erros erroRead = LeituraConfig(xmlConfig);
	
	if( erroRead != SUCESSO ) {
		return ERRO_LEITURA_CONFIG_XML;
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
		return ERRO_LEITURA_ARENA_SVG;
	}
	
	return SUCESSO;
}

Erros TC3:: LeituraConfig(XMLDocument& xmlConfig) {

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
	 * Lendo o multiplicador da velocidade do jogador:
	 */

	elemento1 = raiz->FirstChildElement("jogador");
	if(elemento1 == 0) return ERRO_LEITURA_CONFIG_XML;

	GLfloat multVelAviao;
	if(elemento1->QueryFloatAttribute("vel", &multVelAviao)) return ERRO_LEITURA_CONFIG_XML;
	
	GLfloat multVelTiro;
	if(elemento1->QueryFloatAttribute("velTiro", &multVelTiro)) return ERRO_LEITURA_CONFIG_XML;
	
	jogador = new Jogador();
	jogador->setMultVelAviao(multVelAviao);
	jogador->setMultVelTiro(multVelTiro);

	return SUCESSO;
}

Erros TC3:: LeituraArena(XMLDocument& xmlArena) {

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
				Inimigo* inimigo = new Inimigo();
				inimigo->setCirculo(circulo);
				inimigo->setGX(cX);
				inimigo->setGY(cY);
				AdicionarInimigoVoador(inimigo);
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
				Inimigo* inimigo = new Inimigo();
				inimigo->setCirculo(circulo);
				inimigo->setGX(cX);
				inimigo->setGY(cY);
				AdicionarInimigoTerrestre(inimigo);
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

void TC3:: AdicionarInimigoVoador(Inimigo* inimigo) {
	inimigosVoadores.push_back(inimigo);
}

void TC3:: AdicionarInimigoTerrestre(Inimigo* inimigo) {
	inimigosTerrestres.push_back(inimigo);
}

void TC3:: setFrametime(GLint frametime) {
	this->frametime = frametime;
}

void TC3:: setColisaoInimigo(bool colisaoInimigo) {
	this->colisaoInimigo = colisaoInimigo;
}

bool TC3:: getColisaoInimigo(void) {
	return colisaoInimigo;
}

void TC3:: DesenharArena(void) {
	arena->Desenhar();
}

void TC3:: DesenharJogador(void) {
	jogador->Desenhar(frametime);
}

void TC3:: DesenharPista(void) {
	pista->Desenhar();
}

void TC3:: DesenharInimigosVoadores(void) {
	DesenharInimigos(inimigosVoadores);
}

void TC3:: DesenharInimigosTerrestres(void) {
	DesenharInimigos(inimigosTerrestres);
}

void TC3:: DesenharInimigos(list<Inimigo*>& listaInimigos) {
	list<Inimigo*>::iterator itr;
	for(itr = listaInimigos.begin(); itr != listaInimigos.end(); ++itr) {
		(*itr)->Desenhar();
	}
}

void TC3:: DesenharTiros(void) {
	vector<Tiro*>::iterator itr;
	for(itr = tiros.begin(); itr != tiros.end(); itr++) {
		(*itr)->Desenhar();
	}
}

void TC3:: KeyDown(unsigned char key) {
	keyStatus[key] = 1;
}

void TC3:: KeyUp(unsigned char key) {
	if(key != keyDecolar) {
		keyStatus[key] = 0;
	}
}

bool TC3:: PossivelConflito(GLint tipo) {
	
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

bool TC3:: PossivelConflitoArena(GLfloat raio, GLfloat x, GLfloat y) {
	
	if(arena->ExisteConflito(raio, x, y, true) == true) {
		return true;
	} else {
		return false;
	}
}

bool TC3:: PossivelConflitoInimigos(GLfloat raio, GLfloat x, GLfloat y) {

	list<Inimigo*>::iterator itr;
	for(itr = inimigosVoadores.begin(); itr != inimigosVoadores.end(); ++itr) {
		
		Inimigo* inimigo = *itr;
		if(inimigo->ExisteConflito(raio, x, y) == true) {
			return true;
		}
	}
	
	return false;
}

void TC3:: AtualizarJogador(void) {
	
	if(keyStatus[keyReset] == 0) {
	
		if(jogador->getDecolou() == true && colisaoInimigo == false) {
			
			if(this->PossivelConflito(2) == false) {
				
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

void TC3:: AtualizarTiros(void) {
	
	if(tiros.size() > 0) {
		
		vector<Tiro*>::iterator itr = tiros.begin();
		
		while(itr != tiros.end()) {
			
			Tiro* tiro = *itr;
			Circulo* circulo = tiro->getCirculo();
			GLfloat raio = circulo->getRaio();
			GLint x = tiro->getGX();
			GLint y = tiro->getGY();
			
			if(arena->ExisteConflito(raio, x, y, true) == false) {
				tiro->Mover(frametime);
				itr++;
			} else {
				delete(*itr);
				itr = tiros.erase(itr);
			}
		}
	}
}

void TC3:: AtualizarMousePosicao(GLint x, GLint y) {
	
	GLint dX = x - mX;
	
	if(dX != 0) {
		jogador->AjustarAnguloCanhao(dX);
	}
	
	this->mX = x;
	this->mY = y;
}

void TC3:: AtualizarMouseBotoes(GLint button, GLint state) {
	
	if(jogador->getDecolou() == true && colisaoInimigo == false) {
		
		if(state == GLUT_DOWN) {
			
			if(button == GLUT_LEFT_BUTTON) {
				Tiro* tiro = jogador->Atirar();
				tiros.push_back(tiro);
			}
			
			if(button == GLUT_RIGHT_BUTTON) {
				// jogador->Bombardear(frametime);
			}
		}
	}
}

void TC3:: TeleportarJogador(void) {
	
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

GLfloat TC3:: DistanciaPontoAReta(GLfloat x, GLfloat y, GLfloat a, GLfloat b, GLfloat c) {
	GLfloat num = abs((a * x) + (b * y) + c);
	GLfloat den = (GLfloat) sqrt(pow(a, 2) + pow(b, 2));
	GLfloat resultado = num / den;
	return resultado;
}

void TC3:: Reset(void) {
	
	keyStatus[keyDecolar] = 0;
	colisaoInimigo = false;
	
	jogador->setEmDecolagem(false);
	jogador->setDecolou(false);
	jogador->setVelAviao(0.0f);
	
	Circulo* circulo = jogador->getCirculo();
	circulo->setRaio( circulo->getRaioInicial() );
	
	jogador->setGX( jogador->getGXInicial() );
	jogador->setGY( jogador->getGYInicial() );
	
	jogador->setAnguloAviaoGraus( jogador->getAnguloAviaoGrausInicial() );
	jogador->setAnguloAviaoRadianos( jogador->getAnguloAviaoGrausInicial() * 3.14159f / 180.0f);
	
	this->LiberarTiros();
	tiros.clear();
}

void TC3:: LiberarTiros(void) {
	
	if(tiros.size() > 0) {
		
		vector<Tiro*>::iterator itr = tiros.begin();
		
		while(itr != tiros.end()) {
			delete *itr;
			itr = tiros.erase(itr);
		}
	}
}

void TC3:: LiberarListaInimigos(list<Inimigo*>& listaInimigos) {
	
	if(listaInimigos.size() > 0) {
		
		list<Inimigo*>::iterator itr = listaInimigos.begin();
		
		while(itr != listaInimigos.end()) {
			delete *itr;
			itr = listaInimigos.erase(itr);
		}
	}
}

TC3:: ~TC3() {
	delete janela;
	delete jogador;
	delete arena;
	delete pista;
	this->LiberarListaInimigos(inimigosVoadores);
	this->LiberarListaInimigos(inimigosTerrestres);
	this->LiberarTiros();
}
