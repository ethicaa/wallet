#include "funcoes.h"
#include <stdio.h>
#include <string.h>



void show_menu(void) {
    printf("\n=== CARTEIRA DE INVESTIMENTOS ===\n");
    printf("1. Cadastrar ativo\n");
    printf("2. Listar ativos\n");
    printf("3. Valor total da carteira\n");
    printf("4. Rentabilidade geral\n");
    printf("5. Ordenar por rentabilidade\n");
    printf("6. Simulador educativo\n");
    printf("7. Relatorio final\n");
    printf("8. Classificar risco (regra do exercicio)\n");
    printf("0. Sair\n");
}

int cadastrar(Ativo carteira[], int pos){
    printf("Nome do ativo: ");
    fgets(carteira[pos].nome, sizeof(carteira[pos].nome), stdin);
    carteira[pos].nome[strcspn(carteira[pos].nome, "\n")] = '\0';
    printf("Categoria: ");
    fgets(carteira[pos].categoria,sizeof(carteira[pos].categoria),stdin);
    carteira[pos].categoria[strcspn(carteira[pos].categoria, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &carteira[pos].quantidade);
    printf("Preco de Compra: ");
    scanf("%f", &carteira[pos].precoCompra);
    printf("Preco Atual: ");
    scanf("%f", &carteira[pos].precoAtual);
    printf("------------------------------\n");
    getchar();

    return 1;
}
void listar(Ativo carteira[], int pos){

    for(int i = 0; i < pos; i++){
        carteira[i].nome[strcspn(carteira[i].nome, "\n")] = '\0';
        carteira[i].categoria[strcspn(carteira[i].categoria, "\n")] = '\0';
        printf("\n------------------------------\nNAME: %s\n", carteira[i].nome);
        printf("CTG: %s\n", carteira[i].categoria);
        printf("QTD: %d\n", carteira[i].quantidade);
        printf("PCOMPRA: %.2f\n", carteira[i].precoCompra);
        printf("PATUAL: %.2f\n------------------------------\n", carteira[i].precoAtual); 
    }
}


float calcular_rentabilidade_total(Ativo carteira[], int total) {
    float totalInvestido = 0;
    float totalAtual = 0;

    for (int i = 0; i < total; i++) {
        totalInvestido += carteira[i].precoCompra * carteira[i].quantidade;
        totalAtual += carteira[i].precoAtual * carteira[i].quantidade;
        
    }

    if (totalInvestido == 0) {
        printf("\nRentabilidade geral indefinida: total investido zero.\n");
        printf("Lucro ou prejuizo total: R$ %.2f\n", totalAtual - totalInvestido);
        return 0;
    }

    float lucro = totalAtual - totalInvestido;
    float rentabilidade = lucro / totalInvestido * 100;
    printf("\nRentabilidade total: %.2f%%\n", rentabilidade);
    printf("Lucro ou prejuizo total: R$ %.2f\n\n", lucro);

    return rentabilidade;
}

int risco(Ativo carteira[],int pos){

    for(int i = 0; i < pos; i ++){   
        if (carteira[i].precoCompra == 0){
            printf("O preco de compra da acao %s e 0.\n\n", carteira[i].nome);
            continue;
        }
        
        float rentabilidade =(carteira[i].precoAtual - carteira[i].precoCompra)/ carteira[i].precoCompra * 100;

        if (rentabilidade < 5) {
            printf("\nO investimento da acao %s e de Alto risco.\n\n", carteira[i].nome);
        } else if (rentabilidade <= 15) {
            printf("\nO investimento da acao %s e de Medio risco.\n\n", carteira[i].nome);
        } else {
            printf("\nO investimento da acao %s e de Baixo risco.\n\n", carteira[i].nome);
        }
    }
    return 0;
}



#define TAXA_POUPANCA 0.005
#define TAXA_TESOURO 0.008
#define TAXA_CDB 0.009

float valor_total(Ativo carteira[], int total) {
    float valor = 0;
    for (int i = 0; i < total; i++) {
        valor += carteira[i].precoAtual * carteira[i].quantidade;
    }
    return valor;
}

float rentabilidade_ativo(Ativo ativo) {
    return (ativo.precoAtual - ativo.precoCompra) / ativo.precoCompra * 100;
}


void ordenar_rentabilidade(Ativo carteira[], int total) {
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - 1 - i; j++) {
            int trocar = 0;
            if (carteira[j].precoCompra <= 0 &&
                carteira[j + 1].precoCompra > 0) {
                trocar = 1;
            } else if (carteira[j].precoCompra > 0 &&
                       carteira[j + 1].precoCompra > 0 &&
                       rentabilidade_ativo(carteira[j]) <
                       rentabilidade_ativo(carteira[j + 1])) {
                trocar = 1;
            }
            if (trocar) {
                Ativo temporario = carteira[j];
                carteira[j] = carteira[j + 1];
                carteira[j + 1] = temporario;
            }
        }
    }
}

