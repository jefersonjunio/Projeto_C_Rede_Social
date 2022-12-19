#pragma once

#ifndef __PERFIL_h__
#define __PERFIL_h__

//------- Inclusões

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "ListaE.h" 
#include "Grafo.h"
#include "Postagem.h"
#include "Pilha.h"

//------- Fim Inclusões


//-------- Constantes

#define MAX_NOME  (45 + 1)
#define MAX_LOGIN (15 + 1)
#define MAX_SENHA (7 + 1)
#define MAX_CONTEUDO (50 + 1)

//-------- Fim Constantes

//-------- Dado Armazenado 
//-------- Fim Dado Armazenado

//-------- Modelagem de Funcoes de Manipulacao e tipos 

typedef uint32_t boolean_t;

//-------- Fim Modelagem de Funcoes de Manipulacao e tipos


//-------- Estrutura 

struct dadosPerfil_s {
	char login[MAX_LOGIN];
	char senha[MAX_SENHA];
	char nome[MAX_NOME];
};

typedef struct dadosPerfil_s dadosPerfil_t;

struct perfil_s {
	uint32_t idUnicioPerfil;
	dadosPerfil_t dadosPerfil;
	listaE_t postagens;
	verticeGrafo_t* endGrafo;
	boolean_t visibilidade;
};

typedef struct perfil_s perfil_t;

//-------- Fim Estrutura 


//-------- Assinatura Funcoes 

boolean_t autenticarLogin(perfil_t** perfisRede, uint32_t numPerfis, char* login, char* senha);
perfil_t* encontrarPerfil(perfil_t** perfisRede, uint32_t numPerfis, char* login);
perfil_t* criarNovoPerfil(char* nome, char* login, char* senha, uint32_t idUnico);
boolean_t desativarPerfil(perfil_t* usuario);
boolean_t reativarPerfil(perfil_t* usuario);

boolean_t novoPostPerfil(perfil_t* usuario);
boolean_t deletarPostagem(perfil_t* usuario, post_t* postagem);
boolean_t curtiPostagem(perfil_t* usuario, post_t* postagem);
boolean_t descurtirPostagem(perfil_t* usuario, post_t* postagem);
void imprimirPostagens(perfil_t* usuarioLogado, perfil_t* perfilVisitado);

void visitarPerfil(perfil_t* usuarioLogado, perfil_t* perfilVisitado, perfil_t** perfisRede, grafo_t* grafo);
void visualizarAmigos(perfil_t* perfil, perfil_t** perfisRede, grafo_t* grafo);

void prepararPilhaTimeLine(perfil_t* usuarioLogado, uint32_t numPerfis, perfil_t** perfisRede, pilha_t* pilha);
void imprimirTimeLine(perfil_t* usuarioLogado, uint32_t numPerfis, perfil_t** perfisRede, grafo_t* grafo);

boolean_t adicionarAmizade(perfil_t* usuario, perfil_t* perfilVisitado, grafo_t* grafo);
boolean_t desfazerAmizade(perfil_t* usuario, perfil_t* perfilVisitado, grafo_t* grafo);

boolean_t adicionarAmigosPeloLogin(perfil_t* usuarioLogado, uint32_t numPerfis, perfil_t** perfisRede, grafo_t* grafo);

void listarPerfis(perfil_t** pefisRede, uint32_t numPerfis);


//----<<<<

/*
void visitarPerfil(perfil_t* usuarioLogado, perfil_t* perfilOrigem, perfil_t* perfilVisitado, perfil_t** perfisRede);

void imprimirAmigos(perfil_t* perfil, perfil_t** perfisRede);

void imprimirTimeLine(perfil_t* usuario, perfil_t** perfisRede);
*/

//-------- Fim Assinatura Funcoes 


#endif //__PERFIL_h_