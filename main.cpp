/*
 * Arquivo: main.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC3
 */

#include <GL/glut.h>
#include <iostream>
#include <string>
#include "TC3.h"

using namespace std;

TC3 tc3;

void initialize(void) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(
		tc3.janela->getXI(), tc3.janela->getXF(),
		tc3.janela->getYI(), tc3.janela->getYF(),
		0.0f, 1.0f
	);
}

void keyDown(unsigned char key, int x, int y) {
	tc3.KeyDown(key);
}

void keyUp(unsigned char key, int x, int y) {
	tc3.KeyUp(key);
}

void passiveMouseMotion(int x, int y) {
	tc3.AtualizarMousePosicao(x, y);
}

void mouseMotion(int x, int y) {
	tc3.AtualizarMousePosicao(x, y);
}

void mouse(int button, int state, int x, int y) {
	tc3.AtualizarMouseBotoes(button, state);
}

void display(void) {
	
	glClear (GL_COLOR_BUFFER_BIT);
	
	tc3.DesenharArena();
	tc3.DesenharPista();
	tc3.DesenharInimigosVoadores();
	tc3.DesenharInimigosTerrestres();
	
	if(tc3.getColisaoInimigo() == false) {
		tc3.DesenharJogador();
	}

	glutSwapBuffers();
}

void idle(void) {
	
	static GLint tempoAnterior = 0;
	
	GLint tempoAtual = glutGet(GLUT_ELAPSED_TIME);
	GLint frametime = tempoAtual - tempoAnterior;
	
	tempoAnterior = tempoAtual;
	tc3.setFrametime(frametime);
	
	bool colisaoInimigo = tc3.PossivelConflito(1);
	
	if(colisaoInimigo == true) {
		tc3.setColisaoInimigo(colisaoInimigo);
	}
	
	tc3.AtualizarJogador();
	
	glutPostRedisplay();
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

	return erro;
}

int main(int argc, char** argv) {

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
	
	const char* chArqConfig = strArqConfig.c_str();
	Erros erroArquivo = tc3.LeituraArquivos(chArqConfig);
	
	if(erroArquivo != SUCESSO) {
		return RetornaErro(erroArquivo);
	}
	
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(tc3.janela->Largura(), tc3.janela->Altura());
	glutInitWindowPosition(100, 100);
	glutCreateWindow(tc3.janela->getTitulo().c_str());
	
	initialize();
	
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutPassiveMotionFunc(passiveMouseMotion);
	glutMotionFunc(mouseMotion);
	glutMouseFunc(mouse);
	
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	
	glutMainLoop();

	return SUCESSO;
}
