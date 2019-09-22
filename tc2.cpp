/*
 * Arquivo: tc2.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
 */

#include <GL/glut.h>
#include <iostream>
#include <list>
#include <locale>
#include <math.h>
#include <string>
#include "Arena.h"
#include "Circulo.h"
#include "Janela.h"
#include "Jogador.h"
#include "tinyxml2.h"
#include "NumberUtils.h"

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
 * Declaracoes de variaveis globais:
 */

Arena* arena = new Arena();
Jogador* jogador = new Jogador();
Janela* janela = new Janela();
list<Circulo*> inimigosVoadores;
list<Circulo*> inimigosTerrestres;


// Coordenadas do cursor em tempo real.
int mX = 0;
int mY = 0;

// Diferenca entre as coordenadas do clique botao direito e o centro do circulo.
int dragX = 0;
int dragY = 0;

// Verificacoes de acoes do mouse.
bool mousePertenceJanela = false;
bool conflitoModelo = false;
bool arrastarCirculo = false;

// Quantidade de linhas definindo circunferencia.
int qtdeLinhas = 50;

/* 
 * Declaracoes de funcoes:
 */

/* Descricao: Funcao de leitura do arquivo config.xml.
 * Entrada: Objeto do tipo XMLDocument representando o arquivo ja' aberto.
 * Saida: Boolean indicando sucesso ou fracasso na leitura do arquivo.
 */
bool LeituraConfig(XMLDocument& xmlConfig);

/* Descricao: Calcula a distancia entre dois pontos.
 * Entrada: Coordenadas X e Y de dois pontos.
 * Saida: Distancia entre os pontos passados.
 */
float distPontos(int x1, int y1, int x2, int y2);

/* Descricao: Define configuracoes da janela.
 * Entrada: Nenhuma.
 * Saida: Nenhuma.
 */
void init(void);

/* Descricao: Descreve um circulo ou circunferencia em pontos usando as coordenadas de centro especificadas.
 * Entrada: Coordenadas X e Y do centro do circulo/circunferencia.
 * Saida: Nenhuma.
 */
void drawCircle(int centroX, int centroY);

/* Descricao: (callback) Atualiza a tela com as informacoes do mundo virtual.
 * Entrada: Nenhuma.
 * Saida: Nenhuma.
 */
void display(void);

/* Descricao: (callback) Verifica se o cursor entrou ou saiu da janela e atualiza variavel global.
 * Entrada: Estado do cursor (entrou / saiu).
 * Saida: Nenhuma.
 */
void mouseEntryState(int state);

/* Descricao: Atualiza posicao do cursor quando este se move pela janela com um botao sendo clicado.
 * Entrada: Coordenadas X e Y do cursor.
 * Saida: Nenhuma.
 */
void mouseMotion(int x, int y);

/* Descricao: (callback) Atualiza posicao do cursor quando este se move pela janela sem nenhum botao clicado.
 * Entrada: Coordenadas X e Y do cursor.
 * Saida: Nenhuma.
 */
void mousePassiveMotion(int x, int y);

/* Descricao: (callback) Resgata cliques do mouse e atualiza variaveis globais de acordo.
 * Entrada: Botao acionado, tipo de acao (pressionado ou solto) e coordenadas do clique.
 * Saida: Nenhuma.
 */
void mouseClick(int button, int state, int x, int y);

/* Descricao: Funcao que verifica se existe algum tipo de conflito baseando-se na posicao fornecida.
 * Entrada: Coordenadas X e Y a serem consideradas para conflito com circulos impressos.
 * Saida: Boolean indicando se existe ou nao conflito.
 */
bool verificarConflito(int x, int y);

/* Descricao: (callback) Chama atualizacao da tela.
 * Entrada: Nenhuma.
 * Saida: Nenhuma.
 */
void idle(void);

/* 
 * Definicoes de funcoes:
 */

