/*
 * Arquivo: tc1.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC1
*/

#include <iostream>
#include <math.h>
#include <list>
#include <GL/glut.h>
#include "tinyxml2.h"
#include "Circulo.h"
#include "CirculoModelo.h"
#include "CirculoImpresso.h"
#include "Janela.h"

using namespace std;
using namespace tinyxml2;

/* Enumeracao dos tipos de erros verificados que o programa pode encontrar em execucao */

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
list<CirculoImpresso*> circulos;
list<CirculoImpresso*>::iterator itr;
CirculoImpresso* circuloArrastado;

// Coordenadas do cursor em tempo real.
int mX = 0;
int mY = 0;

// Coordenadas do cursor no momento de clique do mouse1.
int printX = 0;
int printY = 0;

// Diferenca entre as coordenadas do clique mouse2 e o centro do circulo.
int dragX = 0;
int dragY = 0;

// Verificacoes de acoes do mouse
bool mousePertenceJanela = false;
bool mouse1Press = false;
bool conflitoModelo = false;
bool arrastarCirculo = false;

// Quantidade de linhas definindo circunferencia do circulo.
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

float distPontos(const int& x1, const int& y1, const int& x2, const int& y2) {
	return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
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

void display(void) {
		
	int i;
	int centroX, centroY;
	int raio = circuloGenerico.getRaio();
	float corR, corG, corB;

	glClear(GL_COLOR_BUFFER_BIT);
	glutEntryFunc(mouseEntryState);
	
	corR = circuloGenerico.getCorR();
	corG = circuloGenerico.getCorG();
	corB = circuloGenerico.getCorB();
	
	if(arrastarCirculo == true) {
		
		centroX = mX - dragX;
		centroY = mY - dragY;
		
		glColor3f(corR, corG, corB);
		glBegin(GL_POLYGON);
		
			for(i = 0; i < qtdeLinhas; i++) {
				
				float angulo = 2.0f * 3.141593f * ((float) i / qtdeLinhas);
				float x = raio * cosf(angulo);
				float y = raio * sinf(angulo);
				
				glVertex2i((int) x + centroX, (int) y + centroY);
			}
			
		glEnd();
	}

	for(itr = circulos.begin(); itr != circulos.end(); itr++) {
		
		centroX = (*itr)->getX();
		centroY = (*itr)->getY();
		
		glColor3f(corR, corG, corB);
		glBegin(GL_POLYGON);
		
			for(i = 0; i < qtdeLinhas; i++) {
				
				float angulo = 2.0f * 3.141593f * ((float) i / qtdeLinhas);
				float x = raio * cosf(angulo);
				float y = raio * sinf(angulo);
				
				glVertex2i((int) x + centroX, (int) y + centroY);
			}
			
		glEnd();
	}
	
	if(mousePertenceJanela == true && arrastarCirculo == false) {
				
		if(conflitoModelo == true) {
			corR = circuloModelo.getCorSobreposicaoR();
			corG = circuloModelo.getCorSobreposicaoG();
			corB = circuloModelo.getCorSobreposicaoB();
		} else {
			corR = circuloModelo.getCorR();
			corG = circuloModelo.getCorG();
			corB = circuloModelo.getCorB();
		}
		
		centroX = mX;
		centroY = mY;
		
		glColor3f(corR, corG, corB);
		glBegin(GL_LINE_LOOP);
			
			for(i = 0; i < qtdeLinhas; i++) {
				
				float angulo = 2.0f * 3.141593f * ((float) i / qtdeLinhas);
				float x = raio * cosf(angulo);
				float y = raio * sinf(angulo);
				
				glVertex2i((int) x + centroX, (int) y + centroY);
			}
		
		glEnd();
	}

	glFlush();
}

void mouseMotion(int x, int y) {
	mX = x;
	mY = y;
	glutPostRedisplay();
}

/* Funcao que verifica se existe algum tipo de conflito baseando-se na posicao fornecida.
*/
bool verificarConflito(int x, int y) {
	
	for(itr = circulos.begin(); itr != circulos.end(); itr++) {
		
		float dist = distPontos(x, y, (*itr)->getX(), (*itr)->getY());
		int raio = circuloGenerico.getRaio();
		
		if(dist <= 2 * raio) {
			return true;
		}
	}
	
	return false;
}

void mousePassiveMotion(int x, int y) {
	
	mX = x;
	mY = y;
	
	if(verificarConflito(x, y) == true) {
		conflitoModelo = true;
	} else {
		conflitoModelo = false;
	}
		
	mousePertenceJanela = true;
	glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y) {
		
	if(state == GLUT_DOWN) {
	
		if(button == GLUT_LEFT_BUTTON) {
					
			if(mousePertenceJanela == true && conflitoModelo == false) {
				
				CirculoImpresso* circulo = new CirculoImpresso();
				
				circulo->setX(x);
				circulo->setY(y);
				circulo->setRaio(circuloGenerico.getRaio());
				circulo->setCorR(circuloGenerico.getCorR());
				circulo->setCorG(circuloGenerico.getCorG());
				circulo->setCorB(circuloGenerico.getCorB());
				
				circulos.push_back(circulo);
			}
		
		} else if(button == GLUT_RIGHT_BUTTON) {
			
			for(itr = circulos.begin(); itr != circulos.end(); itr++) {
		
				float dist = distPontos(x, y, (*itr)->getX(), (*itr)->getY());
				int raio = circuloGenerico.getRaio();
				
				if(dist <= raio) {
										
					arrastarCirculo = true;
					circuloArrastado = new CirculoImpresso(*itr);
					
					int centroX = circuloArrastado->getX();
					int centroY = circuloArrastado->getY();
					
					dragX = x - centroX;
					dragY = y - centroY;
					
					CirculoImpresso* circuloDesaloc = *itr;
					circulos.erase(itr);
					delete(circuloDesaloc);
					break;
				}
			}
		}
		
	} else if(state == GLUT_UP) {
		
		if(button == GLUT_RIGHT_BUTTON) {
		
			if(arrastarCirculo == true) {
				
				int centroX = x - dragX;
				int centroY = y - dragY;
				
				if(verificarConflito(centroX, centroY) == false) {
					circuloArrastado->setX(x - dragX);
					circuloArrastado->setY(y - dragY);
				}
				
				circulos.push_back(circuloArrastado);
				arrastarCirculo = false;
			}
		}
	}
	
	glutPostRedisplay();
}

void idle(void) {
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	
	string strArquivo;
	
	if(argc > 1) {
    	
		string subdir(argv[1]);
    	strArquivo = subdir + "config.xml";
  		
  		if(strArquivo.at(0) != '.') {
  			strArquivo = "." + strArquivo;
  		}
    	
    } else {
    	
    	strArquivo = "./config.xml";
	}
	
	char chArquivo[strArquivo.length() + 1];
	strcpy(chArquivo, strArquivo.c_str());
    
	cout << chArquivo << endl;
		
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

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(janela.getLargura(), janela.getAltura());
	glutInitWindowPosition(100, 100);
	glutCreateWindow(janela.getTitulo());
	init();
	glutPassiveMotionFunc(mousePassiveMotion);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMotion);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();

	for(itr = circulos.begin(); itr != circulos.end(); itr++)
		delete(*itr);
	delete(circuloArrastado);

	return SUCESSO;
}
