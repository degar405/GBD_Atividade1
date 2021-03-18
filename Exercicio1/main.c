#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int formataLinha(char *pLinha, char *pLinhaFormatada){
    char *pInicioUF;
    char *pInicioCidade;
    char *pInicioLogradouro;
    char *pFinalLinha;

    pFinalLinha = memchr(pLinha, 10, strlen(pLinha));
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

    char cep[tamanhoCep + 1];
    char uf[tamanhoUF + 1];
    char cidade[tamanhoCidade + 1];
    char logradouro[tamanhoLogradouro + 1];

    memcpy(cep, pLinha, tamanhoCep);
    memcpy(uf, pInicioUF, tamanhoUF);
    memcpy(cidade, pInicioCidade, tamanhoCidade);
    if (pInicioLogradouro != NULL)
        memcpy(logradouro, pInicioLogradouro, tamanhoLogradouro);

    cep[tamanhoCep] = '\0';
    uf[tamanhoUF] = '\0';
    cidade[tamanhoCidade] = '\0';
    logradouro[tamanhoLogradouro] = '\0';

    char separador[2] = "|";
    char quebraDeLinha[2] = {'\n', '\0'};
    char linhaFormatada[121] = "";

    strcat(linhaFormatada, logradouro);
    strcat(linhaFormatada, separador);
    strcat(linhaFormatada, cidade);
    strcat(linhaFormatada, separador);
    strcat(linhaFormatada, uf);
    strcat(linhaFormatada, separador);
    strcat(linhaFormatada, cep);
    strcat(linhaFormatada, quebraDeLinha);

    strcpy(pLinhaFormatada, linhaFormatada);

    if (pInicioLogradouro != NULL)
        return 1;

    return 0;
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
    char *pLinhaFormatada = (char *) malloc(121 * sizeof(char));
    while(1){
        pLinhaOriginal = fgets(pLinhaOriginal, 121, arquivoOriginal);
        if(feof(arquivoOriginal))
            break;
        formataLinha(pLinhaOriginal, pLinhaFormatada);
        //printf("%s", pLinhaFormatada);
        fputs(pLinhaFormatada, arquivoNovo);
        fflush(arquivoNovo);
    }

    char teste[15] = "Terminou!";
    fputs(teste, arquivoNovo);

    fclose(arquivoOriginal);
    fclose(arquivoNovo);
}

int main()
{
    char nomeArquivoOriginal[20] = "cep.txt";
    char nomeNovoArquivo[20] = "cepFormatado.txt";

    criaArquivoFormatado(nomeArquivoOriginal, nomeNovoArquivo);

    return 0;
}
