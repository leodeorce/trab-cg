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

vector<Circulo> circuloImpressao;
CirculoModelo circuloModelo;
Janela janela;

// Coordenadas do cursor em tempo real
int mX = 0;
int mY = 0;

// Coordenadas do cursor no momento de clique do mouse1
int printX = 0;
int printY = 0;

// Verificacoes de acoes do mouse
bool mousePertenceJanela = false;
bool mouse1PressJanela = false;

// Quantidade de linhas definindo circunferencia do circulo
int qtdeLinhas = 50;

/* Definicoes de funcoes */

bool LeituraXML(XMLDocument& xmlConfig) {
	
	XMLNode* raiz = xmlConfig.FirstChild();
	if(raiz == nullptr) return false;
	
	/* Lendo a configuracao do circulo a ser impresso */
	
	XMLElement* elemento = raiz->FirstChildElement("circulo");
	if(elemento == nullptr) return false;
	
	int raio;
	if( elemento->QueryIntAttribute("raio", &raio) ) return false;
	
	float corR, corG, corB;
	if( elemento->QueryFloatAttribute("corR", &corR) ) return false;
	if( elemento->QueryFloatAttribute("corG", &corG) ) return false;
	if( elemento->QueryFloatAttribute("corB", &corB) ) return false;
	
	circuloImpressao.setRaio(raio);
	circuloImpressao.setCorR(corR);
	circuloImpressao.setCorG(corG);
	circuloImpressao.setCorB(corB);
	
	/* Lendo a configuracao do circulo modelo */
	
	elemento = raiz->FirstChildElement("circuloModelo");
	if(elemento == nullptr) return false;
	
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
	if(elemento == nullptr) return false;
	
	XMLElement* elementoJanela = elemento->FirstChildElement("dimensao");
	if(elementoJanela == nullptr) return false;
	
	int largura, altura;
	if( elementoJanela->QueryIntAttribute("largura", &largura) ) return false;
	if( elementoJanela->QueryIntAttribute("altura", &altura) ) return false;
	
	janela.setLargura(largura);
	janela.setAltura(altura);
		
	elementoJanela = elemento->FirstChildElement("fundo");
	if(elementoJanela == nullptr) return false;
	
	if( elementoJanela->QueryFloatAttribute("corR", &corR) ) return false;
	if( elementoJanela->QueryFloatAttribute("corG", &corG) ) return false;
	if( elementoJanela->QueryFloatAttribute("corB", &corB) ) return false;
	
	janela.setCorR(corR);
	janela.setCorG(corG);
	janela.setCorB(corB);
		
	elementoJanela = elemento->FirstChildElement("titulo");
	if(elementoJanela == nullptr) return false;
	
	const char* titulo = elementoJanela->GetText();
	if(titulo == nullptr) return false;
	
	janela.setTitulo(titulo);
	
	return true;
	
}

void init(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, janela.getLargura(), 0.0f, janela.getAltura(), 0.0f, 1.0f);
	// glOrtho(0.0f, janela.getLargura(), janela.getAltura(), 0.0f, 0.0f, 1.0f);
}

void mouseEntryState(int state) {
	mousePertenceJanela = (state == GLUT_ENTERED) ? true : false;
	glutPostRedisplay();
}

void drawCircle(float raio, float cX, float cY, float corR, float corG, float corB) {
	glBegin(GL_LINE_LOOP);
		glColor3f(corR, corG, corB);
		int i;
		for(i = 0; i < qtdeLinhas; i++) {
			float angulo = 2.0f * 3.1416f * ((float) i / qtdeLinhas);
			float x = raio * cosf(angulo);
			float y = raio * sinf(angulo);
			glVertex2f(x + cX, y + cY);
		}
	glEnd();
}

void display(void) {
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	glutEntryFunc(mouseEntryState);
	
	if(mousePertenceJanela) {		
		drawCircle(
			circuloModelo.getRaio(),
			mX, mY,
			circuloModelo.getCorR(),
			circuloModelo.getCorG(),
			circuloModelo.getCorB()
			);
	}
	
	// for()
		if(mouse1PressJanela) {
			drawCircle(
				circuloImpressao.getRaio(),
				printX, printY,
				circuloImpressao.getCorR(),
				circuloImpressao.getCorG(),
				circuloImpressao.getCorB()
				);
		}
	
	// static int j = 0;
	// cout << "teste" << j++ << endl;
	
	glFlush();
}

// void mousePositionUpdate(int& x, int& y) {
// 	mX = x;
// 	mY = glutGet(GLUT_WINDOW_HEIGHT) - y;
// }

void mouseMotion(int x, int y) {
	// mousePositionUpdate(x, y);
	mX = x;
	mY = glutGet(GLUT_WINDOW_HEIGHT) - y;
	mousePertenceJanela = true;
	glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y) {
	if(button == GLUT_LEFT_BUTTON)
		if(state == GLUT_DOWN)
			mouse1PressJanela = (mousePertenceJanela) ? true : false;
		else
			if(mousePertenceJanela && mouse1PressJanela && x == mx && y == mY) {
				Circulo circulo;
				circulo.setRaio(circuloModelo.getRaio());
				circulo.setCorR(circuloModelo.getCorR());
				circulo.setCorG(circuloModelo.getCorG());
				circulo.setCorB(circuloModelo.getCorB());
			}
				
	// mousePositionUpdate(x, y);
	printX = x;
	printY = glutGet(GLUT_WINDOW_HEIGHT) - y;
	glutPostRedisplay();
}

// void idle(void) {
// 	glutPostRedisplay();
// }

int main(int argc, char** argv) {

	if(argc > 1) {
		
		/* Construindo caminho para arquivo de configuracoes "config.xml" a partir de argv */
		
		// Unindo o caminho usado para executar o programa (argv[0]) com o caminho passado como
		// parametro (argv[1]) temos o caminho para config.xml a partir do diretorio de execucao
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
		
		// erroLoad recebe zero se "LoadFile" for bem sucedida
		if( !erroLoad ) {
			
			bool erroRead = LeituraXML(xmlConfig);
			if(!erroRead) {
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
	// glutIdleFunc(idle);
	glutMainLoop();
		
	return SUCESSO;

}
