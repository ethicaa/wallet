# Wallet — Carteira de Investimentos · CP3

Sistema em C para gerenciar uma carteira de até 100 ativos. Integra menu, vetor de structs, persistência em arquivo de texto, ordenação com bubble sort e simulador educativo.

## Compilar e executar

Abra o PowerShell na pasta principal do projeto e compile:

~~~powershell
gcc -Wall -Wextra -Iinclude src/main.c src/funcoes.c src/modulo.c -o programa
~~~

Depois, execute:

~~~powershell
.\programa.exe
~~~

Execute sempre na pasta principal, pois o caminho data/carteira.txt é relativo à pasta de execução. A pasta data precisa existir.

## Organização

~~~text
wallet/
├── src/
│   ├── main.c
│   ├── funcoes.c
│   └── modulo.c
├── include/
│   ├── funcoes.h
│   └── modulo.h
├── data/
│   ├── carteira.txt
│   └── carteira_exemplo.txt
└── README.md
~~~

- **main.c:** menu e chamadas das funções.
- **funcoes.c:** cadastro, listagem, cálculos, ordenação, simulador e relatório.
- **modulo.c:** leitura e salvamento da carteira.
- **funcoes.h:** estrutura Ativo e declarações das funções.
- **modulo.h:** declarações das funções de persistência.
- **carteira.txt:** carteira utilizada pelo programa.
- **carteira_exemplo.txt:** três ativos fictícios para demonstração.

## Menu

| Opção | Funcionalidade |
|---|---|
| 1 | Cadastrar ativo |
| 2 | Listar ativos |
| 3 | Exibir o valor total atual da carteira |
| 4 | Calcular a rentabilidade geral e o lucro ou prejuízo total |
| 5 | Ordenar por rentabilidade, do maior para o menor, e salvar a ordem |
| 6 | Executar o simulador educativo de 12 meses |
| 7 | Exibir o relatório final com ativos ordenados, totais e impacto social |
| 8 | Classificar o risco conforme as faixas do exercício anterior |
| 0 | Salvar e sair |

Ao cadastrar, digite os preços com ponto decimal, por exemplo: 32.50.

## Cálculos e ordenação

~~~text
Valor atual = soma de (precoAtual × quantidade)
Total investido = soma de (precoCompra × quantidade)
Lucro ou prejuízo = valor atual − total investido
Rentabilidade geral (%) = lucro ou prejuízo ÷ total investido × 100
~~~

A rentabilidade geral considera o total investido: ela não é a soma nem a média simples das rentabilidades individuais. Quando o total investido é zero, a rentabilidade geral é indefinida.

A ordenação usa bubble sort: compara ativos vizinhos e troca a struct inteira quando o segundo tem rentabilidade maior. Ativos com preço de compra zero ou negativo ficam no final, sem calcular sua rentabilidade na ordenação e no relatório.

A classificação de risco foi mantida dos CPs anteriores:

- Menos de 5%: alto risco.
- De 5% até 15%: médio risco.
- Acima de 15%: baixo risco.

Essas faixas são uma regra do exercício e não representam uma avaliação real do risco financeiro de cada ativo.

## Simulador educativo

O simulador utiliza o valor atual total da carteira como aplicação inicial em cada alternativa. As taxas mensais ilustrativas são definidas com #define em src/funcoes.c:

| Alternativa | Taxa mensal ilustrativa |
|---|---:|
| Poupança | 0,50% |
| Tesouro Selic | 0,80% |
| CDB | 0,90% |

Um laço de 12 repetições aplica juros compostos:

~~~c
valor *= 1 + taxa;
~~~

Os resultados são brutos, com taxas constantes, sem impostos ou tarifas. As taxas não representam condições atuais do mercado nem promessa de rendimento. O programa explica rentabilidade, juros compostos, risco e liquidez em linguagem simples.

## Persistência

O programa carrega a carteira ao iniciar e salva após cada cadastro, ordenação, relatório e ao escolher Sair.

A persistência usa fopen, fprintf, fscanf e fclose, verificando NULL ao abrir o arquivo. Arquivo vazio ou inexistente inicia uma carteira vazia; o arquivo é criado ao salvar. Outros erros de leitura encerram o programa para evitar sobrescrever dados inválidos.

A primeira linha do arquivo contém a quantidade de ativos. Cada ativo ocupa cinco linhas, nesta ordem:

1. Nome.
2. Categoria.
3. Quantidade.
4. Preço de compra.
5. Preço atual.

Para começar do zero, com o programa fechado, faça uma cópia de segurança dos dados que deseja manter e deixe data/carteira.txt vazio, com apenas 0, ou remova o arquivo. Mantenha a pasta data.

## Arquivo de exemplo

Com o programa fechado, faça uma cópia de segurança da sua carteira e copie o conteúdo de data/carteira_exemplo.txt para data/carteira.txt.

Resultados esperados do exemplo:

| Indicador | Resultado |
|---|---:|
| Total investido | R$ 3.000,00 |
| Valor atual | R$ 3.200,00 |
| Lucro total | R$ 200,00 |
| Rentabilidade geral | 6,67% |

Ordem esperada: Ativo Crescimento (30%), Ativo Estavel (10%) e Ativo Queda (-20%). Esses nomes e valores são fictícios.

## Impacto social — ODS 8.10

O simulador apresenta conceitos financeiros em linguagem simples, permitindo comparar alternativas de investimento sem aplicar dinheiro real. Isso contribui para a educação e a inclusão financeira, ajudando as pessoas a compreender rendimento, risco e liquidez e apoiando o objetivo da ODS 8.10 de ampliar o acesso a serviços financeiros. A simulação é educativa e não substitui a avaliação das condições de cada produto.

## Vídeo de demonstração

[Assistir à demonstração do Wallet](https://youtu.be/7_HwJzzI6Ow)

## Código-fonte

[Repositório do projeto no GitHub](https://github.com/ethicaa/wallet)

