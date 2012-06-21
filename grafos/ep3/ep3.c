#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define pb push_back
#define f(i,x,y)  for(i = x; i<y; i++ )
#define FORV(it,A) for(vector<int>::iterator it = A.begin(); it!= A.end(); it++)
#define FORS(it,A) for(set<int>::iterator it = A.begin(); it!= A.end(); it++)
#define quad(x) (x) * (x)
#define mp make_pair
#define clr(x, y) memset(x, y, sizeof x)
#define fst first
#define snd second
typedef long long ll;
typedef long double ld;

#define maxV 1024
#define Vertex int

int VV[] = {30, 40, 50, 60};

/*nó de uma lista de adjacencia*/
typedef struct node *link;
struct node {
  Vertex w;
  link next;
};

/*definição de digrafo inclui matriz e lista de adjacencia*/
struct digraph {
  int V;
  int A;
  int **Adj;
  link *adj;
};
typedef struct digraph *Digraph;

void DIGRAPHdfsM (Digraph G);
void dfsRM (Digraph G, Vertex v);

void DIGRAPHdfsL (Digraph G);
void dfsRL (Digraph G, Vertex v);

static int cnt, lbl[maxV];

/*busca em profundidade em matriz de adjacencia*/
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

/*busca em profundidade em lista de adjacencia*/
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


/* Item.h */
typedef Vertex Item;

/* QUEUE.h */
void QUEUEinit(int);
int QUEUEempty();
void QUEUEput(Item);
Item QUEUEget();
void QUEUEfree();

Item *q;
int inicio, fim;
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

/*busca em largura em matriz de adjacencia*/
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

/*busca em largura em lista de adjacencia*/
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

Digraph DIGRAPHInit (int n){
	int i, j;
	Digraph G = malloc (sizeof (struct digraph));
	G->V = n;
	G->A = 0;
	G->Adj = (int**) malloc(n * sizeof(int*));
	f(i, 0, n)
		G->Adj[i] = (int *) malloc(n * sizeof(int));
	f (i, 0, n) f (j, 0, n) G->Adj[i][j] = 0;
	G->adj = (link*) malloc(n * sizeof(link));
	f (i, 0, n) G->adj[i] = NULL;
	return G;
}

void Digraph_insere (Digraph G, int a, int b){
	G->Adj[a][b] = 1;
	link p = malloc (sizeof ( struct node));
	p->w = b; p->next = G->adj[a];
	G->adj[a] = p;
	G->A++;
}

struct no{
	double m_dfs, m_bfs, l_dfs, l_bfs;
	int arcos;
};

struct no Experimento(int V, double p) {
	int conta_arcos = 0, i, j;
	long long M_dfs_ini, M_dfs_fim, M_bfs_ini, M_bfs_fim;
	long long L_dfs_ini, L_dfs_fim, L_bfs_ini, L_bfs_fim;
	struct no ans;
	/*link pp;*/
	Digraph G = DIGRAPHInit(V);
	f (i, 0, V) f (j, 0, V) if (i != j){
		if (rand() <  p*RAND_MAX){
			conta_arcos++;
			Digraph_insere (G, i, j);
		}
	}
	/*
	f (i, 0, V){
		printf("Vertice %d: ", i);
		for (pp = G->adj[i]; pp != NULL; pp = pp->next){
			printf("%d ", pp->w);
		}
		printf("\n");
	}
	f (i, 0, V){
		f (j, 0, V) printf("%d ", G->Adj[i][j]); printf("\n");
	}*/
	
	M_dfs_ini = clock();
	f (i, 0, 8) DIGRAPHdfsM (G);
	M_dfs_fim = clock();
	ans.m_dfs = (double)(M_dfs_fim-M_dfs_ini)/CLOCKS_PER_SEC; 
	L_dfs_ini = clock();
	f (i, 0, 8) DIGRAPHdfsL (G);
	L_dfs_fim = clock();
	ans.l_dfs = (double)(L_dfs_fim-L_dfs_ini)/CLOCKS_PER_SEC;
	M_bfs_ini = clock();
	f (i, 0, 8*V) DIGRAPHbfsM(G, 0);
	M_bfs_fim = clock();
	ans.m_bfs = (double)(M_bfs_fim-M_bfs_ini)/CLOCKS_PER_SEC;
	L_bfs_ini = clock();
	f (i, 0, 8*V) DIGRAPHbfsL(G, 0);
	L_bfs_fim = clock();
	ans.l_bfs = (double)(L_bfs_fim-L_bfs_ini)/CLOCKS_PER_SEC;
	ans.arcos = conta_arcos;
	return ans;
}

int melhor (int n, double p){
	int vezes = 30, i;
	struct no a, ret;
	ret.m_dfs = ret.l_dfs = ret.m_bfs = ret.l_bfs = 0;
	f (i, 0, vezes){
		a = Experimento(n, p);
		ret.m_dfs += a.m_dfs; ret.l_dfs += a.l_dfs; ret.m_bfs += a.m_bfs; ret.l_bfs += a.l_bfs;
	}
	return ret.l_bfs+ret.l_dfs < ret.m_bfs+ret.m_dfs;
}


void driver (){
	int i, j;
	double ini, fim, mid;
	struct no a;
	f (i, 0, 4){
		ini = 0.; fim = 1.0;
		f (j, 0, 20){
			mid = (ini+fim)/2;
			if (melhor (VV[i], mid)) ini = mid;
			else fim = mid;
		}
		printf("numero de vertices = %d\n", VV[i]);
		printf("alpha encontrado = %lf\n", mid);
		a = Experimento (VV[i], mid);
		printf("tempos = %lf %lf %lf %lf, arcos = %d\n", a.m_dfs, a.l_dfs, a.m_dfs, a.m_bfs, a.arcos);
	}
}
	
	
int main (){
	int V, i; double p;
	srand(time(NULL));
	driver();
    return 0;
}
