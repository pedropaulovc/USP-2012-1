/**
 * MAC0328-2012 - Algoritmos em grafos - Tarefa 3: Descobrindo se um grafo é denso
 * Alunos: 
 *		Stefano Tommasini        - 7278080
 *		Pedro Paulo Vezzá Campos - 7538743
 * Sobre o arquivo: Aqui estão declarados defines úteis durante a implementação
 * do EP.
 */

#ifndef _UTIL_H
#define _UTIL_H
#include<limits.h>

/**
 * Definição de valores booleanos.
 */
#define TRUE 1
#define FALSE 0

/**
 * Versão resumida de um laço for que executará (y - x) vezes.
 * Parâmetros:
 * 	i: Nome da variável de iteração já previamente declarada.
 * 	x: Valor inicial da variável de iteração.
 *	y: Valor limite da variável de iteração.
 */
#define f(i,x,y)  for(i = x; i<y; i++)

/**
 * Define responsável por retornar o quadrado de um número.
 * Parâmetros:
 * 	x: O valor a ser elevado ao quadrado.
 */
#define quad(x) (x) * (x)

/**
 * Define responsável por inicializar uma variável x de tamanho
 * sizeof(x) com o valor y.
 * Parâmetros:
 * 	x: A variável a ser inicializada
 *	y: O valor inicial utilizado. Normalmente 0.
 */
#define clr(x, y) memset(x, y, sizeof x)

/**
 * Definição de números de dupla precisão (64 bits) caso estejam
 * disponíveis na compilação.
 */
#ifdef LLONG_MAX
typedef long long ll;
#else
typedef long ll;
#endif

#endif

