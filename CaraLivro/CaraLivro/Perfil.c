//------- Inclusões
////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "Perfil.h"
#include "ListaE.h"
#include "Grafo.h"
#include "Postagem.h"
#include "Pilha.h"
#include "Menus.h"

//------- Fim Inclusões


//-------- Funcoes Perfil

boolean_t autenticarLogin(perfil_t** perfisRede, uint32_t numPerfis, char* login, char* senha) {
	boolean_t resultado = FALSE;
	perfil_t* perfilTestado = encontrarPerfil(perfisRede, numPerfis, login);

	if (perfilTestado != NULL) {
		resultado = (strcmp(perfilTestado->dadosPerfil.login, login) == 0 && strcmp(perfilTestado->dadosPerfil.senha, senha) == 0);
	}

	return resultado;
}

perfil_t* encontrarPerfil(perfil_t** perfisRede, uint32_t numPerfis, char* login) {
	int i;
	perfil_t* perfil = NULL;
	boolean_t encontrado = FALSE;

	for (i = 0; i < numPerfis && !encontrado; i++) {
		if (strcmp(perfisRede[i]->dadosPerfil.login, login) == 0) {
			perfil = perfisRede[i];
			encontrado = TRUE;
		}
	}

	return perfil;
}

perfil_t* criarNovoPerfil(char* nome, char* login, char* senha, uint32_t idUnico) {
	perfil_t* novo = (perfil_t*)malloc(sizeof(perfil_t));

	if (novo != NULL) {

		//Inicializa Config Perfil
		novo->idUnicioPerfil = idUnico;
		novo->visibilidade = TRUE;
		inicializaLista(&novo->postagens);

		//Inicializa Dados do Perfil
		strcpy(novo->dadosPerfil.login, login);
		strcpy(novo->dadosPerfil.nome, nome);
		strcpy(novo->dadosPerfil.senha, senha);
	}

	return novo;
}

boolean_t desativarPerfil(perfil_t* usuario) {
	if (usuario != NULL) {
		usuario->visibilidade = FALSE;
	}
}

boolean_t reativarPerfil(perfil_t* usuario) {
	if (usuario != NULL) {
		usuario->visibilidade = TRUE;
	}
}

boolean_t novoPostPerfil(perfil_t* usuario) {
	char conteudo[MAX_CONTEUDO];

	criaLinhaCabecalho(_CENTRO_, TAM_TELA_UM, "NOVO POST");
	printf("\n\tDIGITE O CONTEUDO [MAX - 50caracteres]:\n\t");
	lerString(conteudo, MAX_CONTEUDO);

	return insereInicioLista(&usuario->postagens, postagemCria(conteudo, usuario->dadosPerfil.login, usuario->postagens.numItens, usuario->idUnicioPerfil), addPostPerfil);
}

boolean_t deletarPostagem(perfil_t* usuario, post_t* postagem) {
	boolean_t removida = FALSE;

	if (retiraItemLista(&usuario->postagens, postagem, postagemCompara)) {
		removida = postagemDeleta(postagem);
		usuario->postagens.numItens--;
	}

	return removida;
}

boolean_t curtiPostagem(perfil_t* usuario, post_t* postagem) {
	boolean_t existe = tabelaHash_estaPresente(&postagem->tabelaInteracoes, usuario->dadosPerfil.login);


	if (existe) return descurtirPostagem(usuario, postagem);
	else return  tabelaHash_insere(&postagem->tabelaInteracoes, usuario->dadosPerfil.login);
}

boolean_t descurtirPostagem(perfil_t* usuario, post_t* postagem) {
	boolean_t removido = FALSE;

	if (tabelaHash_estaPresente(&postagem->tabelaInteracoes, usuario->dadosPerfil.login)) {
		removido = tabelaHash_remove(&postagem->tabelaInteracoes, usuario->dadosPerfil.login);
	}

	return removido;
}

