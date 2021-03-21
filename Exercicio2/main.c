//Higor Raphael Faria e Sousa - 11811BCC014
//Leonardo Frangello Franzese - 11721BCC029

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formatacao_arquivo.h"
#include "busca_sequencial.h"
#include "busca_por_posicao.h"

int main()
{
    char nomeArquivoOriginal[20] = "cep.txt";
    char nomeNovoArquivo[20] = "cepFormatado.bin";

    cria_arquivo_formatado(nomeArquivoOriginal, nomeNovoArquivo);

    int menuSelecionado;
    printf("Bem vindo(a) ao sistema de buscas de endereco.\n");
    while(1){
        printf("Digite 1 para acessar o menu de busca sequencial de\n");
        printf("enderecos, 2 para acessar o menu de busca de enderecos\n");
        printf("por posicao ou 0 para sair.\n");
        scanf("%d", &menuSelecionado);
        if(menuSelecionado < 1 || menuSelecionado > 2){
            if(menuSelecionado == 0){
                break;
            }
            printf("\nOpcao invalida.\n");
            continue;
        }

        switch (menuSelecionado){
        case 1:
            menu_busca_sequencial(nomeNovoArquivo);
            break;
        case 2:
            menu_busca_por_posicao(nomeNovoArquivo);
            break;
        default:
            break;
        }

        printf("\n");
    }

    return 0;
}
