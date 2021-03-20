#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "formatacao_arquivo.h"

#define TAMANHO_LINHA_ARQUIVO_FORMATADO 121

typedef struct informacoes_linha {
    int cep;
    char uf[31];
    char cidade[39];
    char logradouro[67];
} Info_linha;

void extrair_informacoes_linha(Info_linha *dest, char *pLinha){
    char *pInicioUF;
    char *pInicioCidade;
    char *pInicioLogradouro;
    char *pFinalLinha;

    char cepAux[9];

    pFinalLinha = memchr(pLinha, 10, strlen(pLinha));
    if(pFinalLinha == NULL || pFinalLinha == pLinha){
        dest->cep = 0;
        dest->uf[0] = '\0';
        dest->cidade[0] = '\0';
        dest->logradouro[0] = '\0';
        return;
    }
    if(pLinha[(pFinalLinha - 1) - pLinha] == '\t'){
        pLinha[(pFinalLinha - 1) - pLinha] = '\n';
        pLinha[pFinalLinha - pLinha] = '\0';
    }

    pInicioUF = memchr(pLinha, 9, strlen(pLinha)) + 1;
    pInicioCidade = memchr(pInicioUF, 9, strlen(pInicioUF)) + 1;
    pInicioLogradouro = memchr(pInicioCidade, 9, strlen(pInicioCidade));
    if (pInicioLogradouro != NULL)
        pInicioLogradouro++;
    pFinalLinha = memchr(pLinha, 10, strlen(pLinha));

    int tamanhoCep = (pInicioUF - 1) - pLinha;
    int tamanhoUF = (pInicioCidade - 1) - pInicioUF;
    int tamanhoCidade;
    int tamanhoLogradouro;
    if (pInicioLogradouro != NULL){
        tamanhoCidade = (pInicioLogradouro - 1) - pInicioCidade;
        tamanhoLogradouro = pFinalLinha - pInicioLogradouro;
    } else {
        tamanhoCidade = pFinalLinha - pInicioCidade;
        tamanhoLogradouro = 0;
    }

    //TODO: VALIDAÇÃO DO TAMANHO MÁXIMO DE CADA CAMPO

    memcpy(cepAux, pLinha, tamanhoCep);
    memcpy(dest->uf, pInicioUF, tamanhoUF);
    memcpy(dest->cidade, pInicioCidade, tamanhoCidade);
    if (pInicioLogradouro != NULL)
        memcpy(dest->logradouro, pInicioLogradouro, tamanhoLogradouro);

    cepAux[tamanhoCep] = '\0';
    dest->cep = atoi(cepAux);
    dest->uf[tamanhoUF] = '\0';
    dest->cidade[tamanhoCidade] = '\0';
    dest->logradouro[tamanhoLogradouro] = '\0';
}

void cria_linha_formatada(char *pLinhaFormatada, Info_linha *info){
    char separador[2] = "|";
    char quebraDeLinha[2] = {'\n', '\0'};
    char linhaFormatada[121] = "";
    char cepAux[9];
    char tamanhoCampo[3];
    itoa(info->cep, cepAux, 10);

    itoa(strlen(info->logradouro), tamanhoCampo, 10);
    if(tamanhoCampo[1] == '\0'){
        tamanhoCampo[2] = tamanhoCampo[1];
        tamanhoCampo[1] = tamanhoCampo[0];
        tamanhoCampo[0] = '0';
    }
    strcat(linhaFormatada, tamanhoCampo);
    strcat(linhaFormatada, info->logradouro);

    itoa(strlen(info->cidade), tamanhoCampo, 10);
    if(tamanhoCampo[1] == '\0'){
        tamanhoCampo[2] = tamanhoCampo[1];
        tamanhoCampo[1] = tamanhoCampo[0];
        tamanhoCampo[0] = '0';
    }
    strcat(linhaFormatada, tamanhoCampo);
    strcat(linhaFormatada, info->cidade);

    itoa(strlen(info->uf), tamanhoCampo, 10);
    strcat(linhaFormatada, tamanhoCampo);
    strcat(linhaFormatada, info->uf);

    itoa(strlen(cepAux), tamanhoCampo, 10);
    strcat(linhaFormatada, tamanhoCampo);
    strcat(linhaFormatada, cepAux);

    strcat(linhaFormatada, quebraDeLinha);

    strcpy(pLinhaFormatada, linhaFormatada);

    return;
}

void cria_arquivo_formatado(char *nomeArquivoOriginal, char *nomeNovoArquivo){
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

    char *pLinhaOriginal = (char *) malloc(TAMANHO_LINHA_ARQUIVO_FORMATADO * sizeof(char));
    Info_linha *dadosLinha = (Info_linha *) malloc(sizeof(Info_linha));
    char *pLinhaFormatada = (char *) malloc(TAMANHO_LINHA_ARQUIVO_FORMATADO * sizeof(char));

    while(1){
        pLinhaOriginal = fgets(pLinhaOriginal, TAMANHO_LINHA_ARQUIVO_FORMATADO, arquivoOriginal);
        if(feof(arquivoOriginal))
            break;

        extrair_informacoes_linha(dadosLinha, pLinhaOriginal);
        if(dadosLinha->cep == 0)
            continue;
        cria_linha_formatada(pLinhaFormatada, dadosLinha);
        fwrite(pLinhaFormatada, 1, TAMANHO_LINHA_ARQUIVO_FORMATADO, arquivoNovo);
        fflush(arquivoNovo);
    }

    fclose(arquivoOriginal);
    fclose(arquivoNovo);

    free(pLinhaOriginal);
    free(dadosLinha);
    free(pLinhaFormatada);

    return;
}
