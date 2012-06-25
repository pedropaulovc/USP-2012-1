/**
 * MAC0328-2012 - Algoritmos em grafos - Tarefa 3: Descobrindo se um grafo é denso
 * Alunos: 
 *		Stefano Tommasini        - 7278080
 *		Pedro Paulo Vezzá Campos - 7538743
 * Sobre o arquivo: TODO
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"util.h"
#include"digrafo.h"


int VV[] = {30, 40, 50, 60};

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
	srand(time(NULL));
	driver();
    return 0;
}
