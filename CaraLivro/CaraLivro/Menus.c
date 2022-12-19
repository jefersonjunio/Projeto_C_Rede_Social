//------- Inclusões

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "Menus.h"
#include "Uteis.h"

//------- Fim Inclusões


//-------- Funcoes De Menus

opcao_t lerOpcaoMenu() {
	opcao_t opc;
	printf("\n\n\tDIGITE UMA OPCAO:\t");
	scanf("%d%*c", &opc);
	return opc;
}

opcao_t menuPrincipal() {
	opcao_t opcao;
	boolean_t ERRO;

	do {
		criaLinhaCabecalho(_CENTRO_, TAM_TELA_UM, "CARA LIVRO");
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "1 - LOGIN ");
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "2 - CADASTRO");
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "3 - LISTAR PERFIS ATIVOS");
		criaLinhaTexto(_DIREITA_, TAM_TELA_UM, "0 - FINALIZAR");

		opcao = lerOpcaoMenu();
		ERRO = opcao < _SAIR_&& opcao > _LISTA_PERFIS_;

		if (ERRO) printf("ERRO - OPCAO INVALIDA!");
	} while (ERRO);

	return opcao;
}

opcao_t menuFuncionalidadesPerfil(char* nomeUsuarioAtual) {
	opcao_t opcao;
	boolean_t ERRO;

	do {
		criarQuebraLinha();
		criaLinhaCabecalho(_CENTRO_, TAM_TELA_UM, "ACESSANDO COMO:");
		criaLinhaCabecalho(_CENTRO_, TAM_TELA_UM, nomeUsuarioAtual);
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "1 - TIME-LINE");
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "2 - MEU PERFIL");
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "3 - CRIAR POST");
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "4 - ADICIONAR AMIGOS");
		criaLinhaTexto(_DIREITA_, TAM_TELA_UM, "0 - SAIR");

		opcao = lerOpcaoMenu();
		ERRO = opcao < _SAIR_&& opcao > _CRIAR_POST_;

		if (ERRO) printf("ERRO - OPCAO INVALIDA!");
	} while (ERRO);

	return opcao;
}

opcao_t menuMeuPerfil(char* nomeUsuarioAtual) {
	opcao_t opcao;
	boolean_t ERRO;

	do {
		criarQuebraLinha();
		criaLinhaCabecalho(_CENTRO_, TAM_TELA_UM, nomeUsuarioAtual);
		criaLinhaCabecalho(_CENTRO_, TAM_TELA_UM, "MEU PERFIL");
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "1 - AMIZADES");
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "2 - MINHAS POSTAGENS");
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "3 - CRIAR POST");
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "4 - DESATIVAR");
		criaLinhaTexto(_DIREITA_, TAM_TELA_UM, "0 - VOLTAR");

		opcao = lerOpcaoMenu();
		ERRO = opcao < _SAIR_&& opcao > _CONFIG_PERFIL_;

		if (ERRO) printf("ERRO - OPCAO INVALIDA!");
	} while (ERRO);

	return opcao;
}


opcao_t menuTimeLine() {
	opcao_t opcao;
	boolean_t ERRO;

	do {
		criarLinha(_LINHA_DIVISORIA_, TAM_TELA_UM);
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "1 - CURTIR");
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "2 - DETALHES");
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "3 - ROLAR FEED");
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "4 - DELETAR POST");
		criaLinhaTexto(_DIREITA_, TAM_TELA_UM, "0 - RETORNAR AO PERFIL");
		criarLinha(_LINHA_DIVISORIA_, TAM_TELA_UM);

		opcao = lerOpcaoMenu();
		ERRO = opcao < _SAIR_&& opcao > _RETORNAR_AO_PERFIL;

		if (ERRO) printf("ERRO - OPCAO INVALIDA!");
	} while (ERRO);

	return opcao;
}


opcao_t menuOpcoesPost() {
	opcao_t opcao;
	boolean_t ERRO;

	do {
		criarLinha(_LINHA_DIVISORIA_, TAM_TELA_UM);
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "1 - CURTIR");
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "2 - DETALHES");
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "3 - ROLAR FEED");
		criaLinhaTexto(_DIREITA_, TAM_TELA_UM, "0 - RETORNAR AO PERFIL");
		criarLinha(_LINHA_DIVISORIA_, TAM_TELA_UM);

		opcao = lerOpcaoMenu();
		ERRO = opcao < _SAIR_&& opcao > _RETORNAR_AO_PERFIL;

		if (ERRO) printf("ERRO - OPCAO INVALIDA!");
	} while (ERRO);

	return opcao;
}

opcao_t menuOpcoesTimeLine() {
	opcao_t opcao;
	boolean_t ERRO;

	do {
		criarLinha(_LINHA_DIVISORIA_, TAM_TELA_UM);
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "1 - CURTIR");
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "2 - DETALHES");
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "3 - ROLAR FEED");
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "4 - VISITAR PERFIL");
		criaLinhaTexto(_DIREITA_, TAM_TELA_UM, "0 - RETORNAR");
		criarLinha(_LINHA_DIVISORIA_, TAM_TELA_UM);

		opcao = lerOpcaoMenu();
		ERRO = opcao < _SAIR_&& opcao > _RETORNAR_AO_PERFIL;

		if (ERRO) printf("ERRO - OPCAO INVALIDA!");
	} while (ERRO);

	return opcao;
}



opcao_t menuVisitaPerfil(char* perfilVisitado) {
	opcao_t opcao;
	boolean_t ERRO;

	do {
		criaLinhaCabecalho(_CENTRO_, TAM_TELA_UM, perfilVisitado);
		criarLinha(_LINHA_DIVISORIA_, TAM_TELA_UM);
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "1 - Ver lista amigos");
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "2 - Seguir");
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "3 - Ver postagens");
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "0 - Voltar");
		criarLinha(_LINHA_DIVISORIA_, TAM_TELA_UM);

		opcao = lerOpcaoMenu();
		ERRO = opcao < _SAIR_&& opcao > _SEGUIR_;

		if (ERRO) printf("ERRO - OPCAO INVALIDA!");
	} while (ERRO);

	return opcao;
}

opcao_t menuVisualizarPerfis() {
	opcao_t opcao;
	boolean_t ERRO;

	do {
		criarLinha(_LINHA_DIVISORIA_, TAM_TELA_UM);
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "1 - Visitar Perfil");
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "2 - Seguir");
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "3 - Continuar Lista");
		criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, "0 - Voltar");
		criarLinha(_LINHA_DIVISORIA_, TAM_TELA_UM);

		opcao = lerOpcaoMenu();
		ERRO = opcao < _SAIR_&& opcao > _ROLAR_FEED_;

		if (ERRO) printf("ERRO - OPCAO INVALIDA!");
	} while (ERRO);

	return opcao;
}