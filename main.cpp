/*
 * Arquivo: tc2.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC2
 */

#include <GL/glut.h>
#include <iostream>
#include <string>
#include "TC2.h"

using namespace std;

TC2 tc2;

void initialize(void) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(
		tc2.janela->getXI(), tc2.janela->getXF(),
		tc2.janela->getYI(), tc2.janela->getYF(),
		0.0f, 1.0f
	);
}

void keyDown(unsigned char key, int x, int y) {
	tc2.KeyDown(key);
}

void keyUp(unsigned char key, int x, int y) {
	tc2.KeyUp(key);
}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT);

	tc2.DesenharArena();
	tc2.DesenharPista();
	tc2.DesenharJogador();
	tc2.DesenharInimigosVoadores();
	tc2.DesenharInimigosTerrestres();

	glutSwapBuffers();
}

void idle(void) {
	tc2.Atualizar();
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
	Erros erroArquivo = tc2.LeituraArquivos(chArqConfig);
	
	if(erroArquivo != SUCESSO) {
		return RetornaErro(erroArquivo);
	}
	
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(tc2.janela->Largura(), tc2.janela->Altura());
	glutInitWindowPosition(100, 100);
	glutCreateWindow(tc2.janela->getTitulo().c_str());
	
	initialize();
	
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	
	glutMainLoop();

	return SUCESSO;
}
