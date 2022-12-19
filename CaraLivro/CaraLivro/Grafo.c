//------- Inclusoes

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ListaE.h"
#include "Grafo.h"

//-------- Fim Inclusoes


//-------- Funcoes Grafo Lista Adjacencia


void imprimeGrafo(infoLista_t dado) {
	printf("%d", (dadoVertice_t)dado);
}

boolean_t addItemGrafo(infoLista_t* end, infoLista_t item) {
	*end = item;
	return (end != NULL);
}

int compararItemGrafo(infoLista_t itemUM, infoLista_t itemDois) {
	if (((dadoVertice_t)itemUM) == ((dadoVertice_t)itemDois)) {
		return 0;
	}
	else if (((dadoVertice_t)itemUM) > ((dadoVertice_t*)itemDois)) {
		return 1;
	}
	else
	{
		return -1;
	}
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void inicializaGrafoVazio(grafo_t* grafo) {
	grafo->numArestas = 0;
	grafo->numVerticesAtual = 0;
	grafo->numVerticesGerados = 0;
	grafo->verticesGrafo = NULL;

	grafo->funcoes.funcaoAtribui = addItemGrafo;
	grafo->funcoes.funcaoCompara = compararItemGrafo;
	grafo->funcoes.funcaoImprime = imprimeGrafo;
}


boolean_t criaNovoVertice(grafo_t* grafo, dadoVertice_t idUnico) {
	boolean_t conseguiuAdicionar = FALSE;
	int novaPos = grafo->numVerticesAtual + 1;

	verticeGrafo_t* vertice = buscaVerticeGrafo(grafo, idUnico);

	if (vertice == NULL) {

		verticeGrafo_t** temp = (verticeGrafo_t**)realloc(grafo->verticesGrafo, novaPos * sizeof(verticeGrafo_t*));

		if (temp != NULL) {
			grafo->verticesGrafo = temp;

			verticeGrafo_t* posTemp = (verticeGrafo_t*)malloc(sizeof(verticeGrafo_t));

			if (posTemp != NULL) {

				grafo->verticesGrafo[novaPos - 1] = posTemp;

				grafo->funcoes.funcaoAtribui(&grafo->verticesGrafo[novaPos - 1]->idVertice, idUnico);
				inicializaLista(&grafo->verticesGrafo[novaPos - 1]->listaConexoes);

				grafo->numVerticesAtual++;
				grafo->numVerticesGerados++;
				conseguiuAdicionar = TRUE;

			}
		}

	}

	return conseguiuAdicionar;
}


boolean_t criaAdjacencia(grafo_t* grafo, verticeGrafo_t* verticeBase, dadoVertice_t verticeAdj) {
	boolean_t inserido = FALSE;

	if (verticeBase != NULL && verticeBase->idVertice != verticeAdj && buscarItemLista(&verticeBase->listaConexoes, verticeAdj, grafo->funcoes.funcaoCompara) == NULL) {
		inserido = insereOrdenado(&verticeBase->listaConexoes, verticeAdj, grafo->funcoes.funcaoCompara, grafo->funcoes.funcaoAtribui);
		if (inserido) grafo->numArestas++;
	}

	return inserido;
}


boolean_t removeAdjacencia(grafo_t* grafo, verticeGrafo_t* verticeBase, dadoVertice_t verticeAdj) {
	boolean_t removido = FALSE;

	if (verticeBase != NULL && verticeBase->idVertice != verticeAdj) {
		removido = retiraItemLista(&verticeBase->listaConexoes, verticeAdj, grafo->funcoes.funcaoCompara);
		if (removido) grafo->numArestas--;
	}

	return removido;
}


boolean_t removeVerticeGrafo(grafo_t* grafo, verticeGrafo_t* verticeRemove) {
	boolean_t semReferencias = TRUE;
	boolean_t conseguiuRemover = FALSE;

	if (verticeRemove != NULL && buscaVerticeGrafo(grafo, verticeRemove->idVertice) != NULL) {

		for (int i = 0; i < grafo->numVerticesAtual; i++) {
			if (grafo->verticesGrafo[i]->idVertice != verticeRemove->idVertice) {
				if (buscarItemLista(&grafo->verticesGrafo[i]->listaConexoes, verticeRemove->idVertice, grafo->funcoes.funcaoCompara) != NULL) {
					semReferencias = retiraItemLista(&grafo->verticesGrafo[i]->listaConexoes, verticeRemove->idVertice, grafo->funcoes.funcaoCompara);
				}
			}
		}

		if (verticeRemove->listaConexoes.numItens != NULL)
			liberaLista(&verticeRemove->listaConexoes);

		grafo->numVerticesAtual--;

		conseguiuRemover = TRUE;
	}

	return (conseguiuRemover && semReferencias);
}


verticeGrafo_t* buscaVerticeGrafo(grafo_t* grafo, dadoVertice_t idVertice) {
	uint32_t i;
	verticeGrafo_t* verticeLocalizado = NULL;

	for (i = 0; i < grafo->numVerticesAtual; i++) {
		if (grafo->verticesGrafo[i]->idVertice == idVertice)
			verticeLocalizado = grafo->verticesGrafo[i];;
	}

	return verticeLocalizado;
}


void liberaGrafo(grafo_t* grafo) {
	uint32_t i, c = 0;

	if (grafo->verticesGrafo != NULL) {

		for (i = (grafo->numVerticesAtual - 1); i >= 0; i--) {
			;
			if (removeVerticeGrafo(grafo, &grafo->verticesGrafo[i])) c++;
		}

		free(grafo->verticesGrafo);
	}
}

//-------- Fim Funcoes Grafo Lista Adjacencia