void simulador_educativo(Ativo carteira[], int total) {
    double inicial = valor_total(carteira, total);
    if (inicial <= 0) {
        printf("\nA carteira precisa ter valor positivo para simular.\n");
        return;
    }

    double poupanca = inicial;
    double tesouro = inicial;
    double cdb = inicial;

    for (int mes = 0; mes < 12; mes++) {
        poupanca *= 1 + TAXA_POUPANCA;
        tesouro *= 1 + TAXA_TESOURO;
        cdb *= 1 + TAXA_CDB;
    }

    printf("\n=== SIMULADOR EDUCATIVO ===\n");
    printf("Aplicacao inicial: R$ %.2f por 12 meses\n", inicial);
    printf("POUPANCA (%.2f%%/mes): R$ %.2f (ganho: R$ %.2f)\n",
           TAXA_POUPANCA * 100, poupanca, poupanca - inicial);
    printf("TESOURO SELIC (%.2f%%/mes): R$ %.2f (ganho: R$ %.2f)\n",
           TAXA_TESOURO * 100, tesouro, tesouro - inicial);
    printf("CDB (%.2f%%/mes): R$ %.2f (ganho: R$ %.2f)\n",
           TAXA_CDB * 100, cdb, cdb - inicial);
    printf("\nTaxas ilustrativas e constantes, sem impostos ou tarifas.\n");
    printf("Os resultados nao sao uma promessa de rendimento.\n");
    printf("Rentabilidade e quanto o dinheiro cresce ou diminui.\n");
    printf("Juros compostos: o rendimento passa a render tambem.\n");
    printf("Risco e a possibilidade de perder dinheiro ou nao recebe-lo no prazo.\n");
    printf("Poupanca: opcao conhecida; neste exemplo tem o menor rendimento.\n");
    printf("Tesouro Selic: titulo publico; pode variar de preco antes do vencimento.\n");
    printf("CDB: emprestimo ao banco; depende do emissor e das condicoes do produto.\n");
    printf("Liquidez e a facilidade de retirar o dinheiro; confira o prazo de resgate.\n");
    printf("Maior rendimento, sozinho, nao significa menor risco.\n");
}

void relatorio_final(Ativo carteira[], int total) {
    ordenar_rentabilidade(carteira, total);
    printf("\n=== RELATORIO FINAL ===\n");
    printf("Ativos do melhor para o pior desempenho:\n");
    if (total == 0) printf("Carteira vazia.\n");

    for (int i = 0; i < total; i++) {
        printf("\n%d. %s | Categoria: %s | Quantidade: %d\n",
               i + 1, carteira[i].nome, carteira[i].categoria,
               carteira[i].quantidade);
        printf("Compra: R$ %.2f | Atual: R$ %.2f | Valor: R$ %.2f\n",
               carteira[i].precoCompra, carteira[i].precoAtual,
               carteira[i].precoAtual * carteira[i].quantidade);
        if (carteira[i].precoCompra > 0) {
            printf("Rentabilidade: %.2f%%\n", rentabilidade_ativo(carteira[i]));
        } else {
            printf("Rentabilidade indefinida: preco de compra invalido.\n");
        }
    }

    printf("\nValor total atual: R$ %.2f\n", valor_total(carteira, total));
    calcular_rentabilidade_total(carteira, total);
    printf("\nImpacto social - ODS 8.10:\n");
    printf("O simulador ajuda a compreender juros, risco e liquidez em linguagem\n");
    printf("simples. Comparar alternativas acessiveis contribui para a educacao\n");
    printf("e a inclusao financeira, apoiando decisoes mais conscientes e o\n");
    printf("objetivo de ampliar o acesso a servicos financeiros da ODS 8.10.\n");
}

