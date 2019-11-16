/*
 * Arquivo: TC4.h
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC4
*/

#ifndef TC4_H
#define TC4_H

#include <GL/glut.h>
#include <vector>
#include "Arena.h"
#include "Bomba.h"
#include "InimigoAviao.h"
#include "InimigoBase.h"
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

class TC4 {

protected:
	Arena* arena;
	Pista* pista;
	Jogador* jogador;
	
	GLint frametime = 0;
	
	vector<Tiro*> tirosJogador;
	vector<Tiro*> tirosInimigos;
	vector<Bomba*> bombas;
	vector<InimigoAviao*> inimigosAviao;
	vector<InimigoBase*> inimigosBase;
	
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
	const GLfloat ajusteMultVel = 0.01;
	
	GLfloat inimVel = 0.05;
	GLfloat inimFreqTiro = 0.2;
	GLfloat inimMultVel = 2.0;
	GLfloat inimMultVelTiro = 1.0;
	GLfloat msEntreTiros = 5000.0;
	
	GLint qtdeBasesInicial = 0;
	GLint qtdeBasesAtual = 0;
	bool jogadorVence = false;
	bool jogadorPerde = false;
	
public:
	Janela* janela;
	
	Erros LeituraArquivos(const char*);
	void setFrametime(GLint);
	void setJogadorVence(bool);
	void setJogadorPerde(bool);
	bool getJogadorVence(void);
	bool getJogadorPerde(void);
	void DesenharArenaCirculo(void);
	void DesenharArenaContorno(void);
	void DesenharJogador(void);
	void DesenharPista(void);
	void DesenharInimigosAviao(void);
	void DesenharInimigosBase(void);
	void DesenharTiros(void);
	void DesenharBombas(void);
	void KeyDown(unsigned char);
	void KeyUp(unsigned char);
	bool PossivelConflito(GLint);
	void AtualizarJogador(void);
	void AtualizarInimigos(void);
	void AtualizarTiros(void);
	void AtualizarBombas(void);
	void AtualizarJogo(void);
	void AtualizarMousePosicao(GLint, GLint);
	void AtualizarMouseBotoes(GLint, GLint);
	void TeleportarJogador(void);
	void TeleportarInimigoAviao(InimigoAviao*);
	void InimigosAtirar(void);
	void AtribuirEstadosInimigos(void);
	void AtribuirAngulosInimigos(void);
	void DesenharTela(const char*, GLfloat, GLfloat, GLfloat);
	~TC4();
	
private:
	Erros LeituraConfig(XMLDocument&);
	Erros LeituraArena(XMLDocument&);
	void AdicionarInimigoAviao(InimigoAviao*);
	void AdicionarInimigoBase(InimigoBase*);
	bool PossivelConflitoArena(GLfloat, GLfloat, GLfloat);
	bool PossivelConflitoInimigos(GLfloat, GLfloat, GLfloat);
	bool PossivelConflitoTiros(GLfloat, GLfloat, GLfloat);
	GLfloat DistanciaPontoAReta(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
	void LiberarTiros(void);
	void LiberarBombas(void);
	void Reset(void);
};

#endif /* TC4_H */
