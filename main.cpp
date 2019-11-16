/*
 * Arquivo: main.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC4
 */

#include <GL/glut.h>
#include <iostream>
#include <string>
#include "TC4.h"

using namespace std;

TC4 tc4;

void initialize(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(
		tc4.janela->getXI(), tc4.janela->getXF(),
		tc4.janela->getYI(), tc4.janela->getYF(),
		0.0, 1.0
	);
}

void keyDown(unsigned char key, int x, int y)
{
	tc4.KeyDown(key);
}

void keyUp(unsigned char key, int x, int y)
{
	tc4.KeyUp(key);
}

void passiveMouseMotion(int x, int y)
{
	tc4.AtualizarMousePosicao(x, y);
}

void mouseMotion(int x, int y)
{
	tc4.AtualizarMousePosicao(x, y);
}

void mouse(int button, int state, int x, int y)
{
	tc4.AtualizarMouseBotoes(button, state);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	tc4.DesenharArenaCirculo();
	tc4.DesenharPista();
	tc4.DesenharInimigosBase();
	tc4.DesenharBombas();
	tc4.DesenharTiros();
	
	if(tc4.getJogadorPerde() == false) {
		tc4.DesenharJogador();
	}
	
	tc4.DesenharInimigosAviao();
	tc4.DesenharArenaContorno();
	
	if(tc4.getJogadorVence() == true) {
		
		const char* str = "Ganhou";
		tc4.DesenharTela(str, 0.0, 1.0, 0.0);
		
	} else if(tc4.getJogadorPerde() == true) {
		
		const char* str = "Perdeu";
		tc4.DesenharTela(str, 1.0, 0.0, 0.0);
	}

	glutSwapBuffers();
}

void idle(void)
{
	static GLint tempoAnterior = 0;
	
	GLint tempoAtual = glutGet(GLUT_ELAPSED_TIME);
	GLint frametime = tempoAtual - tempoAnterior;
	
	tempoAnterior = tempoAtual;
	tc4.setFrametime(frametime);
	
	bool jogadorPerde = tc4.getJogadorPerde();
	
	if(jogadorPerde == false) {
		jogadorPerde = tc4.PossivelConflito(1);
	}
		
	if(jogadorPerde == true) {
		tc4.setJogadorPerde(jogadorPerde);
	} else if(tc4.getJogadorVence() == false) {
		tc4.InimigosAtirar();
	}
			
	tc4.AtualizarInimigos();
	tc4.AtualizarJogador();
	tc4.AtualizarTiros();
	tc4.AtualizarBombas();
	
	tc4.AtualizarJogo();
	
	glutPostRedisplay();
}

int RetornaErro(Erros erro)
{
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

int main(int argc, char** argv)
{
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
	Erros erroArquivo = tc4.LeituraArquivos(chArqConfig);
	
	if(erroArquivo != SUCESSO) {
		return RetornaErro(erroArquivo);
	}
	
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(tc4.janela->Largura(), tc4.janela->Altura());
	glutInitWindowPosition(100, 100);
	glutCreateWindow(tc4.janela->getTitulo().c_str());
	
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
