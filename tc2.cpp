/*
 * Arquivo: tc2.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
 */

#include <GL/glut.h>
#include <iostream>
#include <string>
#include "Arena.h"
#include "Circulo.h"
#include "Inimigos.h"
#include "Janela.h"
#include "Jogador.h"
#include "Pista.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

// Enumeracao dos tipos de erros verificados que o programa pode encontrar em execucao.
enum Erros {
	SUCESSO = 0,
	ERRO_ABERTURA_CONFIG_XML = 1,
	ERRO_LEITURA_CONFIG_XML = 2,
	ERRO_ABERTURA_ARENA_SVG = 3,
	ERRO_LEITURA_ARENA_SVG = 4
};

/*
 * Definicoes de variaveis globais:
 */

Arena* arena = new Arena();
Jogador* jogador = new Jogador();
Janela* janela = new Janela();
Pista* pista = new Pista(0.0f, 0.0f, 0.0f);
Inimigos* inimigosVoadores = new Inimigos();
Inimigos* inimigosTerrestres = new Inimigos();

/*
 * Definicoes de funcoes:
 */

bool LeituraConfig(XMLDocument& xmlConfig) {

	XMLNode* raiz = xmlConfig.FirstChild();

	/*
	 * Lendo a configuracao do arquivo a ser lido:
	 */

	XMLElement* elemento1 = raiz->FirstChildElement("arquivoDaArena");
	if(elemento1 == 0) return false;

	XMLElement* elemento2 = elemento1->FirstChildElement("nome");
	if(elemento2 == 0) return false;
	const char* nome = elemento2->GetText();
	if(nome[0] == '\0') return false;

	elemento2 = elemento1->FirstChildElement("tipo");
	if(elemento2 == 0) return false;
	const char* tipo = elemento2->GetText();
	if(tipo[0] == '\0') return false;

	 elemento2 = elemento1->FirstChildElement("caminho");
	if(elemento2 == 0) return false;
	const char* caminho = elemento2->GetText();
	if(caminho[0] == '\0') return false;

	string strNome(nome);
	string strTipo(tipo);
	string strCaminho(caminho);
	string arquivo = strCaminho + strNome + "." + strTipo;
	janela->setTitulo(strNome);

	arena->setNomeArquivo(arquivo);

	/*
	 * Lendo o multiplicador da velocidade do jogador:
	 */

	elemento1 = raiz->FirstChildElement("jogador");
	if(elemento1 == 0) return false;

	GLfloat multiplicador;
	if(elemento1->QueryFloatAttribute("vel", &multiplicador)) return false;

	jogador->setMultiplicador(multiplicador);

	return true;
}

bool LeituraArena(XMLDocument& xmlArena) {

	XMLNode* raiz = xmlArena.FirstChild();
	XMLNode* svg = raiz->NextSibling();

	GLint cX;
	GLint cY;
	GLint r;
	const char* fill;
	XMLElement* elemento;

	elemento = svg->FirstChildElement("circle");
	if(elemento == 0) return false;

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
				return false;
		}

		Circulo* circulo = new Circulo(rgb[0], rgb[1], rgb[2]);
		circulo->setRaio(r);
		circulo->setCX(cX);
		circulo->setCY(cY);

		switch(cor) {

			case RED:
				inimigosVoadores->Adicionar(circulo);
				break;

			case GREEN:
				jogador->setCirculo(circulo);
				break;

			case BLUE:
				arena->setCirculo(circulo);
				janela->setXI(circulo->getCX() - circulo->getRaio());
				janela->setXF(circulo->getCX() + circulo->getRaio());
				janela->setYI(circulo->getCY() + circulo->getRaio());
				janela->setYF(circulo->getCY() - circulo->getRaio());
				break;

			case ORANGE:
				inimigosTerrestres->Adicionar(circulo);
				break;

			default:
				delete circulo;
				return false;
		}

		elemento = elemento->NextSiblingElement("circle");

	} while(elemento != 0);

	elemento = svg->FirstChildElement("line");
	if(elemento == 0) return false;

	GLint x1, y1;
	GLint x2, y2;

	elemento->QueryIntAttribute("x1", &x1);
	elemento->QueryIntAttribute("y1", &y1);
	elemento->QueryIntAttribute("x2", &x2);
	elemento->QueryIntAttribute("y2", &y2);
	
	pista->setX1(x1);
	pista->setY1(y1);
	pista->setX2(x2);
	pista->setY2(y2);
	
	return true;
}