bool LeituraConfig(XMLDocument& xmlConfig) {

	XMLNode* raiz = xmlConfig.FirstChild();

	/* 
	 * Lendo a configuracao do arquivo a ser lido:
	 */
	
	XMLElement* elemento1 = raiz->FirstChildElement("arquivoDaArena");
	if(!elemento1) return false;
	
	XMLElement* elemento2 = elemento1->FirstChildElement("nome");
	if(!elemento2) return false;
	const char* nome = elemento2->GetText();
	if( nome[0] == '\0' ) return false;
		
	elemento2 = elemento1->FirstChildElement("tipo");
	if(!elemento2) return false;	
	const char* tipo = elemento2->GetText();
	if( tipo[0] == '\0' ) return false;
	
	 elemento2 = elemento1->FirstChildElement("caminho");
	if(!elemento2) return false;	
	const char* caminho = elemento2->GetText();
	if( caminho[0] == '\0' ) return false;
	
	string strNome(nome);
	string strTipo(tipo);
	string strCaminho(caminho);
	string arquivo = strCaminho + strNome + "." + strTipo;
	janela->setTitulo(strNome);
		
	arena->setArquivo(arquivo);
		
	/* 
	 * Lendo o multiplicador da velocidade do jogador:
	 */

	elemento1 = raiz->FirstChildElement("jogador");
	if(!elemento1) return false;
	
	float multiplicador;
	if( elemento1->QueryFloatAttribute("vel", &multiplicador) ) return false;

	jogador->setMultiplicador(multiplicador);
	
	return true;
}

bool LeituraArena(XMLDocument& xmlArena) {
	
	XMLNode* raiz = xmlArena.FirstChild();
	XMLNode* svg = raiz->NextSibling();
	
	int cX;
	int cY;
	int r;
	const char* fill;
	XMLElement* elemento;
	
	elemento = svg->FirstChildElement("circle");
	if(!elemento) return false;
		
	do {
		
		elemento->QueryIntAttribute("cx", &cX);
		elemento->QueryIntAttribute("cy", &cY);
		elemento->QueryIntAttribute("r", &r);
		fill = elemento->Attribute("fill");
		
		Cor cor;
		if(!strcmp(fill, "red")) cor = RED;
		if(!strcmp(fill, "green")) cor = GREEN;
		if(!strcmp(fill, "blue")) cor = BLUE;
		if(!strcmp(fill, "orange")) cor = ORANGE;
		
		float rgb[3];
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
		
		Circulo circulo(rgb[0], rgb[1], rgb[2]);
		circulo.setRaio(r);
		circulo.setCX(cX);
		circulo.setCY(cY);
		
		Circulo* ptrCirculo;
		int largura;
		int altura;
		
		switch(cor) {
			
			case RED:
				// ptrCirculo = new Circulo(circulo);
				// inimigosVoadores.push_back(ptrCirculo);
				break;
				
			case GREEN:
				jogador->setCirculo(circulo);
				break;
				
			case BLUE:
				arena->setCirculo(circulo);
				largura = 2 * cX;
				altura = 2 * cY;
				janela->setLargura(largura);
				janela->setAltura(altura);
				break;
				
			case ORANGE:
				// ptrCirculo = new Circulo(circulo);
				// inimigosTerrestres.push_back(ptrCirculo);
				break;
				
			default:
				return false;
		}
		
		elemento = elemento->NextSiblingElement("circle");
		
	} while(elemento != 0);
	
	elemento = svg->FirstChildElement("line");
	if(!elemento) return false;
	
	int x1, y1;
	int x2, y2;
	
	elemento->QueryIntAttribute("x1", &x1);
	elemento->QueryIntAttribute("y1", &y1);
	elemento->QueryIntAttribute("x2", &x2);
	elemento->QueryIntAttribute("y2", &y2);
	
	const char* style = elemento->Attribute("style");
	string strStyle(style);
		
	int idxRGB = strStyle.find("rgb");
	
	string subStrRGB = strStyle.substr(idxRGB + 4, string::npos);
	int idxRed = subStrRGB.find(",");
	string strRed = subStrRGB.substr(0, idxRed);
	
	string subStrGB = subStrRGB.substr(idxRed + 1, string::npos);
	int idxGreen = subStrGB.find(",");
	string strGreen = subStrGB.substr(0, idxGreen);
	
	string subStrB = subStrGB.substr(idxGreen + 1, string::npos);
	int idxBlue = subStrB.find(")");
	string strBlue = subStrB.substr(0, idxBlue);
	
	float red = parseFloat(strRed, locale());
	float green = parseFloat(strGreen, locale());
	float blue = parseFloat(strBlue, locale());
	
	return true;
}

