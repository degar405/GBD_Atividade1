#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arquivo_indice.h"

void cria_arquivo_de_indices(char *nomeArquivoOriginal, char *nomeNovoArquivo){
    FILE *arquivoOriginal;
    arquivoOriginal = fopen(nomeArquivoOriginal, "r");
    if(arquivoOriginal == NULL){
        printf("Erro ao abrir o arquivo original de Ceps.\n");
        system("pause");
        exit(1);
    }

    FILE *arquivoNovo;
    arquivoNovo = fopen(nomeNovoArquivo, "wb");
    if(arquivoNovo == NULL){
        printf("Erro ao abrir o arquivo novo de Ceps para escrita.\n");
        system("pause");
        exit(1);
    }

    char *pLinhaOriginal = (char *) malloc(121 * sizeof(char));
    char *pFinalLinha;
    int posicaoRegistro = 0;
    int tamanhoLinha;

    while(1){
        pLinhaOriginal = fgets(pLinhaOriginal, 121, arquivoOriginal);
        if(feof(arquivoOriginal))
            break;

        pFinalLinha = memchr(pLinhaOriginal, 10, strlen(pLinhaOriginal));
        if(pFinalLinha == NULL || pFinalLinha == pLinhaOriginal){
            posicaoRegistro++;
            continue;
        }

        tamanhoLinha = (pFinalLinha - pLinhaOriginal) + 2;
        fwrite(&posicaoRegistro, sizeof(int), 1, arquivoNovo);

        fflush(arquivoNovo);

        posicaoRegistro += tamanhoLinha;
    }

    fclose(arquivoOriginal);
    fclose(arquivoNovo);

    free(pLinhaOriginal);

    return;
}
