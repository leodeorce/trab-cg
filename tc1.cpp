/*
 * Arquivo: tc1.cpp
 * Autor: Leonardo Oliveira
 * Disciplina: Computacao Grafica 2019/2
 * Descricao: TC1
*/

#include <iostream>
#include <string>
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

/* Declaracao de variaveis globais */

Circulo circuloImpressao;
CirculoModelo circuloModelo;
Janela janela;

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
	
	const char* strValidacao = nullptr;
	strValidacao = elementoJanela->GetText();
	if(strValidacao == nullptr) return false;
	string titulo(strValidacao);
	
	janela.setTitulo(titulo);
	
	return true;
	
}

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
	
	// cout << circuloImpressao.getRaio() << endl;
	// cout << circuloImpressao.getCorR() << endl;
	// cout << circuloImpressao.getCorG() << endl;
	// cout << circuloImpressao.getCorB() << endl;
	
	// cout << circuloModelo.getRaio() << endl;
	// cout << circuloModelo.getCorR() << endl;
	// cout << circuloModelo.getCorG() << endl;
	// cout << circuloModelo.getCorB() << endl;
	
	// cout << circuloModelo.getCorSobreposicaoR() << endl;
	// cout << circuloModelo.getCorSobreposicaoG() << endl;
	// cout << circuloModelo.getCorSobreposicaoB() << endl;
	
	// cout << janela.getLargura() << endl;
	// cout << janela.getAltura() << endl;
	// cout << janela.getCorR() << endl;
	// cout << janela.getCorG() << endl;
	// cout << janela.getCorB() << endl;
	// cout << janela.getTitulo() << endl;
	
	return SUCESSO;

}
