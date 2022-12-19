//------- Inclusões
///////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "Postagem.h"
#include "tabHash.h"
#include "Perfil.h"


//------- Fim Inclusões


//-------- Funcoes Hash Aberto

int postagemCompara(infoLista_t postagemUm, infoLista_t postagemDois) {
    post_t* postUM = (post_t*)postagemUm;
    post_t* postDois = (post_t*)postagemDois;

    if ((postUM->idPost) == (postDois->idPost)) {
        return 0;
    }
    else if ((postUM->idPost) > (postDois->idPost)) {
        return 1;
    }
    else
    {
        return -1;
    }

}

post_t* postagemCria(infoPost_t* info, char* usuario, uint32_t idPost, uint32_t idDonoPost) {
    post_t* novo = (post_t*)malloc(sizeof(post_t));

    if (novo != NULL) {

        novo->idPost = idPost; //(usuario->postagens.numItens);
        novo->idDonoPost = idDonoPost;

        strcpy(novo->post, info);
        tabelaHash_inicializa(&novo->tabelaInteracoes, MAX_TABELA);
        strcpy(novo->donoPost, usuario);
    }

    return novo;
}

boolean_t postagemDeleta(post_t* postagem) {
    boolean_t deletado = FALSE;

    if (postagem != NULL) {
        tabelaHash_finaliza(&postagem->tabelaInteracoes);

        deletado = TRUE;
    }

    free(postagem);

    return deletado;
}

void postagemImprime(post_t* postagem, char* loginAtual) {
    boolean_t estaPresente;

    estaPresente = tabelaHash_estaPresente(&postagem->tabelaInteracoes, loginAtual);

    if (estaPresente == TRUE) {
        criaLinhaPostAutor(_ESQUERDA_, TAM_TELA_UM, postagem->donoPost);
        criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, postagem->post);
        printf("\n\t| VC + %d Curtiram essa postagem! %*s |", (postagem->tabelaInteracoes.nItens - 1), (int)(((TAM_TELA_UM - 2) - 30)), " ");

    }
    else {
        criaLinhaPostAutor(_ESQUERDA_, TAM_TELA_UM, postagem->donoPost);
        criaLinhaTexto(_ESQUERDA_, TAM_TELA_UM, postagem->post);
        printf("\n\t| %d Curtiram essa postagem! %*s |", postagem->tabelaInteracoes.nItens, (int)(((TAM_TELA_UM - 32))), " ");
        criarLinha(_LINHA_DIVISORIA_, TAM_TELA_UM);
    }

}

void postagemDetalhadaImprime(post_t* postagem, itemTH_t usuario) {

    postagemImprime(postagem, usuario);
    tabelaHash_imprime(&postagem->tabelaInteracoes);

}

boolean_t addPostPerfil(infoLista_t* end, infoLista_t dado) {
    *end = dado;
}


//-------- Fim Funcoes Hash Aberto