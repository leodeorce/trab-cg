/*
 * Arquivo: tc1.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC1
*/

#include <iostream>
#include <math.h>
#include <vector>
#include <GL/glut.h>
#include "tinyxml2.h"
#include "Circulo.h"
#include "CirculoModelo.h"
#include "CirculoImpresso.h"
#include "Janela.h"

using namespace std;
using namespace tinyxml2;

/* Enumeracao dos tipos de erros possiveis que o programa pode encontrar em execucao */

enum Erros {
	SUCESSO = 0,
	ERRO_NENHUM_PARAMETRO = 1,
	ERRO_ABERTURA_CONFIG = 2,
	ERRO_LEITURA_CONFIG = 3
};

/* Declaracoes de variaveis globais */

Circulo circuloGenerico;
CirculoModelo circuloModelo;
Janela janela;
vector<CirculoImpresso*> circulos;

// Coordenadas do cursor em tempo real
int mX = 0;
int mY = 0;

// Coordenadas do cursor no momento de clique do mouse1
int printX = 0;
int printY = 0;

// Verificacoes de acoes do mouse
bool mousePertenceJanela = false;
bool mouse1Press = false;

// Quantidade de linhas definindo circunferencia do circulo
int qtdeLinhas = 50;

/* Definicoes de funcoes */

bool LeituraXML(XMLDocument& xmlConfig) {

	XMLNode* raiz = xmlConfig.FirstChild();

	/* Lendo a configuracao do circulo a ser impresso */

	XMLElement* elemento = raiz->FirstChildElement("circulo");
	if(!elemento) return false;

	int raio;
	if( elemento->QueryIntAttribute("raio", &raio) ) return false;

	float corR, corG, corB;
	if( elemento->QueryFloatAttribute("corR", &corR) ) return false;
	if( elemento->QueryFloatAttribute("corG", &corG) ) return false;
	if( elemento->QueryFloatAttribute("corB", &corB) ) return false;

	circuloGenerico.setRaio(raio);
	circuloGenerico.setCorR(corR);
	circuloGenerico.setCorG(corG);
	circuloGenerico.setCorB(corB);

	/* Lendo a configuracao do circulo modelo */

	elemento = raiz->FirstChildElement("circuloModelo");
	if(!elemento) return false;

	if( elemento->QueryFloatAttribute("corR", &corR) ) return false;
	if( elemento->QueryFloatAttribute("corG", &corG) ) return false;
	if( elemento->QueryFloatAttribute("corB", &corB) ) return false;

	circuloModelo.setRaio(raio);
	circuloModelo.setCorR(corR);
	circuloModelo.setCorG(corG);
	circuloModelo.setCorB(corB);

	float corSobreposicaoR, corSobreposicaoG, corSobreposicaoB;
	if( elemento->QueryFloatAttribute("corSobreposicaoR", &corSobreposicaoR) ) return false;
	if( elemento->QueryFloatAttribute("corSobreposicaoG", &corSobreposicaoG) ) return false;
	if( elemento->QueryFloatAttribute("corSobreposicaoB", &corSobreposicaoB) ) return false;

	circuloModelo.setCorSobreposicaoR(corSobreposicaoR);
	circuloModelo.setCorSobreposicaoG(corSobreposicaoG);
	circuloModelo.setCorSobreposicaoB(corSobreposicaoB);

	/* Lendo a configuracao da janela */

	elemento = raiz->FirstChildElement("janela");
	if(!elemento) return false;

	XMLElement* elementoJanela = elemento->FirstChildElement("dimensao");
	if(!elementoJanela) return false;

	int largura, altura;
	if( elementoJanela->QueryIntAttribute("largura", &largura) ) return false;
	if( elementoJanela->QueryIntAttribute("altura", &altura) ) return false;

	janela.setLargura(largura);
	janela.setAltura(altura);

	elementoJanela = elemento->FirstChildElement("fundo");
	if(!elementoJanela) return false;

	if( elementoJanela->QueryFloatAttribute("corR", &corR) ) return false;
	if( elementoJanela->QueryFloatAttribute("corG", &corG) ) return false;
	if( elementoJanela->QueryFloatAttribute("corB", &corB) ) return false;

	janela.setCorR(corR);
	janela.setCorG(corG);
	janela.setCorB(corB);

	elementoJanela = elemento->FirstChildElement("titulo");
	if(!elementoJanela) return false;

	const char* titulo = elementoJanela->GetText();

	janela.setTitulo(titulo);

	return true;

}

