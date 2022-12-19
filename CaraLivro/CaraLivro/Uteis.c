//------- Inclusões

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "Uteis.h" 

//------- Fim Inclusões


//-------- Funcoes Uteis

void criarLinha(int tipoLinha, int tamanhoLinha) {

	printf("\n\t");

	switch (tipoLinha) {
	case _LINHA_MENU_:
		printf("+");
		for (int i = 0; i < tamanhoLinha; i++) printf("-");
		printf("+");
		break;
	case _LINHA_DIVISORIA_:
		for (int i = 0; i < tamanhoLinha; i++) printf("-");
	default:
		break;
	}
}

void criaLinhaTexto(int alinhamentoTexto, int tamanhoDaTela, char* textoLinha) {
	if (alinhamentoTexto == _ESQUERDA_) printf("\n\t| %s%*s |", textoLinha, (int)(((tamanhoDaTela - 2) - strlen(textoLinha))), " ");
	else if (alinhamentoTexto == _CENTRO_) printf("\n\t| %*s%s%*s |", ((int)(tamanhoDaTela - strlen(textoLinha) / 2), " ", textoLinha, (int)(tamanhoDaTela - strlen(textoLinha) / 2), " "));
	else printf("\n\t| %*s%s |", ((int)((tamanhoDaTela - 2) - strlen(textoLinha))), " ", textoLinha);

	criarLinha(_LINHA_MENU_, tamanhoDaTela);
}

void criaLinhaCabecalho(int alinhamentoTexto, int tamanhoDaTela, char* textoCabecalho) {
	criarLinha(_LINHA_MENU_, tamanhoDaTela);
	printf("\n\t| %*s%s%*s |", (((tamanhoDaTela - 1) - strlen(textoCabecalho)) / 2), " ", textoCabecalho, (((tamanhoDaTela - 2) - strlen(textoCabecalho) + 1) / 2), " ");
	criarLinha(_LINHA_MENU_, tamanhoDaTela);
}

void criaLinhaPostAutor(int alinhamentoTexto, int tamanhoDaTela, char* textoCabecalho) {
	criarLinha(_LINHA_MENU_, tamanhoDaTela);
	printf("\n\t| %*sPost do %s%*s |", (((tamanhoDaTela - 1) - strlen(textoCabecalho) - 8) / 2), " ", textoCabecalho, (((tamanhoDaTela - 2) - strlen(textoCabecalho) + 1 - 8) / 2), " ");
	criarLinha(_LINHA_MENU_, tamanhoDaTela);
}

void criarQuebraLinha() {
	printf("\n\n\t");
}


void removeBarraEne(char* string) {
	int i;
	char lixo;
	for (i = 0; i < strlen(string); i++) {
		if (string[i] == '\n') {
			string[i] = '\0';
		}
	}
}

void lerString(char* endArmazenar, int MAX_STR) {
	scanf("\n");
	fgets(endArmazenar, MAX_STR, stdin);
	removeBarraEne(endArmazenar);
}