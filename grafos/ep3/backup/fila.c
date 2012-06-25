/**
 * MAC0328-2012 - Algoritmos em grafos - Tarefa 3: Descobrindo se um grafo é denso
 * Alunos: 
 *		Stefano Tommasini        - 7278080
 *		Pedro Paulo Vezzá Campos - 7538743
 * Sobre o arquivo: Neste arquivo estão implementadas as funções relevantes à
 * estrutura de dados fila. O código foi retirado das notas de aula.
 */

#include "item.h"
#include "fila.h"

void QUEUEinit(int maxN) {
  q = (Item*) malloc(maxN*sizeof(Item));
  inicio = 0;
  fim = 0;
}

int QUEUEempty() {
  return inicio == fim;
}

void QUEUEput(Item item){
  q[fim++] = item;
}

Item QUEUEget() {
  return q[inicio++];
}

void QUEUEfree() {
  free(q);
}

