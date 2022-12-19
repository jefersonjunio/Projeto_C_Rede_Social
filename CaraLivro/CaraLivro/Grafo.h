#pragma once

#ifndef __GRAFO_h__
#define __GRAFO_h__

//------- Inclusoes

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ListaE.h"

//-------- Fim Inclusoes


//-------- Constantes

#define SUCESSO (0)
#define TRUE (1==1)
#define FALSE (1!=1)
#define max2(a,b) ((a >b)? a : b)

//-------- Fim Constantes


//-------- Dado Armazenado Grafo (Lista de Adjacencia)

typedef uint32_t dadoVertice_t;

//-------- Fim Dado Armazenado Grafo (Lista de Adjacencia)


//-------- Estrutura Grafo (Lista de Adjacencia)

struct funcoesGrafo_s {
	imprimirDado_f funcaoImprime;
	atribuirDado_f funcaoAtribui;
	compararDado_f funcaoCompara;
};

typedef struct funcoesGrafo_s funcoesGrafo_t;

struct verticeGrafo_s {
	dadoVertice_t idVertice;
	listaE_t listaConexoes;
};

typedef struct verticeGrafo_s verticeGrafo_t;

struct grafo_s {
	uint32_t numArestas;
	uint32_t numVerticesAtual;
	uint32_t numVerticesGerados;
	verticeGrafo_t** verticesGrafo;
	funcoesGrafo_t funcoes;
};

typedef struct grafo_s grafo_t;

//-------- Fim Estrutura Grafo (Lista de Adjacencia)


//-------- Assinatura Funcoes Grafo (Lista de Adjacencia)

void inicializaGrafoVazio(grafo_t* grafo);
boolean_t criaNovoVertice(grafo_t* grafo, dadoVertice_t idVertice);
boolean_t criaAdjacencia(grafo_t* grafo, verticeGrafo_t* verticeBase, dadoVertice_t idVerticeAdj);
boolean_t removeAdjacencia(grafo_t* grafo, verticeGrafo_t* verticeBase, dadoVertice_t idVerticeAdj);
verticeGrafo_t* buscaVerticeGrafo(grafo_t* grafo, dadoVertice_t idVertice);
void liberaGrafo(grafo_t* grafo);

//-------- Fim Assinatura Funcoes Grafo (Lista de Adjacencia)

#endif // __GRAFO_h__