/*
 * Arquivo: TC2.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
*/

#include <iostream>
#include <string>
#include "TC2.h"


Erros TC2:: LeituraArquivos(const char* chArqConfig) {
	
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

Erros TC2:: LeituraConfig(XMLDocument& xmlConfig) {

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

	GLfloat multiplicador;
	if(elemento1->QueryFloatAttribute("vel", &multiplicador)) return ERRO_LEITURA_CONFIG_XML;
	
	jogador = new Jogador();
	jogador->setMultiplicador(multiplicador);

	return SUCESSO;
}

Erros TC2:: LeituraArena(XMLDocument& xmlArena) {

	XMLNode* raiz = xmlArena.FirstChild();
	XMLNode* svg = raiz->NextSibling();

	GLint cX;
	GLint cY;
	GLint r;
	const char* fill;
	XMLElement* elemento;

	elemento = svg->FirstChildElement("circle");
	if(elemento == 0) return ERRO_LEITURA_ARENA_SVG;

	do {

		elemento->QueryIntAttribute("cx", &cX);
		elemento->QueryIntAttribute("cy", &cY);
		elemento->QueryIntAttribute("r", &r);
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

	GLint x1, y1;
	GLint x2, y2;

	elemento->QueryIntAttribute("x1", &x1);
	elemento->QueryIntAttribute("y1", &y1);
	elemento->QueryIntAttribute("x2", &x2);
	elemento->QueryIntAttribute("y2", &y2);
	
	pista = new Pista(0.0f, 0.0f, 0.0f);
	pista->setX1(x1);
	pista->setY1(y1);
	pista->setX2(x2);
	pista->setY2(y2);

	return SUCESSO;
}

void TC2:: AdicionarInimigoVoador(Inimigo* inimigo) {
	inimigosVoadores.push_back(inimigo);
}

void TC2:: AdicionarInimigoTerrestre(Inimigo* inimigo) {
	inimigosTerrestres.push_back(inimigo);
}

void TC2:: DesenharArena(void) {
	arena->Desenhar();
}

void TC2:: DesenharJogador(void) {
	jogador->Desenhar();
}

void TC2:: DesenharPista(void) {
	pista->Desenhar();
}

void TC2:: DesenharInimigosVoadores(void) {
	DesenharInimigos(inimigosVoadores);
}

void TC2:: DesenharInimigosTerrestres(void) {
	DesenharInimigos(inimigosTerrestres);
}

void TC2:: DesenharInimigos(list<Inimigo*>& listaInimigos) {
	list<Inimigo*>::iterator itr;
	for(itr = listaInimigos.begin(); itr != listaInimigos.end(); ++itr) {
		(*itr)->Desenhar();
	}
}

void TC2:: KeyDown(unsigned char key) {
	keyStatus[key] = 1;
}

void TC2:: KeyUp(unsigned char key) {
	keyStatus[key] = 0;
}

void TC2:: Atualizar(void) {
	
	GLfloat delta = 1.0f;
	
	if(keyStatus[keyDecolar] == 1) {
		jogador->Decolar();
	}
	if(keyStatus[keyCima] == 1) {
		jogador->MoverY(+ delta);
	}
	if(keyStatus[keyEsquerda] == 1) {
		jogador->MoverX(- delta);
	}
	if(keyStatus[keyBaixo] == 1) {
		jogador->MoverY(- delta);
	}
	if(keyStatus[keyDireita] == 1) {
		jogador->MoverX(+ delta);
	}
}

void TC2:: LiberarListaInimigos(list<Inimigo*>& listaInimigos) {
	
	if(listaInimigos.size() > 0) {
		
		list<Inimigo*>::iterator itr = listaInimigos.begin();
		
		while(itr != listaInimigos.end()) {
			delete *itr;
			itr = listaInimigos.erase(itr);
		}
	}
}

TC2:: ~TC2() {
	delete janela;
	delete jogador;
	delete arena;
	delete pista;
	LiberarListaInimigos(inimigosVoadores);
	LiberarListaInimigos(inimigosTerrestres);
}