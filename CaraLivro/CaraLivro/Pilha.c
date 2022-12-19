// ------ - Inclusoes

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Pilha.h"
#include "Postagem.h"


//-------- Fim Inclusoes


//-------- Funcoes Pilha Lista

boolean_t addPostPilha(infoPilha_t * end, infoPilha_t dado) {
	*end = dado;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void inicializaPilha(pilha_t* pilha, uint32_t capacidade) {
	if (capacidade != 0) { //Se capacidade 0, nao tem porque inicializar pilha.
		pilha->capacidade = capacidade;
		pilha->numItens = 0;
		pilha->topoPilha = NULL;
	}
}


boolean_t pilhaVazia(pilha_t* pilha) {
	return (pilha->numItens == 0);
}


boolean_t empilhaPilha(pilha_t* pilha, infoPilha_t dado, atribuirDado_f metodoDeAtribuicao) {
	boolean_t conseguiuEmpilhar = FALSE;

	if (pilha->capacidade != pilha->numItens) { // Verificar se capacidade maxima foi atingida para que seja inserido um novo item.

		itemPilha_t* novo = malloc(sizeof(itemPilha_t));

		if (novo != NULL) { // Confirma se existe espaco alocado em novo para que possa inserir o dado e posiciona-lo no topo da pilha.
			conseguiuEmpilhar = metodoDeAtribuicao(&novo->dadoArmazenado, dado);

			if (conseguiuEmpilhar) {
				novo->proxItem = pilha->topoPilha;

				pilha->numItens++;
				pilha->topoPilha = novo;
			}
		}
	}

	return conseguiuEmpilhar;
}


boolean_t desempilhaPilha(pilha_t* pilha, infoPilha_t* enderecoRetornoDado, atribuirDado_f metodoDeAtribuicao) {
	boolean_t conseguiuDesempilhar = FALSE;

	if (!pilhaVazia(pilha)) { //Confirma se tem elementos na pilha.

		//Armazena endereco do topo da pilha e proximo item.
		itemPilha_t* atualTopo = pilha->topoPilha;
		itemPilha_t* temp = atualTopo->proxItem;

		conseguiuDesempilhar = metodoDeAtribuicao(enderecoRetornoDado, atualTopo->dadoArmazenado); // Salva o dado da pilha.

		if (conseguiuDesempilhar) {
			//free(atualTopo); // Libera topo da pilha.

			pilha->topoPilha = temp; //Posiciona topo da pilha no elemento seguinte.
			pilha->numItens--;
		}
	}

	return conseguiuDesempilhar;
}


void liberaPilha(pilha_t* pilha) {
	itemPilha_t* atualTopo = pilha->topoPilha;

	while (atualTopo != NULL) {
		itemPilha_t* tmp = atualTopo->proxItem;
		free(atualTopo);
		atualTopo = tmp;
	}
}


void imprimePilha(pilha_t* pilha, imprimirDado_f metodoDeImpressao) {
	itemPilha_t* atual = pilha->topoPilha;

	while (atual != NULL) {
		metodoDeImpressao(atual->dadoArmazenado);
		atual = atual->proxItem;
	}
}

//-------- Fim Funcoes Pilha Lista