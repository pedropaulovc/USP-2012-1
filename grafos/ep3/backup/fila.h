/**
 * MAC0328-2012 - Algoritmos em grafos - Tarefa 3: Descobrindo se um grafo é denso
 * Alunos: 
 *		Stefano Tommasini        - 7278080
 *		Pedro Paulo Vezzá Campos - 7538743
 * Sobre o arquivo: Neste arquivo estão declarados os protótipos e inclusões
 * relevantes à estrutura de dados fila. O código foi retirado das notas de aula.
 */

#include"item.h"

/**
 * A variável que armazena o endereço da fila de itens
 * alocada utilizando QUEUEinit().
 */
Item *q;
/**
 * Variáveis marcadoras do início e fim respectivamente
 * dos valores atualmente inseridos na fila.
 */
int inicio, fim;

/**
 * Função responsável por criar e inicializar uma fila
 * com capacidade cap.
 * Parâmetros:
 *	maxN: A capacidade da fila.
 */
void QUEUEinit(int maxN);

/**
 * Função responsável por retornar se a fila está vazia no
 * momento.
 */
int QUEUEempty();

/**
 * Função responsável por inserir o item x na fila caso
 * seja possível.
 * Parâmetros:
 *	x: O elemento a ser inserido.
 */
void QUEUEput(Item x);
/**
 * Função responsável por desenfileirar um elemento da fila
 * e retorná-lo. Não checa se há elemento para ser desenfileirado.
 */
Item QUEUEget();

/**
 * Função responsável desalocar a fila atual.
 */
void QUEUEfree();


