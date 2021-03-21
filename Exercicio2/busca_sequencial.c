#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formatacao_arquivo.h"
#include "busca_sequencial.h"

void busca_enderecos(int codigoOperacao, char *textoBusca, char *nomeArquivo){
    FILE *arquivo;
    arquivo = fopen(nomeArquivo, "rb");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo de CEPs para leitura.\n");
        system("pause");
        exit(1);
    }

    item *registro = (item *) malloc(sizeof(item));
    char *pTextoCampo = (char *) malloc(70 * sizeof(char));

    while(fread(registro, sizeof(item), 1, arquivo)){
        if(registro->cep == 0)
            continue;

        switch(codigoOperacao){
        case 1:
            if(registro->logradouro[0] == '\0')
                continue;
            strcpy(pTextoCampo, registro->logradouro);
            break;
        case 2:
            strcpy(pTextoCampo, registro->cidade);
            break;
        case 3:
            strcpy(pTextoCampo, registro->uf);
            break;
        case 4:
            itoa(registro->cep, pTextoCampo, 10);
            break;
        default:
            printf("Erro ao efetuar busca sequencial.");

            fclose(arquivo);

            free(registro);
            free(pTextoCampo);

            exit(-1);
        }

        if(strstr(pTextoCampo, textoBusca) != NULL){
            printf("%s - %s - %s - %d\n", registro->logradouro, registro->cidade, registro->uf, registro->cep);
        }
    }

    fclose(arquivo);

    free(registro);
    free(pTextoCampo);
}


void menu_busca_sequencial(char *nomeArquivo){
    int codigoOperacao;
    char textoBusca[70];
    char arrayTextoPergunta[4][20] = {
        "do logradouro",
        "da cidade",
        "da UF",
        "do CEP"
    };

    printf("\nBem vindo(a) ao sistema de busca sequencial de enderecos.");
    while(1){
        printf("\nEscolha por qual campo deseja realizar a busca. Digite\n");
        printf("1 para Logradouro\n");
        printf("2 para Cidade\n");
        printf("3 para UF\n");
        printf("4 para CEP\n");
        printf("0 para sair\n");
        scanf("%d", &codigoOperacao);

        if(codigoOperacao < 1 || codigoOperacao > 4){
            if(codigoOperacao == 0){
                return;
            }
            printf("\nCódigo digitado é inválido.\n");
            continue;
        }

        while(1){
            printf("\nDigite o texto para buscar o endereco atraves %s ou 0 para voltar ao menu principal.\n", arrayTextoPergunta[codigoOperacao - 1]);
            setbuf(stdin, NULL);
            gets(textoBusca);
            setbuf(stdin, NULL);

            if(textoBusca[0] == '0' && textoBusca[1] == '\0')
                break;

            busca_enderecos(codigoOperacao, textoBusca, nomeArquivo);
        }
    }
}
