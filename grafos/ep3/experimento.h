/**
 * MAC0328-2012 - Algoritmos em grafos - Tarefa 3: Descobrindo se um grafo é denso
 * Alunos: 
 *		Stefano Tommasini        - 7278080
 *		Pedro Paulo Vezzá Campos - 7538743
 * Sobre o arquivo: Neste arquivo estão declarados os protótipos e inclusões
 * relevantes à seção 1 do EP (O experimento).
 */

#ifndef _EXPERIMENTO_H
#define _EXPERIMENTO_H

#include<time.h>
#include<math.h>
#include<unistd.h>
#include"util.h"
#include"digrafo.h"

/**
 * Definições de macros para comparar os tempos medidos das duas representações
 * utilizando a função compara_representacoes().
 */
#define LISTA_MELHOR -1
#define TEMPOS_IGUAIS 0
#define MATRIZ_MELHOR 1

/**
 * Definição do epsilon a ser utilizado na função compara_representações.
 */
#define EPS 1e-5

/**
 * Definição da diferença de duas struct timespec transformada para double para 
 * comparação facilitada pelo programa.
 */
#define diff_timespec(f, i) (( f.tv_sec - i.tv_sec ) + (double)( f.tv_nsec - i.tv_nsec )/ (double) 1000000000L)

/**
 * Definição do resultado de um experimento. Contém os tempos
 * calculados para a execução das buscas em largura e profundidade
 * nas representações de matriz e lista de adjacência. Ainda armazena
 * a quantidade de arcos do digrafo aleatório gerado.
 */
typedef struct{
	double m_dfs, m_bfs, l_dfs, l_bfs;
	int arcos;
} resultado;

/**
 * Função que executa um experimento definido como:
 *  - Geração de um digrafo aleatório com probabilidade de
 * existência de um arco entre v e w dado por p
 *  - Tomada dos tempos da execução de 8 buscas em profundidade
 * no digrafo e 8 * V buscas em largura (8 para cada vértice inicial).
 * Onde cada uma das buscas é realizada tanto para a representação em
 * listas de adjacência quanto em matriz de adjacências.
 */
resultado Experimento(int V, double p);

/**
 * Função que compara duas respostas de um experimento e analisa qual forma
 * de representar o grafo é melhor (Menor tempo).
 *
 * A comparação é feita comparando se a soma dos tempos das buscas (BFS e DFS)
 * utilizando listas de adjacência com a soma dos tempos das buscas (BFS e DFS)
 * utilizando matriz de adjacência.
 * 
 * Algoritmo:
 * Se o |tempo_lista - tempo_matriz| < EPS então
 * 	retorne TEMPOS_IGUAIS
 * Senão se tempo_lista < tempo_matriz então
 * 	retorne LISTA_MELHOR
 * Senão
 * 	retorne MATRIZ_MELHOR
 * Fim se
 */
int comparar_representacoes (resultado r);
#endif

