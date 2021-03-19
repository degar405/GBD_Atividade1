#include <stdlib.h>
#include <string.h>

typedef struct informacoes_linha {
    char cep[9];
    char uf[31];
    char cidade[39];
    char logradouro[67];
} Info_linha;

void extrair_informacoes_linha(Info_linha *dest, char *pLinha){
    char *pInicioUF;
    char *pInicioCidade;
    char *pInicioLogradouro;
    char *pFinalLinha;

    pFinalLinha = memchr(pLinha, 10, strlen(pLinha));
    if(pFinalLinha == NULL || pFinalLinha == pLinha){
        dest->cep[0] = '\0';
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

    memcpy(dest->cep, pLinha, tamanhoCep);
    memcpy(dest->uf, pInicioUF, tamanhoUF);
    memcpy(dest->cidade, pInicioCidade, tamanhoCidade);
    if (pInicioLogradouro != NULL)
        memcpy(dest->logradouro, pInicioLogradouro, tamanhoLogradouro);

    dest->cep[tamanhoCep] = '\0';
    dest->uf[tamanhoUF] = '\0';
    dest->cidade[tamanhoCidade] = '\0';
    dest->logradouro[tamanhoLogradouro] = '\0';
}
