#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formatacao_arquivo.h"
#include "busca_por_posicao.h"

int busca_endereco(int posicao, char *nomeArquivo){
    FILE *arquivo;
    arquivo = fopen(nomeArquivo, "rb");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo de CEPs para leitura.\n");
        system("pause");
        exit(1);
    }

    posicao = (posicao / sizeof(item)) * sizeof(item);

    if(fseek(arquivo, posicao, SEEK_SET) != 0){
        fclose(arquivo);
        return -1;
    }

    item *registro = (item *) malloc(sizeof(item));

    if(fread(registro, sizeof(item), 1, arquivo) == 0){
        fclose(arquivo);
        free(registro);
        return -1;
    }

    printf("%s - %s - %s - %d\n", registro->logradouro, registro->cidade, registro->uf, registro->cep);

    fclose(arquivo);
    free(registro);
    return 0;
}

void menu_busca_por_posicao(char *nomeArquivo){
    int posicaoBuscada;

    printf("\nBem vindo(a) ao sistema de busca de enderecos por posicao.");
    while(1){
        printf("\nDigite a posicao para a busca do endereco ou -1 para sair.\n");
        scanf("%d", &posicaoBuscada);
        if(posicaoBuscada < 0){
            if(posicaoBuscada == -1)
                break;
            printf("\nPosição digitada é inválida.\n");
            continue;
        }

        if(busca_endereco(posicaoBuscada, nomeArquivo) == -1){
            printf("\nPosição digitada é inválida.\n");
            continue;
        }
    }
}
