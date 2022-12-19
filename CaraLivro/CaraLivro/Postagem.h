#pragma once

#ifndef __POSTAGEM_h__
#define __POSTAGEM_h__

//------- Inclusões

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


#include "tabHash.h" 
#include "ListaE.h"
#include "Uteis.h"

//------- Fim Inclusões


//-------- Constantes

#define MAX_TABELA 1000

//-------- Fim Constantes


//-------- Modelagem de Funcoes de Manipulacao e tipos 

typedef char infoPost_t;

//-------- Fim Modelagem de Funcoes de Manipulacao e tipos


//-------- Estrutura 

struct post_s {
	char donoPost[50 + 1];
	uint32_t idDonoPost;
	infoPost_t post[50 + 1];
	uint32_t idPost;
	tabelaHash_t tabelaInteracoes;
};

typedef struct post_s post_t;

//-------- Fim Estrutura 


//-------- Assinatura Funcoes 

post_t* postagemCria(infoPost_t* info, char* usuario, uint32_t idPost, uint32_t idDonoPost);
boolean_t postagemDeleta(post_t* postagem);
void postagemImprime(post_t* postagem, char* loginAtual);
void postagemDetalhadaImprime(post_t* postagem, itemTH_t usuario);
boolean_t addPostPerfil(infoLista_t* end, infoLista_t dado);
int postagemCompara(infoLista_t postagemUm, infoLista_t postagemDois);

//-------- Fim Assinatura Funcoes 




#endif //__POSTAGEM_h_