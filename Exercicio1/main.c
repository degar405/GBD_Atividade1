//Higor Raphael Faria e Sousa - 11811BCC014
//Leonardo Frangello Franzese - 11721BCC029

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formatacao_arquivo.h"
#include "busca_sequencial.h"

int main()
{
    char nomeArquivoOriginal[20] = "cep.txt";
    char nomeNovoArquivo[20] = "cepFormatado.txt";

    cria_arquivo_formatado(nomeArquivoOriginal, nomeNovoArquivo);

    menu_busca_sequencial(nomeNovoArquivo);

    return 0;
}
