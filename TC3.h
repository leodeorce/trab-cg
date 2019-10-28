/*
 * Arquivo: TC3.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC3
*/

#ifndef TC3_H
#define TC3_H

#include <GL/glut.h>
#include <list>
#include <vector>
#include "Arena.h"
#include "Bomba.h"
#include "Inimigo.h"
#include "Janela.h"
#include "Jogador.h"
#include "Pista.h"
#include "tinyxml2.h"
#include "Tiro.h"

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

class TC3 {
	Arena* arena;
	Pista* pista;
	Jogador* jogador;
	GLint frametime = 0;
	bool colisaoInimigo = false;
	vector<Tiro*> tiros;
	vector<Bomba*> bombas;
	list<Inimigo*> inimigosVoadores;
	list<Inimigo*> inimigosTerrestres;
	char keyStatus[256] = {0};
	const unsigned char keyDecolar = 'u';
	const unsigned char keyEsquerda = 'a';
	const unsigned char keyDireita = 'd';
	const unsigned char keyReset = 'r';
	const unsigned char keyVelUp = '=';
	const unsigned char keyVelDown = '-';
	const unsigned char keyNumpadVelUp = '+';
	const unsigned char keyNumpadVelDown = '-';
	GLint mX = 0;
	GLint mY = 0;
	const GLfloat ajusteMult = 0.01f;
public:
	Janela* janela;
	Erros LeituraArquivos(const char*);
	void setFrametime(GLint);
	void setColisaoInimigo(bool);
	bool getColisaoInimigo(void);
	void DesenharArenaCirculo(void);
	void DesenharArenaContorno(void);
	void DesenharJogador(void);
	void DesenharPista(void);
	void DesenharInimigosVoadores(void);
	void DesenharInimigosTerrestres(void);
	void DesenharTiros(void);
	void DesenharBombas(void);
	void KeyDown(unsigned char);
	void KeyUp(unsigned char);
	bool PossivelConflito(GLint);
	void AtualizarJogador(void);
	void AtualizarTiros(void);
	void AtualizarBombas(void);
	void AtualizarMousePosicao(GLint, GLint);
	void AtualizarMouseBotoes(GLint, GLint);
	void TeleportarJogador(void);
	~TC3();
private:
	Erros LeituraConfig(XMLDocument&);
	Erros LeituraArena(XMLDocument&);
	void AdicionarInimigoVoador(Inimigo*);
	void AdicionarInimigoTerrestre(Inimigo*);
	bool PossivelConflitoArena(GLfloat, GLfloat, GLfloat);
	bool PossivelConflitoInimigos(GLfloat, GLfloat, GLfloat);
	GLfloat DistanciaPontoAReta(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
	void DesenharInimigos(list<Inimigo*>&);
	void LiberarTiros(void);
	void LiberarBombas(void);
	void LiberarListaInimigos(list<Inimigo*>&);
	void Reset(void);
};

#endif /* TC3_H */
