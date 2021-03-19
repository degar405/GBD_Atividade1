#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "informacoes_linha.c"

void criaLinhaFormatada(char *pLinhaFormatada, Info_linha *info){
    char separador[2] = "|";
    char quebraDeLinha[2] = {'\n', '\0'};
    char linhaFormatada[121] = "";

    strcat(linhaFormatada, info->logradouro);
    strcat(linhaFormatada, separador);
    strcat(linhaFormatada, info->cidade);
    strcat(linhaFormatada, separador);
    strcat(linhaFormatada, info->uf);
    strcat(linhaFormatada, separador);
    strcat(linhaFormatada, info->cep);
    strcat(linhaFormatada, quebraDeLinha);

    strcpy(pLinhaFormatada, linhaFormatada);

    return;
}

void criaArquivoFormatado(char *nomeArquivoOriginal, char *nomeNovoArquivo){
    FILE *arquivoOriginal;
    arquivoOriginal = fopen(nomeArquivoOriginal, "r");
    if(arquivoOriginal == NULL){
        printf("Erro ao abrir o arquivo original de Ceps.\n");
        system("pause");
        exit(1);
    }

    FILE *arquivoNovo;
    arquivoNovo = fopen(nomeNovoArquivo, "w");
    if(arquivoNovo == NULL){
        printf("Erro ao abrir o arquivo novo de Ceps para escrita.\n");
        system("pause");
        exit(1);
    }

    char *pLinhaOriginal = (char *) malloc(121 * sizeof(char));
    Info_linha *dadosLinha = malloc(sizeof(Info_linha));
    char *pLinhaFormatada = (char *) malloc(121 * sizeof(char));

    while(1){
        pLinhaOriginal = fgets(pLinhaOriginal, 121, arquivoOriginal);
        if(feof(arquivoOriginal))
            break;

        extrair_informacoes_linha(dadosLinha, pLinhaOriginal);
        if(dadosLinha->cep[0] == '\0')
            continue;
        criaLinhaFormatada(pLinhaFormatada, dadosLinha);
        fputs(pLinhaFormatada, arquivoNovo);
        fflush(arquivoNovo);
    }

    fclose(arquivoOriginal);
    fclose(arquivoNovo);

    free(pLinhaOriginal);
    free(dadosLinha);
    free(pLinhaFormatada);

    return;
}

int main()
{
    char nomeArquivoOriginal[20] = "cep.txt";
    char nomeNovoArquivo[20] = "cepFormatado.txt";

    criaArquivoFormatado(nomeArquivoOriginal, nomeNovoArquivo);

    return 0;
}