// float distPontos(int x1, int y1, int x2, int y2) {
// 	return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
// }

// void init(void) {
// 	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();
// 	glOrtho(0.0f, janela.getLargura(), janela.getAltura(), 0.0f, 0.0f, 1.0f);
// }

// void drawCircle(int centroX, int centroY) {
	
// 	int i;
// 	int raio = circuloGenerico.getRaio();
			
// 	for(i = 0; i < qtdeLinhas; i++) {
		
// 		// "angulo" recebe o em radianos um angulo auxiliar para encontrar cada
// 		// ponto que constroi o circulo.
// 		float angulo = 2.0f * 3.141593f * ((float) i / qtdeLinhas);
// 		float x = raio * cosf(angulo);
// 		float y = raio * sinf(angulo);
		
// 		glVertex2i((int) x + centroX, (int) y + centroY);
// 	}
// }

// void display(void) {
	
// 	int centroX, centroY;
// 	float corR, corG, corB;

// 	glClear(GL_COLOR_BUFFER_BIT);
	
// 	// Verifica se o cursor esta dentro da janela.
// 	glutEntryFunc(mouseEntryState);
	
// 	corR = circuloGenerico.getCorR();
// 	corG = circuloGenerico.getCorG();
// 	corB = circuloGenerico.getCorB();
	
// 	// Desenha circulo sendo arrastado.
// 	if(arrastarCirculo == true) {
		
// 		// Garante que o centro do circulo sendo arrastado seja relativo a posicao
// 		// atual do mouse com base em onde ele foi inicialmente seleecionado.
// 		centroX = mX - dragX;
// 		centroY = mY - dragY;
		
// 		glColor3f(corR, corG, corB);
// 		glBegin(GL_POLYGON);
		
// 		drawCircle(centroX, centroY);
		
// 		glEnd();
// 	}
	
// 	// Desenha todos os circulos impressos.
// 	for(itr = circulos.begin(); itr != circulos.end(); itr++) {
		
// 		centroX = (*itr)->getX();
// 		centroY = (*itr)->getY();
		
// 		glColor3f(corR, corG, corB);
// 		glBegin(GL_POLYGON);
		
// 		drawCircle(centroX, centroY);
		
// 		glEnd();
// 	}
	
// 	// Desenha circulo modelo.
// 	if(mousePertenceJanela == true && arrastarCirculo == false) {
				
// 		if(conflitoModelo == true) {
// 			corR = circuloModelo.getCorSobreposicaoR();
// 			corG = circuloModelo.getCorSobreposicaoG();
// 			corB = circuloModelo.getCorSobreposicaoB();
// 		} else {
// 			corR = circuloModelo.getCorR();
// 			corG = circuloModelo.getCorG();
// 			corB = circuloModelo.getCorB();
// 		}
		
// 		centroX = mX;
// 		centroY = mY;
		
// 		glColor3f(corR, corG, corB);
// 		glBegin(GL_LINE_LOOP);
		
// 		drawCircle(centroX, centroY);
		
// 		glEnd();
// 	}

// 	glFlush();
// }

// void mouseEntryState(int state) {
// 	mousePertenceJanela = (state == GLUT_ENTERED) ? true : false;
// }

