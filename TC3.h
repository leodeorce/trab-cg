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
#include "Arena.h"
#include "Inimigo.h"
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

class TC3 {
	Arena* arena;
	Pista* pista;
	list<Inimigo*> inimigosVoadores;
	list<Inimigo*> inimigosTerrestres;
	char keyStatus[256] = {0};
	const unsigned char keyDecolar = 'u';
	const unsigned char keyCima = 'w';
	const unsigned char keyEsquerda = 'a';
	const unsigned char keyBaixo = 's';
	const unsigned char keyDireita = 'd';
public:
	Janela* janela;
	Jogador* jogador;
	Erros LeituraArquivos(const char*);
	void DesenharArena(void);
	void DesenharJogador(void);
	void DesenharPista(void);
	void DesenharInimigosVoadores(void);
	void DesenharInimigosTerrestres(void);
	void KeyDown(unsigned char);
	void KeyUp(unsigned char);
	bool PossivelConflitoX(GLfloat);
	bool PossivelConflitoY(GLfloat);
	bool PossivelConflitoInimigos(GLfloat, GLfloat);
	bool PossivelConflitoArena(GLfloat, GLfloat);
	void Atualizar(GLint);
	~TC3();
private:
	Erros LeituraConfig(XMLDocument&);
	Erros LeituraArena(XMLDocument&);
	void AdicionarInimigoVoador(Inimigo*);
	void AdicionarInimigoTerrestre(Inimigo*);
	void DesenharInimigos(list<Inimigo*>&);
	void LiberarListaInimigos(list<Inimigo*>&);
};

#endif /* TC3_H */
