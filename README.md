# Carteira de Investimentos - CP3

Projeto em C com vetor de structs, funcoes, arquivo de texto, bubble sort
e simulador educativo. Limite: 100 ativos.

## Compilar e executar

Abra o PowerShell na pasta principal do projeto:

gcc -Wall -Wextra -Iinclude src/main.c src/funcoes.c src/modulo.c -o programa

.\programa.exe

Execute sempre na pasta principal para encontrar data/carteira.txt.

## Organizacao

- src/main.c: menu e chamadas das funcoes.
- src/funcoes.c: cadastro, listagem, calculos, ordenacao, simulador e relatorio.
- src/modulo.c: salvar e carregar a carteira.
- include/funcoes.h: struct Ativo e declaracoes das funcoes.
- include/modulo.h: declaracoes da persistencia.
- data/carteira.txt: carteira usada pelo programa.
- data/carteira_exemplo.txt: tres ativos ficticios para demonstracao.

## Menu

1. Cadastrar ativo.
2. Listar ativos.
3. Valor total atual da carteira.
4. Rentabilidade geral e lucro/prejuizo total.
5. Ordenar por rentabilidade, do maior para o menor, e salvar a ordem.
6. Simulador educativo de 12 meses.
7. Relatorio final na tela, com ativos ordenados, totais e impacto social.
8. Classificacao de risco do exercicio anterior.
0. Salvar e sair.

## Como os calculos funcionam

Valor atual da carteira = soma de precoAtual * quantidade.
Total investido = soma de precoCompra * quantidade.
Lucro/prejuizo = valor atual - total investido.
Rentabilidade geral = lucro / total investido * 100.
A rentabilidade geral nao e a soma nem a media simples dos percentuais.
Se o total investido for zero, a rentabilidade geral e indefinida.

A ordenacao usa bubble sort: compara dois ativos vizinhos e troca a struct
inteira quando o segundo tem rentabilidade maior. Ativos com preco de compra
zero ou negativo ficam no final, sem calcular sua rentabilidade.

A classificacao de risco foi mantida por fazer parte dos CPs anteriores:
menos de 5% = alto; de 5% a 15% = medio; acima de 15% = baixo.
Essas faixas sao uma regra do exercicio, nao uma medida de risco financeiro real.

## Simulador

Usa o valor atual total da carteira como aplicacao inicial em cada alternativa.
As taxas mensais ilustrativas estao em #define no arquivo src/funcoes.c:

- Poupanca: 0,50%.
- Tesouro Selic: 0,80%.
- CDB: 0,90%.

Um for de 12 repeticoes aplica valor *= 1 + taxa.
Os resultados sao brutos, com taxas constantes, sem impostos ou tarifas.
Nao representam taxas de mercado nem promessa de rendimento.
O programa explica rentabilidade, juros compostos, risco e liquidez.

## Persistencia

O programa carrega a carteira ao iniciar e salva apos cada cadastro,
ordenacao, relatorio e ao escolher Sair.
Usa fopen, fprintf, fscanf e fclose, verificando NULL ao abrir.
Arquivo vazio ou inexistente inicia uma carteira vazia. O arquivo e criado ao salvar.
Outros erros de leitura encerram o programa para preservar dados invalidos.

O arquivo comeca com o numero de ativos. Cada ativo ocupa cinco linhas:
nome, categoria, quantidade, preco de compra e preco atual.
Para comecar vazio, deixe data/carteira.txt vazio, com apenas 0, ou remova o arquivo.

Para usar os exemplos, com o programa fechado, faca uma copia de seguranca
da sua carteira e copie o conteudo de data/carteira_exemplo.txt para
data/carteira.txt. O exemplo tem valor atual R$ 3200,00, investimento
R$ 3000,00, lucro R$ 200,00 e rentabilidade geral de 6,67%.
A ordem esperada e Crescimento (30%), Estavel (10%), Queda (-20%).

## Impacto social - ODS 8.10

O simulador apresenta conceitos financeiros em linguagem simples, permitindo
comparar alternativas de investimento sem aplicar dinheiro real. Isso contribui
para a educacao e a inclusao financeira, ajudando pessoas a entender rendimento,
risco e liquidez e apoiando o objetivo da ODS 8.10 de ampliar o acesso a servicos
financeiros. A simulacao e educativa e nao substitui a avaliacao de cada produto.

## Video de demonstracao (2 a 3 minutos, sem narracao)

Link do video: PENDENTE - inserir o link nao listado do YouTube ou do Drive.

Roteiro sugerido para gravar a tela:
- 0:00 a 0:25: mostrar estrutura, compilar e abrir o programa.
- 0:25 a 0:55: cadastrar um ativo e listar a carteira.
- 0:55 a 1:15: mostrar valor total e rentabilidade geral.
- 1:15 a 1:40: ordenar a carteira e mostrar a ordem.
- 1:40 a 2:10: mostrar simulador e explicacoes.
- 2:10 a 2:35: mostrar relatorio final e impacto social.
- 2:35 a 2:55: sair, reabrir e listar para demonstrar a persistencia.

Grave sem narracao. Publique e substitua o campo PENDENTE acima.
Nao inclua o arquivo de video no ZIP.

## Entrega e apresentacao

Compactar codigo-fonte, include, data e README.md e enviar pelo grupo
do Blackboard. Apresentacao presencial: Aula 12 (04/11), conforme o enunciado.
O relatorio final do sistema e exibido na opcao 7.

