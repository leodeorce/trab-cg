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
				jogador->setGX(cX);
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

void TC3:: DesenharArena(void) {
	arena->Desenhar();
}

void TC3:: DesenharJogador(void) {
	jogador->Desenhar();
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

void TC3:: KeyDown(unsigned char key) {
	keyStatus[key] = 1;
}

void TC3:: KeyUp(unsigned char key) {
	if(key != keyDecolar) {
		keyStatus[key] = 0;
	}
}

bool TC3:: PossivelConflito(GLfloat frametime) {
		
	GLfloat gX = jogador->getGX();
	GLfloat gY = jogador->getGY();
	GLfloat anguloAviao = jogador->getAnguloAviaoRadianos();
	GLfloat vX = jogador->getVFinal() * cos(anguloAviao);
	GLfloat vY = jogador->getVFinal() * sin(anguloAviao);
	GLfloat dX = vX * frametime;
	GLfloat dY = vY * frametime;
	
	GLfloat possivelGX = gX + dX;
	GLfloat possivelGY = gY + dY;
	
	return PossivelConflitoInimigos(possivelGX, possivelGY) || PossivelConflitoArena(possivelGX, possivelGY);
}

bool TC3:: PossivelConflitoInimigos(GLfloat x, GLfloat y) {
	
	list<Inimigo*>::iterator itr;
	Circulo* circulo = jogador->getCirculo();
	GLfloat raio = circulo->getRaio();
		
	for(itr = inimigosVoadores.begin(); itr != inimigosVoadores.end(); ++itr) {
		
		Inimigo* inimigo = *itr;
		
		if(inimigo->ExisteConflito(raio, x, y) == true) {
			return true;
		}
	}
	
	return false;
}

bool TC3:: PossivelConflitoArena(GLfloat x, GLfloat y) {
	
	list<Inimigo*>::iterator itr;
	Circulo* circulo = jogador->getCirculo();
	GLfloat raio = circulo->getRaio();
		
	if(arena->ExisteConflito(raio, x, y) == true) {
		return true;
	} else {
		return false;
	}
}

void TC3:: Atualizar(GLint frametime) {
	
	// GLint frametimeCorrigido = frametime * sqrt(2) / 2.0f;
	
	cout << jogador->getAnguloAviaoGraus() << endl;
	
	if(jogador->getDecolou() == true) {
		
		if(keyStatus[keyEsquerda] == 1 && keyStatus[keyDireita] == 0) {
			
			jogador->AjustarAnguloAviao( +frametime);
			
		} else if(keyStatus[keyEsquerda] == 0 && keyStatus[keyDireita] == 1){
			
			jogador->AjustarAnguloAviao( -frametime);
		}
		
		jogador->Mover(frametime);
				
	} else {
		
		if(keyStatus[keyDecolar] == 1) {
			jogador->Decolar(frametime, pista->getX2(), pista->getY2());
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
	LiberarListaInimigos(inimigosVoadores);
	LiberarListaInimigos(inimigosTerrestres);
}