// void mouseMotion(int x, int y) {
// 	mX = x;
// 	mY = y;
// }

// void mousePassiveMotion(int x, int y) {
	
// 	mX = x;
// 	mY = y;
	
// 	// Modifica "conflitoModelo" verificando se existe necessidade de mudar a cor
// 	// do circulo modelo.
// 	if(verificarConflito(x, y) == true) {
// 		conflitoModelo = true;
// 	} else {
// 		conflitoModelo = false;
// 	}
		
// 	mousePertenceJanela = true;
// }

// void mouseClick(int button, int state, int x, int y) {
		
// 	if(state == GLUT_DOWN) {
	
// 		if(button == GLUT_LEFT_BUTTON) {
			
// 			// Cria novo circulo a ser impresso e o adiciona na lista de circulos impressos.
// 			if(mousePertenceJanela == true && conflitoModelo == false) {
				
// 				CirculoImpresso* circulo = new CirculoImpresso();
				
// 				circulo->setX(x);
// 				circulo->setY(y);
// 				circulo->setRaio(circuloGenerico.getRaio());
// 				circulo->setCorR(circuloGenerico.getCorR());
// 				circulo->setCorG(circuloGenerico.getCorG());
// 				circulo->setCorB(circuloGenerico.getCorB());
				
// 				circulos.push_back(circulo);
// 			}
		
// 		} else if(button == GLUT_RIGHT_BUTTON) {
			
// 			// Verifica se o clique com botao direito foi feito dentro da area de algum
// 			// circulo impresso.
// 			for(itr = circulos.begin(); itr != circulos.end(); itr++) {
		
// 				float dist = distPontos(x, y, (*itr)->getX(), (*itr)->getY());
// 				int raio = circuloGenerico.getRaio();
				
// 				// Se sim, cria um "circuloArrastado" copiando o circulo clicado e
// 				// remove o circulo clicado da lista.
// 				if(dist <= raio) {
										
// 					arrastarCirculo = true;
// 					circuloArrastado = new CirculoImpresso(*itr);
					
// 					int centroX = circuloArrastado->getX();
// 					int centroY = circuloArrastado->getY();
					
// 					dragX = x - centroX;
// 					dragY = y - centroY;
					
// 					CirculoImpresso* circuloDesaloc = *itr;
// 					circulos.erase(itr);
// 					delete(circuloDesaloc);
// 					break;
// 				}
// 			}
// 		}
		
// 	} else if(state == GLUT_UP) {
		
// 		if(button == GLUT_RIGHT_BUTTON) {
			
// 			// Se o botao direito foi solto com um circulo sendo arrastado,
// 			// verifica se existe conflito com um circulo impresso e imprime
// 			// o circulo arrastado de acordo: posicao atual caso nao haja conflito
// 			// ou posicao antes de ser arrastado caso haja conflito.
// 			if(arrastarCirculo == true) {
				
// 				int centroX = x - dragX;
// 				int centroY = y - dragY;
				
// 				if(verificarConflito(centroX, centroY) == false) {
// 					circuloArrastado->setX(x - dragX);
// 					circuloArrastado->setY(y - dragY);
// 				}
				
// 				circulos.push_back(circuloArrastado);
// 				arrastarCirculo = false;
// 			}
// 		}
// 	}
// }

// bool verificarConflito(int x, int y) {
	
// 	// Itera sobre os circulos impressos buscando distancia de 2 * raio entre o centro
// 	// de um circulo e a coordenada passada.
// 	for(itr = circulos.begin(); itr != circulos.end(); itr++) {
		
// 		float dist = distPontos(x, y, (*itr)->getX(), (*itr)->getY());
// 		int raio = circuloGenerico.getRaio();
		
// 		if(dist <= 2 * raio) {
// 			return true;
// 		}
// 	}
	
// 	return false;
// }

// void idle(void) {
// 	glutPostRedisplay();
// }