void visitarPerfil(perfil_t* usuarioLogado, perfil_t* perfilVisitado, perfil_t** perfisRede, grafo_t* grafo) {
	int numAmigos = perfilVisitado->endGrafo->listaConexoes.numItens;
	boolean_t sairPefil = FALSE;

	do {
		criarQuebraLinha();
		criaLinhaCabecalho(_CENTRO_, TAM_TELA_UM, usuarioLogado->dadosPerfil.nome);
		criaLinhaCabecalho(_CENTRO_, TAM_TELA_UM, "VISITANDO PERFIL DE");

		opcao_t opcoes = menuVisitaPerfil(perfilVisitado->dadosPerfil.nome);

		switch (opcoes)
		{
		case _VER_LISTA_AMIGOS_:
			visualizarAmigos(perfilVisitado, perfisRede, grafo);
			break;
		case _SEGUIR_:
			adicionarAmizade(usuarioLogado, perfilVisitado, grafo);
			break;
		case _VER_POSTAGENS_:
			imprimirPostagens(usuarioLogado, perfilVisitado);
			break;
		default:
			sairPefil = TRUE;
			break;
		}
	} while (!sairPefil);


}

void visualizarAmigos(perfil_t* perfil, perfil_t** perfisRede, grafo_t* grafo) {
	int i, numAmigos = perfil->endGrafo->listaConexoes.numItens;
	itemListaE_t* amgAtual = perfil->endGrafo->listaConexoes.primeiro;
	boolean_t parar = FALSE;

	criaLinhaCabecalho(_CENTRO_, TAM_TELA_UM, "AMIGOS DE: ");
	criaLinhaCabecalho(_CENTRO_, TAM_TELA_UM, perfil->dadosPerfil.login);

	while (amgAtual != NULL && !parar) {
		uint32_t pos = (uint32_t)amgAtual->dadoArmazenado;
		perfil_t* perfilAmigo = perfisRede[pos];

		if (perfilAmigo->visibilidade) {

			criarQuebraLinha();
			criaLinhaCabecalho(_CENTRO_, TAM_TELA_UM, perfilAmigo->dadosPerfil.nome);

			opcao_t opc = menuVisualizarPerfis();
			switch (opc)
			{
			case _VISITAR_PERFIL_:
				visitarPerfil(perfil, perfisRede[pos], perfisRede, grafo);
				break;
			case _SEGUIR_:
				adicionarAmizade(perfil, perfisRede[pos], grafo);
				break;
			case _ROLAR_FEED_:
				break;
			default:
				parar = TRUE;
				break;
			}

		}

		amgAtual = amgAtual->proxItem;
	}

}

void preparaPilhaImpressao(pilha_t* pilha, perfil_t* perfil) {
	int i;

	for (i = 0; i < pilha->capacidade; i++) {
		post_t postBusca;
		postBusca.idPost = i;
		itemListaE_t* posLista = buscarItemLista(&perfil->postagens, &postBusca, postagemCompara);
		empilhaPilha(pilha, posLista->dadoArmazenado, addPostPilha);
	}
}

void imprimirPostagens(perfil_t* usuarioLogado, perfil_t* perfilVisitado) {
	boolean_t pararFeed = FALSE;
	int i, numPost = perfilVisitado->postagens.numItens;
	pilha_t pilhaImpressao;
	inicializaPilha(&pilhaImpressao, numPost);

	preparaPilhaImpressao(&pilhaImpressao, perfilVisitado);


	for (i = 0; i < numPost && !pararFeed; i++) {
		post_t* posImprimir;
		desempilhaPilha(&pilhaImpressao, &posImprimir, addPostPerfil);
		postagemImprime(posImprimir, perfilVisitado->dadosPerfil.login);

		do
		{
			opcao_t opcao;

			if (usuarioLogado->idUnicioPerfil == perfilVisitado->idUnicioPerfil)
				opcao = menuTimeLine();
			else
				opcao = menuOpcoesPost();


			switch (opcao) {
			case _SAIR_:
				pararFeed = TRUE;
				break;
			case _CURTIR_:
				curtiPostagem(usuarioLogado, posImprimir);
				postagemImprime(posImprimir, usuarioLogado->dadosPerfil.login);
				break;

			case _DETALHES_:
				postagemDetalhadaImprime(posImprimir, usuarioLogado->dadosPerfil.login);
				break;

			case _ROLAR_FEED_:
				if (desempilhaPilha(&pilhaImpressao, &posImprimir, addPostPerfil)) {
					postagemImprime(posImprimir, usuarioLogado->dadosPerfil.login);
				}
				else {
					criaLinhaCabecalho(_CENTRO_, TAM_TELA_UM, "VOCE VISUALIZOU TDS POSTAGENS");
					pararFeed = TRUE;
				}
				break;
			default:
				deletarPostagem(usuarioLogado, posImprimir);
				pararFeed = TRUE;
				break;
			}

		} while (!pararFeed);
	}
}

