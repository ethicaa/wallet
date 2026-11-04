#ifndef FUNCOES_H
#define FUNCOES_H

typedef struct {
    char nome[100];
    char categoria[200];
    int quantidade;
    float precoCompra;
    float precoAtual;
}Ativo ;

void show_menu(void);
int cadastrar(Ativo carteira[], int pos);
float calcular_rentabilidade_total(Ativo carteira[], int total);
void listar(Ativo carteira[], int pos);
int risco(Ativo carteira[], int pos);



float valor_total(Ativo carteira[], int total);

float rentabilidade_ativo(Ativo ativo);
void ordenar_rentabilidade(Ativo carteira[], int total);
void simulador_educativo(Ativo carteira[], int total);
void relatorio_final(Ativo carteira[], int total);

#endif
