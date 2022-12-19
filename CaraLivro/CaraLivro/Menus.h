#pragma once

#ifndef __MENUS_h__
#define __MENUS_h__

//------- Inclusões

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


#include "Uteis.h" 

//------- Fim Inclusões

//-------- Constantes

#define _MAX_OPC_PRINCIPAL_ (2)

//-------- Fim Constantes

//-------- Modelagem de Funcoes de Manipulacao e tipos 

typedef uint32_t boolean_t;
typedef int opcao_t;

//-------- Fim Modelagem de Funcoes de Manipulacao e tipos


//-------- Enumeradores

/// <summary>
///		Enumerador Funcionalidades Menu Principal
/// </summary>
enum {
	_SAIR_,
	_LOGIN_,
	_CADASTRO_,
	_LISTA_PERFIS_
	/*_ALTERAR_DADOS_,
	_DESATIVAR_PERFIL_*/
};


/// <summary>
///		Enumerador Funcionalidades Do Perfil
/// </summary>
enum {
	_TIME_LINE_ = 1,
	_MEU_PERFIL_,
	_ADICIONAR_AMIGOS_ = 4
};

/// <summary>
///		Enumerador Funcionalidades Menu Principal
/// </summary>
enum {
	_AMIZADES_ = 1,
	_MINHAS_POSTAGENS_,
	_CRIAR_POST_,
	_CONFIG_PERFIL_
};

enum {
	_RETORNAR_AO_PERFIL,
	_CURTIR_,
	_DETALHES_,
	_ROLAR_FEED_,
	_EXCLUIR_POSTAGEM_,
};

enum {
	_VISITAR_PERFIL_ = 4,

};

enum {
	_VER_LISTA_AMIGOS_ = 1,
	_SEGUIR_,
	_VER_POSTAGENS_

};

/// <summary>
///		Enumerador Funcionalidades Menu Acoes do Perfil
/// </summary>



//-------- Fim Enumeradores 


//-------- Assinatura Funcoes 

opcao_t lerOpcaoMenu();

opcao_t menuPrincipal();
opcao_t menuFuncionalidadesPerfil(char* nomeUsuarioAtual);
opcao_t menuMeuPerfil(char* nomeUsuarioAtual);
opcao_t menuTimeLine();
opcao_t menuVisualizarPerfis();
opcao_t menuVisitaPerfil(char* perfilVisitado);
opcao_t menuOpcoesPost();
opcao_t menuOpcoesTimeLine();

//void validaMenuInicial();

//-------- Fim Assinatura Funcoes 


#endif //__MENUS_h_