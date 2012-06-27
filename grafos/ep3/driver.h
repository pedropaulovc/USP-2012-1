/**
 * MAC0328-2012 - Algoritmos em grafos - Tarefa 3: Descobrindo se um grafo é denso
 * Alunos: 
 *		Stefano Tommasini        - 7278080
 *		Pedro Paulo Vezzá Campos - 7538743
 * Sobre o arquivo: Neste arquivo estão declarados os protótipos e inclusões
 * relevantes ao driver definido na seção 2 do EP (O teste).
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include"util.h"
#include"digrafo.h"
#include"experimento.h"

#ifndef _DRIVER_H
#define _DRIVER_H

/**
 * Definição do número máximo de tentativas que a busca binária implementada
 * em buscar_alfa() será executada. Garante que o algoritmo não entrará em loop
 * devido a instabilidades decorrentes da natureza aleatória da geração dos 
 * grafos em cada experimento.
 */
#define MAX_TENTATIVAS 20

/**
 * Definição da quantidade de repetições que um dado experimento será realizado.
 */
#define REPETICOES_EXPERIMENTO 30

/**
 * Função principal do driver, responsável pelo interfaceamento com o usuário.
 * Lê os dados da entrada padrão e delega a tarefa de executar os testes com
 * a função buscar_alfa().
 *
 * Aceita comandos no formato 'opcode [parâmetros]' lidos da entrada padrão.
 * Todos visam localizar através de busca binária o valor de p que demarca o
 * limiar entre um digrafo esparso (Listas de adjacências mais rápidas) e um
 * digrafo denso (Matrizes de adjacências mais rápidas). As diferenças estão na
 * classe de p utilizada e na exibição ou não dos resultados intermediários.
 * 
 * - Classe p = \alpha
 *   - 'a V': Busca p para um grafo de V vértices aleatórios, exibe parciais.
 *   - 'A V': Idem anterior, não exibe parciais.
 *   - 'b': Roda uma bateria de testes para determinar o valor de p para digrafos
 * contendo 10, 20, 50, 80, 100, 150, 250 e 500 vértices, exibe parciais.
 *   - 'B': Idem anterior, não exibe parciais.
 *
 * - Classe p = \alpha/lg(V)
 *   - 'l V': Busca p para um grafo de V vértices aleatórios, exibe parciais.
 *   - 'L V': Idem anterior, não exibe parciais.
 *   - 'm': Roda uma bateria de testes para determinar o valor de p para digrafos
 * contendo 10, 20, 50, 80, 100, 150, 250 e 500 vértices, exibe parciais.
 *   - 'M': Idem anterior, não exibe parciais.
 * - 'e V p' para rodar um experimento com V vértices e probabilidade p.
 * - 'f' para encerrar o programa 
 * - 'h' para exibir a ajuda
 */
void driver ();
/**
 * Função responsável por dados V e p executar REPETICOES_EXPERIMENTO
 * experimentos e totalizar os tempos obtidos, retornando essa soma.
 */
resultado rodar_teste (int V, double p);
/**
 * Função responsável por exibir na saída padrão um cabeçalho csv indicando
 * quais dados estão representados em cada coluna.
 */
void imprimir_cabecalho();
/**
 * Função responsável por exibir na saída padrão uma linha csv indicando 
 * o resultado de um dado experimento.
 * Parâmetros:
 *	- V: O número de vértices do digrafo gerado.
 *	- alfa: O valor de \alpha utilizado no experimento
 *	- r: O resultado contendo a leitura dos tempos para cada forma de
 * representação.
 */
void imprimir_resultado(int V, double alfa, resultado r);

/**
 * Função responsável por imprimir na saída padrão os comandos disponíveis
 * ao usuário.
 */
void imprimir_ajuda();

/**
 * Implementação da busca binária para localizar o valor de \alpha que marca
 * o limiar entre um digrafo esparso e um digrafo denso. Executa até 
 * MAX_TENTATIVAS iterações da busca binária ou menos caso o análise do
 * resultado obtido informe que os tempos são iguais.
 * Parâmetros:
 *	- V: Quantidade de vértices do digrafo
 *	- den: Valor do denominador de p. Normalmente 1.0 ou lg(V).
 *	- parcial: Flag com valor TRUE para exibir os resultados parciais ou 
 * FALSE para exibir apenas o resultado final.
 */
void buscar_alfa(int V, double den, int parcial);
#endif

