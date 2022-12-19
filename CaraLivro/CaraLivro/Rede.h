#pragma once

#ifndef __REDE_h__
#define __REDE_h__

//------- Inclusões

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "Perfil.h"
#include "Uteis.h"
#include "Grafo.h"

//------- Fim Inclusões



//-------- Estrutura Padrão Rede

struct caraLivro_s {
	perfil_t* perfilAtivo;
	uint32_t numPerfis;
	perfil_t** vetorPerfis;
	grafo_t relacoesPerfis;
};

typedef struct caraLivro_s caraLivro_t;

//-------- Estrutura Padrão Rede


//-------- Assinatura Funcoes

void inicializaRede(caraLivro_t* estruturaSistema);

boolean_t realizarLogin(caraLivro_t* estruturaSistema);
boolean_t cadastrarNovoPerfil(caraLivro_t* estruturaSistema);

void criarPost(perfil_t* perfilAtual);

//void encerrarRede(caraLivro_t* estruturaSitema);

//-------- Fim Assinatura Funcoes 

#endif //__REDE_h__