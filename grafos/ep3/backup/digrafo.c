/**
 * MAC0328-2012 - Algoritmos em grafos - Tarefa 3: Descobrindo se um grafo é denso
 * Alunos: 
 *		Stefano Tommasini        - 7278080
 *		Pedro Paulo Vezzá Campos - 7538743
 * Sobre o arquivo: Neste arquivo estão implementadas as funções declaradas em
 * digrafo.h. O código foi retirado das notas de aula.
 */

#include"digrafo.h"

void DIGRAPHdfsM (Digraph G) {
  Vertex v;
  cnt = 0;
  for (v = 0; v < G->V; v++)
    lbl[v] = -1;
  for (v= 0; v < G->V; v++)
    if (lbl[v] == -1)
      dfsRM(G, v);
}

void dfsRM (Digraph G, Vertex v) {
  Vertex w;
  lbl[v] = cnt++;
  for (w=0; w < G->V; w++)
    if (G->Adj[v][w])
      if (lbl[w] == -1)
        dfsRM(G, w);
}


void DIGRAPHdfsL (Digraph G) {
  Vertex v;
  cnt = 0;
  for (v=0; v < G->V; v++)
    lbl[v] = -1;
  for (v=0; v < G->V; v++)
    if (lbl[v] == -1)
      dfsRL(G, v);
}

void dfsRL (Digraph G, Vertex v) {
  link p;
  lbl[v] = cnt++;
  for (p = G->adj[v]; p != NULL; p= p->next)
    if (lbl[p->w] == -1)
      dfsRL(G, p->w);
}


void DIGRAPHbfsM (Digraph G, Vertex s) {
  Vertex v, w;
  cnt = 0;
  for (v = 0; v < G->V; v++)
    lbl[v] = -1;
  QUEUEinit(G->V);
  lbl[s] = cnt++;
  QUEUEput(s);
  while (!QUEUEempty()) {
    v = QUEUEget();
    for (w=0; w < G->V; w++)
      if (G->Adj[v][w] == 1 && lbl[w] == -1) {
        lbl[w] = cnt++;
        QUEUEput(w);
      }
  }
  QUEUEfree();
}


void DIGRAPHbfsL (Digraph G, Vertex s) {
  Vertex v;
  link p;
  cnt = 0;
  for (v = 0; v < G->V; v++)
    lbl[v] = -1;
  QUEUEinit(G->V);
  lbl[s] = cnt++;
  QUEUEput(s);
  while (!QUEUEempty()) {
    v = QUEUEget();
    for(p=G->adj[v];p!=NULL;p=p->next)
      if (lbl[p->w] == -1) {
        lbl[p->w] = cnt++;
        QUEUEput(p->w);
      }
  }
  QUEUEfree();
}

int **MATRIXint (int r, int c, int val) {
	Vertex i, j;
	int **m = malloc(r * sizeof(int *));
	for (i = 0; i < r; i++)
		m[i] = malloc(c * sizeof(int));
	for (i = 0; i < r; i++)
	for (j = 0; j < c; j++)
		m[i][j] = val;
	return m;
}

Digraph DIGRAPHinit (int V){
	Vertex v;
	Digraph G = malloc(sizeof *G);
	G–>V = V;
	G–>A = 0;
	G–>Adj = MATRIXint(V,V,0);
	
	G–>adj = malloc(V * sizeof(link));
	for (v = 0; v < V; v++)
		G–>adj[v] = NULL;
	
	return G;
}

link NEW (Vertex w, link next) {
	link p = malloc(sizeof *p);
	p–>w = w;
	p–>next = next;
	return p;
}

void DIGRAPHinsertA (Digraph G,Vertex v,Vertex w) {
	G->Adj[v][w] = 1;
	G–>adj[v] = NEW(w,G–>adj[v]);
	G–>A++;
}


