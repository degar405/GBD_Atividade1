typedef struct item {
    int cep;
    char uf[31];
    char cidade[39];
    char logradouro[67];
} item;

void cria_arquivo_formatado(char *nomeArquivoOriginal, char *nomeNovoArquivo);
