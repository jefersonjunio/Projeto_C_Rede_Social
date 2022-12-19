#pragma once

#ifndef __TABELA_HASH_h__
#define __TABELA_HASH_h__

//------- Inclusões

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "ListaE.h" 

//------- Fim Inclusões

/* Constantes */

/* Tipos */


typedef char* itemTH_t;

typedef uint32_t(*hash_f)(itemTH_t);

struct tabelaHash_s {
	// Tamanho da tabela
	uint32_t tamanho;
	// Endereço da função de cálculo do hash
	//hash_f funcaoHash;
	// Tabela Hash
	listaE_t** tabela;
	// Número de itens na tabela.
	uint64_t nItens;
};


typedef struct tabelaHash_s tabelaHash_t;

/* Funções Exportadas */

void tabelaHash_inicializa(tabelaHash_t* tabHash, uint32_t tamanho);
void tabelaHash_finaliza(tabelaHash_t* tabHash);
boolean_t tabelaHash_insere(tabelaHash_t* tabHash, itemTH_t item);
boolean_t tabelaHash_estaPresente(tabelaHash_t* tabHash, itemTH_t item);
boolean_t tabelaHash_remove(tabelaHash_t* tabHash, itemTH_t item);
void tabelaHash_imprime(tabelaHash_t* tabHash);
uint32_t funcaoHash(itemTH_t item);

#endif // __TABELA_HASH_h__