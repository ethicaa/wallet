#include "modulo.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>

/* Quantidade de ativos seguida de cinco linhas por ativo. */
int salvar_carteira(const Ativo carteira[], int total) {
    FILE *arquivo = fopen("data/carteira.txt", "w");
    if (arquivo == NULL) {
        printf("\nErro ao abrir data/carteira.txt para salvar.\n");
        return 0;
    }
    int sucesso = fprintf(arquivo, "%d\n", total) >= 0;
    for (int i = 0; i < total && sucesso; i++) {
        sucesso = fprintf(arquivo, "%s\n%s\n%d\n%.9g\n%.9g\n",
                          carteira[i].nome, carteira[i].categoria,
                          carteira[i].quantidade, carteira[i].precoCompra,
                          carteira[i].precoAtual) >= 0;
    }
    if (fclose(arquivo) != 0) sucesso = 0;
    if (!sucesso) printf("\nErro ao salvar a carteira.\n");
    return sucesso;
}

/* -1 indica erro: o programa deve parar para preservar os dados. */
int carregar_carteira(Ativo carteira[], int limite) {
    FILE *arquivo = fopen("data/carteira.txt", "r");
    if (arquivo == NULL) {
        if (errno == ENOENT) return 0; /* Primeira execucao: arquivo ainda nao existe. */
        printf("\nErro ao abrir data/carteira.txt para leitura.\n");
        return -1;
    }
    int total;
    int resultado = fscanf(arquivo, "%d", &total);
    if (resultado == EOF && !ferror(arquivo)) {
        fclose(arquivo);
        return 0; /* Arquivo vazio: comecar sem ativos. */
    }
    if (resultado != 1 || total < 0 || total > limite) {
        printf("\nQuantidade de ativos invalida no arquivo.\n");
        fclose(arquivo);
        return -1;
    }
    int caractere;
    while ((caractere = fgetc(arquivo)) != '\n' && caractere != EOF) {}
    for (int i = 0; i < total; i++) {
        Ativo ativo;
        if (fgets(ativo.nome, sizeof ativo.nome, arquivo) == NULL ||
            strchr(ativo.nome, '\n') == NULL ||
            fgets(ativo.categoria, sizeof ativo.categoria, arquivo) == NULL ||
            strchr(ativo.categoria, '\n') == NULL ||
            fscanf(arquivo, "%d %f %f", &ativo.quantidade,
                   &ativo.precoCompra, &ativo.precoAtual) != 3) {
            printf("\nRegistro invalido no arquivo.\n");
            fclose(arquivo);
            return -1;
        }
        ativo.nome[strcspn(ativo.nome, "\r\n")] = '\0';
        ativo.categoria[strcspn(ativo.categoria, "\r\n")] = '\0';
        carteira[i] = ativo;
        while ((caractere = fgetc(arquivo)) != '\n' && caractere != EOF) {}
    }
    fclose(arquivo);
    return total;
}

