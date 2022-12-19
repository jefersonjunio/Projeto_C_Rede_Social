//------- Inclusões

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "Rede.h"
#include "Perfil.h"
#include "Uteis.h"
#include "Grafo.h"



//------- Fim Inclusões


//-------- Funcoes de cadastro 

void inicializaRede(caraLivro_t* estruturaSistema) {
	estruturaSistema->numPerfis = 0;
	estruturaSistema->perfilAtivo = NULL;
	estruturaSistema->vetorPerfis = NULL;
	inicializaGrafoVazio(&estruturaSistema->relacoesPerfis);
}

boolean_t cadastrarNovoPerfil(caraLivro_t* estruturaSistema) {
	boolean_t cadastrado = FALSE;
	uint32_t qtdPerfisAtual = estruturaSistema->numPerfis;
	perfil_t** vertorPerfis = estruturaSistema->vetorPerfis;

	char nome[MAX_NOME], login[MAX_LOGIN], senha[MAX_SENHA];

	criaLinhaCabecalho(_CENTRO_, TAM_TELA_UM, "NOVO CADASTRO ");
	printf("\n\tEscolha seu login [MAX 15 Caracteres]: ");
	lerString(login, MAX_LOGIN);

	if (encontrarPerfil(vertorPerfis, estruturaSistema->numPerfis, login) == NULL) {
		estruturaSistema->vetorPerfis = (perfil_t**)realloc(estruturaSistema->vetorPerfis, (qtdPerfisAtual + 1) * sizeof(perfil_t*));
		if (estruturaSistema->vetorPerfis != NULL) {

			printf("\tEscolha seu senha [MAX 7 Caracteres]: ");
			lerString(senha, MAX_SENHA);

			printf("\tDigite seu nome [MAX 50 Caracteres]: ");
			lerString(nome, MAX_NOME);

			estruturaSistema->vetorPerfis[qtdPerfisAtual] = criarNovoPerfil(nome, login, senha, (qtdPerfisAtual));
			criaNovoVertice(&estruturaSistema->relacoesPerfis, qtdPerfisAtual);
			estruturaSistema->vetorPerfis[qtdPerfisAtual]->endGrafo = buscaVerticeGrafo(&estruturaSistema->relacoesPerfis, qtdPerfisAtual);

			estruturaSistema->numPerfis++;
			cadastrado = TRUE;
		}
	}
	else {
		criaLinhaCabecalho(_CENTRO_, 50, "LOGIN JÁ EXISTE");
	}

	return cadastrado;
}

boolean_t realizarLogin(caraLivro_t* estruturaSistema) {
	char login[MAX_LOGIN], senha[MAX_SENHA];
	boolean_t autenticado = FALSE;
	perfil_t* perfilEncontrado;

	criaLinhaCabecalho(_CENTRO_, TAM_TELA_UM, "REALIZAR LOGIN ");
	printf("\n\tSeu login [MAX 15 Caracteres]: ");
	lerString(login, MAX_LOGIN);
	perfilEncontrado = encontrarPerfil(estruturaSistema->vetorPerfis, estruturaSistema->numPerfis, login);

	if (perfilEncontrado == NULL) {
		criaLinhaCabecalho(_CENTRO_, TAM_TELA_UM, "LOGIN INVALIDO");
	}
	else {
		printf("\n\tSua Senha [MAX 15 Caracteres]: ");
		lerString(senha, MAX_SENHA);
		autenticado = autenticarLogin(estruturaSistema->vetorPerfis, estruturaSistema->numPerfis, login, senha);
		if (autenticado) {
			estruturaSistema->perfilAtivo = perfilEncontrado;
			reativarPerfil(estruturaSistema->perfilAtivo);
		}
		else criaLinhaCabecalho(_CENTRO_, TAM_TELA_UM, "SENHA INVALIDA ");
	}

	return autenticado;
}

void criarPost(perfil_t* perfilAtual) {

	if (!novoPostPerfil(perfilAtual)) {
		criaLinhaCabecalho(_CENTRO_, TAM_TELA_UM, "Nao foi possivel criar o post");
	}
	else {
		imprimirPostagens(perfilAtual, perfilAtual);
	}

}

//---------- Fim funcoes de cadastro