int main(int argc, char** argv) {
	
	setlocale(LC_ALL, "En_US");
	string strArquivo;
	
	// Se houve passagem de argumento, considera o caminho passado.
	if(argc > 1) {
    	
		string subdir(argv[1]);
    	strArquivo = subdir + "config.xml";
  		
  		if(strArquivo.at(0) != '.') {
  			strArquivo = "." + strArquivo;
  		}
    
    // Se nao houve passagem de argumento, considera a pasta de execucao.
    } else {
    	strArquivo = "./config.xml";
	}
		
	char chArquivo[strArquivo.length() + 1];
	strcpy(chArquivo, strArquivo.c_str());
    		
	/* 
	 * Abertura e leitura do arquivo config.xml:
	 */

	XMLDocument xmlConfig;
	XMLError erroLoad = xmlConfig.LoadFile(chArquivo);

	// "erroLoad" recebe zero se "LoadFile" for bem sucedida.
	if( erroLoad != 0 ) {
		cout << "Erro: Falha ao abrir config.xml" << endl;
		return ERRO_ABERTURA_CONFIG_XML;
	}
	
	bool leituraConfigSucesso = LeituraConfig(xmlConfig);
	
	if(leituraConfigSucesso == false) {
		cout << "Erro: Falha ao ler config.xml apos aberto" << endl;
		return ERRO_LEITURA_CONFIG_XML;
	}
	
	/* 
	 * Abertura e leitura do arquivo arena.svg:
	 */
	
	XMLDocument xmlArena;
	erroLoad = xmlArena.LoadFile(arena->getArquivo().c_str());

	// "erroLoad" recebe zero se "LoadFile" for bem sucedida.
	if( erroLoad != 0 ) {
		cout << "Erro: Falha ao abrir arena.svg" << endl;
		return ERRO_ABERTURA_ARENA_SVG;
	}
	
	bool leituraArenaSucesso = LeituraArena(xmlArena);
	
	if(leituraArenaSucesso == false) {
		cout << "Erro: Falha ao ler arena.svg apos aberto" << endl;
		return ERRO_LEITURA_ARENA_SVG;
	}
	
	// cout << jogador->getMultiplicador() << endl;
	// cout << jogador->getCirculo()->getRaio() << endl;
	// cout << jogador->getCirculo()->getCorR() << endl;
	// cout << jogador->getCirculo()->getCorG() << endl;
	// cout << jogador->getCirculo()->getCorB() << endl;
	// cout << jogador->getCirculo()->getCX() << endl;
	// cout << jogador->getCirculo()->getCY() << endl;
	
	// cout << arena->getArquivo() << endl;
	// cout << arena->getCirculo()->getRaio() << endl;
	// cout << arena->getCirculo()->getCorR() << endl;
	// cout << arena->getCirculo()->getCorG() << endl;
	// cout << arena->getCirculo()->getCorB() << endl;
	// cout << arena->getCirculo()->getCX() << endl;
	// cout << arena->getCirculo()->getCY() << endl;
	
	// cout << janela->getLargura() << endl;
	// cout << janela->getAltura() << endl;
	// cout << janela->getTitulo() << endl;
	
	/* 
	 * Iniciando GLUT:
	 */

	// glutInit(&argc, argv);
	// glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// glutInitWindowSize(janela.getLargura(), janela.getAltura());
	// glutInitWindowPosition(100, 100);
	// glutCreateWindow(janela.getTitulo());
	// init();
	// glutPassiveMotionFunc(mousePassiveMotion);
	// glutMouseFunc(mouseClick);
	// glutMotionFunc(mouseMotion);
	// glutDisplayFunc(display);
	// glutIdleFunc(idle);
	// glutMainLoop();
	
	// // Libera alocacao de circulos impressos.
	// for(itr = circulos.begin(); itr != circulos.end(); itr++)
	// 	delete(*itr);
	
	delete janela;
	delete jogador;
	delete arena;

	return SUCESSO;
}
