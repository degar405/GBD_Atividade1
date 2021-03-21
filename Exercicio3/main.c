#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo_indice.h"
#include "acesso_direto.h"

int main()
{
    char nomeArquivoOriginal[20] = "cep.txt";
    char nomeNovoArquivo[20] = "indicesCep.bin";

    cria_arquivo_de_indices(nomeArquivoOriginal, nomeNovoArquivo);

    menu_acesso_indexado(nomeArquivoOriginal, nomeNovoArquivo);

    return 0;
}
