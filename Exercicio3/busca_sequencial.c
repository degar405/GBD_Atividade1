#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "busca_sequencial.h"

int seleciona_logradouro_linha(char *dest, char *linha){
    char *pFinalLogradouro = memchr(linha, '|', strlen(linha));
    if(pFinalLogradouro == NULL){
        printf("Erro ao selecionar logradouro da linha: %s", linha);
        exit(-1);
    }

    int tamanhoLogradouro = pFinalLogradouro - linha;

    if(tamanhoLogradouro > 0){
        memcpy(dest, linha, tamanhoLogradouro);
        dest[tamanhoLogradouro] = '\0';
    }

    return tamanhoLogradouro;
}

void seleciona_cidade_linha(char *dest, char *linha){
    char *pInicioCidade = memchr(linha, '|', strlen(linha));
    if(pInicioCidade == NULL){
        printf("Erro ao selecionar cidade da linha: %s", linha);
        exit(-1);
    }
    pInicioCidade++;
    char *pFinalCidade = memchr(pInicioCidade, '|', strlen(linha));
    if(pFinalCidade == NULL){
        printf("Erro ao selecionar cidade da linha: %s", linha);
        exit(-1);
    }

    int tamanhoCidade = pFinalCidade - pInicioCidade;
    memcpy(dest, pInicioCidade, tamanhoCidade);
    dest[tamanhoCidade] = '\0';
}

void seleciona_uf_linha(char *dest, char *linha){
    char *pInicioCidade = memchr(linha, '|', strlen(linha));
    if(pInicioCidade == NULL){
        printf("Erro ao selecionar UF da linha: %s", linha);
        exit(-1);
    }
    pInicioCidade++;
    char *pInicioUF = memchr(pInicioCidade, '|', strlen(linha));
    if(pInicioUF == NULL){
        printf("Erro ao selecionar UF da linha: %s", linha);
        exit(-1);
    }
    pInicioUF++;
    char *pFinalUF = memchr(pInicioUF, '|', strlen(linha));
    if(pFinalUF == NULL){
        printf("Erro ao selecionar UF da linha: %s", linha);
        exit(-1);
    }

    int tamanhoUF = pFinalUF - pInicioUF;
    memcpy(dest, pInicioUF, tamanhoUF);
    dest[tamanhoUF] = '\0';
}

void seleciona_cep_linha(char *dest, char *linha){
    char *pInicioCidade = memchr(linha, '|', strlen(linha));
    if(pInicioCidade == NULL){
        printf("Erro ao selecionar CEP da linha: %s", linha);
        exit(-1);
    }
    pInicioCidade++;
    char *pInicioUF = memchr(pInicioCidade, '|', strlen(linha));
    if(pInicioUF == NULL){
        printf("Erro ao selecionar CEP da linha: %s", linha);
        exit(-1);
    }
    pInicioUF++;
    char *pInicioCEP = memchr(pInicioUF, '|', strlen(linha));
    if(pInicioCEP == NULL){
        printf("Erro ao selecionar CEP da linha: %s", linha);
        exit(-1);
    }
    pInicioCEP++;
    char *pFinalCEP = memchr(pInicioCEP, 10, strlen(linha));
    if(pFinalCEP == NULL){
        printf("Erro ao selecionar CEP da linha: %s", linha);
        exit(-1);
    }

    int tamanhoCEP = pFinalCEP - pInicioCEP;
    memcpy(dest, pInicioCEP, tamanhoCEP);
    dest[tamanhoCEP] = '\0';
}

void finaliza_execucao_programa(FILE *arquivo, char *pLinha, char *pTextoCampo){
    printf("Houve um erro durante a execução do programa.\n");

    fclose(arquivo);

    free(pLinha);
    free(pTextoCampo);

    exit(-1);
}

void busca_enderecos(int codigoOperacao, char *textoBusca, char *nomeArquivo){
    FILE *arquivo;
    arquivo = fopen(nomeArquivo, "r");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo de CEPs para leitura.\n");
        system("pause");
        exit(1);
    }

    char *pLinha = (char *) malloc(121 * sizeof(char));
    char *pTextoCampo = (char *) malloc(70 * sizeof(char));
    int tamanhoLogradouro;

    while(1){
        fgets(pLinha, 121, arquivo);
        if(feof(arquivo))
            break;

        if(pLinha == NULL || pLinha[0] == '\n')
            continue;

        switch(codigoOperacao){
        case 1:
            tamanhoLogradouro = seleciona_logradouro_linha(pTextoCampo, pLinha);
            if(tamanhoLogradouro == 0)
                continue;
            break;
        case 2:
            seleciona_cidade_linha(pTextoCampo, pLinha);
            break;
        case 3:
            seleciona_uf_linha(pTextoCampo, pLinha);
            break;
        case 4:
            seleciona_cep_linha(pTextoCampo, pLinha);
            break;
        default:
            finaliza_execucao_programa(arquivo, pLinha, pTextoCampo);
        }

        if(strstr(pTextoCampo, textoBusca) != NULL){
            printf("%s", pLinha);
        }
    }

    fclose(arquivo);

    free(pLinha);
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

    printf("Bem vindo(a) ao sistema de busca sequencial de enderecos.");
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
