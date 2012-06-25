/**
 * MAC0328-2012 - Algoritmos em grafos - Tarefa 3: Descobrindo se um grafo é denso
 * Alunos: 
 *		Stefano Tommasini        - 7278080
 *		Pedro Paulo Vezzá Campos - 7538743
 * Sobre o arquivo: Neste arquivo estão declarados os protótipos e inclusões
 * relevantes a um digrafo. O código foi retirado das notas de aula.
 */

#include<stdlib.h>
#include"fila.h"
#include"vertex.h"

/**
 * Definição da capacidade máxima de um digrafo.
 */
#define maxV 1024

/**
 * Variáveis globais utilizadas pelos algoritmos de busca implementados
 * nas notas de aula.
 */
static int cnt, lbl[maxV];

/**
 * Definição de nó de uma lista de adjacencia
 */
typedef struct node *link;
struct node {
  Vertex w;
  link next;
};

/**
 * Definição de um digrafo incluindo tanto matriz quanto lista de adjacência.
 */
struct digraph {
  int V;
  int A;
  int **Adj;
  link *adj;
};
typedef struct digraph *Digraph;

/**
 * Função responsável por inicializar um digrafo contendo V vértices
 * inicialmente.
 * Parâmetros:
 * 	V: A quantidade de vértices do digrafo.
 */
Digraph DIGRAPHinit (int V);
/**
 * Função responsável pela inserção de um arco (dirigido) do vértice v
 * ao vértice w no digrafo G.
 * Parâmetros:
 * 	G: O digrafo a ter o arco inserido.
 * 	v: O vértice de origem
 * 	w: O vértice de destino
 */
void DIGRAPHinsertA (Digraph G,Vertex v,Vertex w);
/**
 * Função responsável pela alocação dinâmica de uma matriz de inteiros
 * contendo r linhas, c colunas e inicializada com o valor val.
 * Parâmetros:
 * 	r: O número de linhas da matriz
 * 	c: O número de colunas da matriz
 * 	val: O valor de inicialização da matriz
 */
int **MATRIXint (int r, int c, int val);
/**
 * Função de alocação de um novo nó da lista de ajacência tendo como 
 * vértice destino o parâmetro w e como próximo elemento na lista
 * de adjacência o nó next.
 * Parâmetros:
 * 	w: O vértice de destino da aresta
 * 	c: O próximo nó na lista de adjacência
 */
link NEW (Vertex w, link next);

/**
 * Função de busca em profundidade na matriz de adjacencia do
 * digrafo G.
 * Parâmetros:
 * 	G: O digrafo a ser percorrido
 */
void DIGRAPHdfsM (Digraph G);
/**
 * Função da parte recursiva da busca em profundidade na matriz de
 * adjacencia do digrafo G.
 * Parâmetros:
 * 	G: O digrafo a ser percorrido
 * 	v: O vértice atual na busca em profundidade
 */
void dfsRM (Digraph G, Vertex v);

/**
 * Função de busca em profundidade na lista de adjacencia do
 * digrafo G.
 * Parâmetros:
 * 	G: O digrafo a ser percorrido
 */
void DIGRAPHdfsL (Digraph G);
/**
 * Função da parte recursiva da busca em profundidade na lista de
 * adjacencia do digrafo G.
 * Parâmetros:
 * 	G: O digrafo a ser percorrido
 * 	v: O vértice atual na busca em profundidade
 */
void dfsRL (Digraph G, Vertex v);

/**
 * Função de busca em largura na matriz de adjacencia do
 * digrafo G.
 * Parâmetros:
 * 	G: O digrafo a ser percorrido
 * 	s: O vértice de início da busca em largura.
 */
void DIGRAPHbfsM (Digraph G, Vertex s);
/**
 * Função de busca em largura na lista de adjacencia do
 * digrafo G.
 * Parâmetros:
 * 	G: O digrafo a ser percorrido
 * 	s: O vértice de início da busca em largura.
 */
void DIGRAPHbfsL (Digraph G, Vertex s);
