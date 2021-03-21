#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "acesso_direto.h"

int busca_posicao(char *nomeArquivo, int indice){
    FILE *arquivo;
    arquivo = fopen(nomeArquivo, "rb");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo de indices para leitura.\n");
        system("pause");
        exit(1);
    }

    int posicaoIndice = (indice - 1) * sizeof(int);
    if(fseek(arquivo, posicaoIndice, SEEK_SET) != 0)
        return -1;

    int posicao;
    if(fread(&posicao, sizeof(int), 1, arquivo) == 0)
        return -1;

    fclose(arquivo);
    return posicao;
}

int recupera_linha_por_posicao(char *dest,char *nomeArquivo, int posicao){
    FILE *arquivo;
    arquivo = fopen(nomeArquivo, "r");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo de CEPs para leitura.\n");
        system("pause");
        exit(1);
    }

    if(fseek(arquivo, posicao, SEEK_SET) != 0)
        return -1;

    fgets(dest, 121, arquivo);
    if(feof(arquivo))
        return -1;

    fclose(arquivo);
    return 0;
}

int recupera_linha_por_indice(char *arquivoCep, char *arquivoIndice, int indice){
    int posicaoLinha;

    posicaoLinha = busca_posicao(arquivoIndice, indice);
    if(posicaoLinha == -1)
        return -1;

    char *linha = (char *) malloc(121 * sizeof(char));
    if(recupera_linha_por_posicao(linha, arquivoCep, posicaoLinha) == 0){
        printf("%s", linha);
        return 0;
    }

    return -1;
}

void menu_acesso_indexado(char *arquivoCep, char *arquivoIndice){
    int indiceBuscado;
    int posicaoRegistro;

    printf("Bem vindo(a) ao sistema de acesso indexado a enderecos.");
    while(1){
        printf("\nDigite o indice que deseja acessar ou 0 para sair.\n");
        scanf("%d", &indiceBuscado);

        if(indiceBuscado < 1){
            if(indiceBuscado == 0)
                return;
            printf("Indice digitado eh invalido.\n");
            continue;
        }

        if(recupera_linha_por_indice(arquivoCep, arquivoIndice, indiceBuscado) == -1){
           printf("Indice digitado eh invalido.\n");
        }
    }
}