void init(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, janela.getLargura(), janela.getAltura(), 0.0f, 0.0f, 1.0f);
}

void mouseEntryState(int state) {
	mousePertenceJanela = (state == GLUT_ENTERED) ? true : false;
	glutPostRedisplay();
}

void drawCircle(float raio, int cX, int cY, float corR, float corG, float corB) {
	glBegin(GL_LINE_LOOP);
		glColor3f(corR, corG, corB);
		int i;
		for(i = 0; i < qtdeLinhas; i++) {
			float angulo = 2.0f * 3.141593f * ((float) i / qtdeLinhas);
			float x = raio * cosf(angulo);
			float y = raio * sinf(angulo);
			glVertex2i((int) x + cX, (int) y + cY);
		}
	glEnd();
}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	glutEntryFunc(mouseEntryState);

	if(mousePertenceJanela) {
		drawCircle(
			circuloModelo.getRaio(),
			mX,
			mY,
			circuloModelo.getCorR(),
			circuloModelo.getCorG(),
			circuloModelo.getCorB()
			);
	}

	vector<CirculoImpresso*>::iterator itr;
	for(itr = circulos.begin(); itr != circulos.end(); itr++) {
		drawCircle(
			(*itr)->getRaio(),
			(*itr)->getX(),
			(*itr)->getY(),
			(*itr)->getCorR(),
			(*itr)->getCorG(),
			(*itr)->getCorB()
			);
	}

	glFlush();
}

void mouseMotion(int x, int y) {
	mX = x;
	mY = y;
	mousePertenceJanela = true;
	glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y) {
	if(button == GLUT_LEFT_BUTTON) {
		if(state == GLUT_DOWN) {
			if(mousePertenceJanela == true) {
				CirculoImpresso* circulo = new CirculoImpresso(x, y);
				circulo->setRaio(circuloGenerico.getRaio());
				circulo->setCorR(circuloGenerico.getCorR());
				circulo->setCorG(circuloGenerico.getCorG());
				circulo->setCorB(circuloGenerico.getCorB());
				circulos.push_back(circulo);
			}
		}
	}
}

void idle(void) {
	glutPostRedisplay();
}

int main(int argc, char** argv) {

	if(argc > 1) {

		/* Construindo caminho para arquivo de configuracoes "config.xml" a partir de argv */

		// Unindo o caminho usado para executar o programa (argv[0]) com o caminho passado como
		// parametro (argv[1]) temos o caminho para config.xml a partir do diretorio de execucao.
		string prog(argv[0]);
		string subdir(argv[1]);
    	string dir = prog.substr(0, prog.find_last_of("/"));
    	string strArquivo = dir + subdir + "config.xml";

    	int n = strArquivo.length();
    	char chArquivo[n + 1];
    	strcpy(chArquivo, strArquivo.c_str());

		/* Iniciando abertura e leitura do arquivo config.xml */

		XMLDocument xmlConfig;
		XMLError erroLoad = xmlConfig.LoadFile(chArquivo);

		// erroLoad recebe zero se "LoadFile" for bem sucedida.
		if( erroLoad == 0 ) {

			bool leituraSucesso = LeituraXML(xmlConfig);
			if(leituraSucesso == false) {
				cout << "Erro: Falha ao ler config.xml apos aberto" << endl;
				return ERRO_LEITURA_CONFIG;
			}

		} else {
			cout << "Erro: Falha ao abrir config.xml" << endl;
			return ERRO_ABERTURA_CONFIG;
		}

	} else {
		cout << "Erro: Nao houve caminho passado" << endl;
		return ERRO_NENHUM_PARAMETRO;
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(janela.getLargura(), janela.getAltura());
	glutInitWindowPosition(100, 100);
	glutCreateWindow(janela.getTitulo());
	init();
	glutPassiveMotionFunc(mouseMotion);
	glutMouseFunc(mouseClick);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();

	vector<CirculoImpresso*>::iterator itr;
	for(itr = circulos.begin(); itr != circulos.end(); itr++)
		delete(*itr);

	return SUCESSO;

}
