#pragma once

#ifndef __UTEIS_h__
#define __UTEIS_h__


//------- Inclusões

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

//------- Fim Inclusões

//-------- Constantes

#define TAM_TELA_UM (50)
#define TAM_TELA_DOIS (150)

//-------- Fim Constantes


//-------- Enumeradores

/// <summary>
///		Enumerador Funcionalidades Menu Principal
/// </summary>
enum {
	_LINHA_MENU_,
	_LINHA_DIVISORIA_
};

/// <summary>
///		Enumerador Posicionamento Texto
/// </summary>
enum {
	_CENTRO_ = 1,
	_DIREITA_,
	_ESQUERDA_
};

//-------- Fim Enumeradores 


//-------- Assinatura Funcoes 

void criarLinha(int tipoLinha, int tamanhoLinha);
void criaLinhaCabecalho(int alinhamentoTexto, int tamanhoDaTela, char* textoCabecalho);
void criaLinhaTexto(int alinhamentoTexto, int tamanhoDaTela, char* textoLinha);
void criaLinhaPostAutor(int alinhamentoTexto, int tamanhoDaTela, char* textoCabecalho);

void removeBarraEne(char* string);
void lerString(char* endArmazenar, int MAX_STR);
void criarQuebraLinha();

#endif //__UTEIS_h__