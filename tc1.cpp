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

using namespace std;
using namespace tinyxml2;

Circulo circuloImpressao;
CirculoModelo circuloModelo;
Janela janela;

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
	
	if( elemento->QueryFloatAttribute("corR", &corR) ) return false;
	if( elemento->QueryFloatAttribute("corG", &corG) ) return false;
	if( elemento->QueryFloatAttribute("corB", &corB) ) return false;
	
	janela.setCorR(corR);
	janela.setCorG(corG);
	janela.setCorB(corB);
	
	const char* strValidacao = nullptr;
	elementoJanela = elemento->FirstChildElement("titulo");
	strValidacao = elementoJanela->GetText();
	if(strValidacao == nullptr) return false;
	string titulo(strValidacao);
	
	janela.setTitulo(titulo);
	
	return true;
	
}

int main(int argc, char** argv) {

	if(argc > 1) {
		
		string prog(argv[0]);
		string subdir(argv[1]);
    	string dir = prog.substr(0, prog.find_last_of("/"));
    	string strArquivo = dir + subdir + "config.xml";
    	
    	int n = strArquivo.length();
    	char chArquivo[n + 1];
    	strcpy(chArquivo, strArquivo.c_str());
		
		XMLDocument xmlConfig;
		XMLError erroLoad = xmlConfig.LoadFile(chArquivo);
		
		if( !erroLoad ) {
			
			bool erroRead = LeituraXML(xmlConfig);
			if(!erroRead) {
				cout << "Erro: Falha ao ler arquivo de configuracoes" << endl;
				return 3;
			}
			
		} else {
			cout << "Erro: Falha ao abrir arquivo de configuracoes" << endl;
			return 2;
		}
		
	} else {
		cout << "Erro: Nao ha arquivo de configuracoes" << endl;
		return 1;
	}
	
	cout << circuloImpressao.getRaio() << endl;
	cout << circuloImpressao.getCorR() << endl;
	cout << circuloImpressao.getCorG() << endl;
	cout << circuloImpressao.getCorB() << endl;
	
	cout << circuloModelo.getRaio() << endl;
	cout << circuloModelo.getCorR() << endl;
	cout << circuloModelo.getCorG() << endl;
	cout << circuloModelo.getCorB() << endl;
	
	cout << circuloModelo.getCorSobreposicaoR() << endl;
	cout << circuloModelo.getCorSobreposicaoG() << endl;
	cout << circuloModelo.getCorSobreposicaoB() << endl;
	
	cout << janela.getLargura() << endl;
	cout << janela.getAltura() << endl;
	cout << janela.getCorR() << endl;
	cout << janela.getCorG() << endl;
	cout << janela.getCorB() << endl;
	cout << janela.getTitulo() << endl;
	
	return 0;

}
