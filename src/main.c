#include <stdio.h>
#include "funcoes.h"
#include "modulo.h"

int main(void) {
    Ativo carteira[100];
    int total = carregar_carteira(carteira, 100);
    if (total < 0) return 1;

    int continuar = 1;
    while (continuar) {
        int opcao;
        show_menu();
        printf("\nEscolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) break;
        getchar();

        switch (opcao) {
            case 1:
                if (total < 100) {
                    if (cadastrar(carteira, total)) {
                        total++;
                        salvar_carteira(carteira, total);
                    }
                } else {
                    printf("\nLimite de cadastros atingido.\n");
                }
                break;
            case 2:
                listar(carteira, total);
                break;
            case 3:
                printf("\nValor total atual: R$ %.2f\n", valor_total(carteira, total));
                break;
            case 4:
                calcular_rentabilidade_total(carteira, total);
                break;
            case 5:
                ordenar_rentabilidade(carteira, total);
                salvar_carteira(carteira, total);
                printf("\nCarteira ordenada do melhor para o pior desempenho.\n");
                listar(carteira, total);
                break;
            case 6:
                simulador_educativo(carteira, total);
                break;
            case 7:
                relatorio_final(carteira, total);
                salvar_carteira(carteira, total);
                break;
            case 8:
                printf("\nFaixas do exercicio; nao medem o risco real do ativo.\n");
                risco(carteira, total);
                break;
            case 0:
                if (salvar_carteira(carteira, total)) continuar = 0;
                break;
            default:
                printf("\nOpcao invalida.\n");
        }
    }
    return 0;
}
