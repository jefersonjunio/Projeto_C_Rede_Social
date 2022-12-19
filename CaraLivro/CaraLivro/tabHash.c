//------- Inclusões

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "tabHash.h" 

#include "ListaE.h" 


//------- Fim Inclusões

void imprimeHash(infoLista_t dado) {
    criarLinha(_LINHA_DIVISORIA_, TAM_TELA_UM);
    criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, dado);
    criarLinha(_LINHA_DIVISORIA_, TAM_TELA_UM);

}

boolean_t addItemHash(infoLista_t* end, infoLista_t item) {
    *end = item;
    return (end != NULL);
}


int compararHash(infoLista_t itemUM, infoLista_t itemDois) {
    if (((char*)itemUM) == ((char*)itemDois)) {
        return 0;
    }
    else if (((char*)itemUM) > ((char*)itemDois)) {
        return 1;
    }
    else
    {
        return -1;
    }
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void tabelaHash_inicializa(tabelaHash_t* tabHash, uint32_t tamanho) {

    uint32_t i;

    // Cria o espaço para as listas da tabela
    tabHash->tabela = (listaE_t**)malloc(sizeof(listaE_t*) * tamanho);
    if (tabHash->tabela == NULL) return;

    tabHash->tamanho = tamanho;
    tabHash->nItens = 0;

    // Cria as listas
    for (i = 0; i < tamanho; i++) {
        tabHash->tabela[i] = malloc(sizeof(listaE_t));
        inicializaLista(tabHash->tabela[i]);
    }
}

uint32_t funcaoHash(itemTH_t item) {
    return item + 23429;
}

void tabelaHash_finaliza(tabelaHash_t* tabHash) {

    uint32_t i;

    // Destroi as listas
    for (i = 0; i < tabHash->tamanho; i++) {
        liberaLista(tabHash->tabela[i]);
    }

    // Libera o espaço para as listas
    free(tabHash->tabela);

    tabHash->tabela = NULL;
    tabHash->tamanho = 0;
    tabHash->nItens = 0;
}


static uint32_t tabelaHash_posicaoSegura(tabelaHash_t* tabHash, uint32_t posicao) {
    return posicao % tabHash->tamanho;
}


boolean_t tabelaHash_insere(tabelaHash_t* tabHash, itemTH_t item) {

    uint32_t posicao;
    itemListaE_t* itemLista;

    // Calcula a posição onde inserir o elemento
    posicao = funcaoHash(item);
    posicao = tabelaHash_posicaoSegura(tabHash, posicao);

    // Verifica se o item já está na lista
    // Procura na lista
    itemLista = buscarItemLista(tabHash->tabela[posicao], item, addItemHash);
    if (itemLista != NULL) return FALSE;

    // Vai na lista e insere
    insereInicioLista(tabHash->tabela[posicao], item, addItemHash);

    // Se chegou até aqui é porque conseguiu inserir
    tabHash->nItens++;
    return TRUE;
}


boolean_t tabelaHash_estaPresente(tabelaHash_t* tabHash, itemTH_t item) {

    uint32_t posicao;
    itemListaE_t* itemLista;

    // Calcula a posição onde inserir o elemento
    posicao = funcaoHash(item);
    posicao = tabelaHash_posicaoSegura(tabHash, posicao);

    // Procura na lista
    itemLista = buscarItemLista(tabHash->tabela[posicao], item, compararHash);

    // Verifica se encontrou
    return itemLista != NULL;
}


boolean_t tabelaHash_remove(tabelaHash_t* tabHash, itemTH_t item) {

    uint32_t posicao;
    boolean_t removeu;

    // Calcula a posição onde inserir o elemento
    posicao = funcaoHash(item);
    posicao = tabelaHash_posicaoSegura(tabHash, posicao);

    // Tenta remover
    removeu = retiraItemLista(tabHash->tabela[posicao], item, compararHash);
    tabHash->nItens--;
    return removeu;
}


void tabelaHash_imprime(tabelaHash_t* tabHash) {

    uint32_t i;

    for (i = 0; i < tabHash->tamanho; i++) {
        imprimeLista(tabHash->tabela[i], imprimeHash);
    }
}