void init(void) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(janela->getXI(), janela->getXF(), janela->getYI(), janela->getYF(), 0.0f, 1.0f);
}

void display(void) {
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	arena->Desenha();
	pista->Desenha();
	jogador->Desenha();
	inimigosVoadores->Desenha();
	inimigosTerrestres->Desenha();
	
	glutSwapBuffers();
}

void idle(void) {
	glutPostRedisplay();
}

void LiberarMemoria(void) {
	delete janela;
	delete jogador;
	delete arena;
	delete pista;
	delete inimigosVoadores;
	delete inimigosTerrestres;
}

int RetornaErro(Erros erro) {
	
	switch(erro) {
		
		case ERRO_ABERTURA_CONFIG_XML:
			cout << "Erro: Falha ao abrir config.xml" << endl;
			break;
			
		case ERRO_LEITURA_CONFIG_XML:
			cout << "Erro: Falha ao ler config.xml apos aberto" << endl;
			break;
			
		case ERRO_ABERTURA_ARENA_SVG:
			cout << "Erro: Falha ao abrir arena.svg" << endl;
			break;
			
		case ERRO_LEITURA_ARENA_SVG:
			cout << "Erro: Falha ao ler arena.svg apos aberto" << endl;
			break;
			
		default:
			break;
	}
	
	LiberarMemoria();
	return erro;
}

int main(int argc, char** argv) {
	
	/*
	 * Abertura e leitura do arquivo config.xml:
	 */
	
	string strArqConfig;

	// Se houve passagem de argumento, considera o caminho passado.
	if(argc > 1) {

		string subdir(argv[1]);
    	strArqConfig = subdir + "config.xml";

  		if(strArqConfig.at(0) != '.') {
  			strArqConfig = "." + strArqConfig;
  		}

    // Se nao houve passagem de argumento, considera a pasta de execucao.
    } else {
    	strArqConfig = "./config.xml";
	}

	char chArqConfig[strArqConfig.length() + 1];
	strcpy(chArqConfig, strArqConfig.c_str());

	XMLDocument xmlConfig;
	XMLError erroLoad = xmlConfig.LoadFile(chArqConfig);

	// "erroLoad" recebe zero se "LoadFile" for bem sucedida.
	if( erroLoad != 0 ) {
		return RetornaErro(ERRO_ABERTURA_CONFIG_XML);
	}

	bool leituraConfigSucesso = LeituraConfig(xmlConfig);

	if(leituraConfigSucesso == false) {
		return RetornaErro(ERRO_LEITURA_CONFIG_XML);
	}

	/*
	 * Abertura e leitura do arquivo arena.svg:
	 */

	XMLDocument xmlArena;
	string strArqArena = arena->getNomeArquivo();
	const char* chArqArena = strArqArena.c_str();
	erroLoad = xmlArena.LoadFile(chArqArena);

	// "erroLoad" recebe zero se "LoadFile" for bem sucedida.
	if( erroLoad != 0 ) {
		return RetornaErro(ERRO_ABERTURA_ARENA_SVG);
	}

	bool leituraArenaSucesso = LeituraArena(xmlArena);

	if(leituraArenaSucesso == false) {
		return RetornaErro(ERRO_LEITURA_ARENA_SVG);
	}
	
	/*
	 * Iniciando GLUT:
	 */

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);	
	glutInitWindowSize(janela->Largura(), janela->Altura());
	glutInitWindowPosition(100, 100);
	glutCreateWindow(janela->getTitulo().c_str());
		
	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();
	
	LiberarMemoria();
	return SUCESSO;
}