void prepararPilhaTimeLine(perfil_t* usuarioLogado, uint32_t numPerfis, perfil_t** perfisRede, pilha_t* pilha) {
	int i;

	for (i = 0; i < pilha->capacidade; i++) {
		if (perfisRede[i]->postagens.numItens > 0) {
			itemListaE_t* posLista = buscarItemLista(&perfisRede[i]->postagens, perfisRede[i]->postagens.primeiro->dadoArmazenado, postagemCompara);
			empilhaPilha(pilha, posLista->dadoArmazenado, addPostPilha);
		}
	}
}

void imprimirTimeLine(perfil_t* usuarioLogado, uint32_t numPerfis, perfil_t** perfisRede, grafo_t* grafo) {
	int i;
	boolean_t pararRolagem = FALSE;
	pilha_t pilhaImpressao;
	inicializaPilha(&pilhaImpressao, numPerfis);
	prepararPilhaTimeLine(usuarioLogado, numPerfis, perfisRede, &pilhaImpressao);
	int impressoes = pilhaImpressao.numItens;

	for (i = 0; i < impressoes && !pararRolagem; i++) {
		post_t* posImprimir;
		desempilhaPilha(&pilhaImpressao, &posImprimir, addPostPerfil);

		if (posImprimir->idDonoPost != usuarioLogado->idUnicioPerfil && perfisRede[posImprimir->idDonoPost]->visibilidade == TRUE) {

			postagemImprime(posImprimir, posImprimir->donoPost);

			opcao_t opcao = menuOpcoesTimeLine();

			switch (opcao) {
			case _SAIR_:
				pararRolagem = TRUE;
				break;
			case _CURTIR_:
				curtiPostagem(usuarioLogado, posImprimir);
				postagemImprime(posImprimir, posImprimir->donoPost);
				break;

			case _DETALHES_:
				postagemDetalhadaImprime(posImprimir, posImprimir->donoPost);
				break;

			case _ROLAR_FEED_:
				if (desempilhaPilha(&pilhaImpressao, &posImprimir, addPostPerfil)) {
					postagemImprime(posImprimir, posImprimir->donoPost);
				}
				else {
					criaLinhaCabecalho(_CENTRO_, TAM_TELA_UM, "VOCE VISUALIZOU TDS POSTAGENS");
					pararRolagem = TRUE;
				}
				break;
			default:
				visitarPerfil(usuarioLogado, perfisRede[posImprimir->idDonoPost], perfisRede, grafo);
				pararRolagem = TRUE;
				break;
			}
		}

	}
}

boolean_t adicionarAmigosPeloLogin(perfil_t* usuarioLogado, uint32_t numPerfis, perfil_t** perfisRede, grafo_t* grafo) {
	char login[MAX_LOGIN];
	perfil_t* perfilAmg;
	boolean_t add = FALSE;

	criaLinhaCabecalho(_CENTRO_, TAM_TELA_UM, "ADICIONAR AMIGO");
	printf("\n\tDIGITE O @ [MAX 15 caracters]:\n\t");
	lerString(login, MAX_LOGIN);

	perfilAmg = encontrarPerfil(perfisRede, numPerfis, login);

	if (perfilAmg != NULL) {
		add = adicionarAmizade(usuarioLogado, perfilAmg, grafo);
	}

	return add;
}

boolean_t adicionarAmizade(perfil_t* usuario, perfil_t* perfilVisitado, grafo_t* grafo) {
	criaAdjacencia(grafo, usuario->endGrafo, perfilVisitado->idUnicioPerfil);
}

boolean_t desfazerAmizade(perfil_t* usuario, perfil_t* perfilVisitado, grafo_t* grafo) {
	removeAdjacencia(grafo, usuario->endGrafo, perfilVisitado->idUnicioPerfil);
}

void listarPerfis(perfil_t** pefisRede, uint32_t numPerfis) {
	int i;
	criaLinhaCabecalho(_CENTRO_, TAM_TELA_UM, "LISTAGEM DE PERFIS");
	for (i = 0; i < numPerfis; i++) {
		if (pefisRede[i]->visibilidade == TRUE) {
			criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, pefisRede[i]->dadosPerfil.nome);
		}
	}
}

//-------- Fim Funcoes Hash Aberto