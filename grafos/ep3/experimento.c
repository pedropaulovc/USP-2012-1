/**
 * MAC0328-2012 - Algoritmos em grafos - Tarefa 3: Descobrindo se um grafo é denso
 * Alunos: 
 *		Stefano Tommasini        - 7278080
 *		Pedro Paulo Vezzá Campos - 7538743
 * Sobre o arquivo: Neste arquivo estão implementadas as funções previamente
 * declaradas em experimento.h relevantes à seção 1 do EP (O experimento).
 */

#include"experimento.h"

resultado Experimento(int V, double p) {
	int i, j;
	ll M_dfs_ini, M_dfs_fim, M_bfs_ini, M_bfs_fim;
	ll L_dfs_ini, L_dfs_fim, L_bfs_ini, L_bfs_fim;
	resultado ans;

	Digraph G = DIGRAPHinit(V);
	
	f (i, 0, V)
		f (j, 0, V)
			if (i != j && rand() <  p*RAND_MAX)
				DIGRAPHinsertA (G, i, j);

	M_dfs_ini = clock();
	f (i, 0, 8)
		DIGRAPHdfsM (G);
	M_dfs_fim = clock();
	ans.m_dfs = (double)(M_dfs_fim - M_dfs_ini)/CLOCKS_PER_SEC; 
	
	L_dfs_ini = clock();
	f (i, 0, 8)
		DIGRAPHdfsL (G);
	L_dfs_fim = clock();
	ans.l_dfs = (double)(L_dfs_fim - L_dfs_ini)/CLOCKS_PER_SEC;
	
	M_bfs_ini = clock();
	f (i, 0, V)
		f(j, 0, 8)
			DIGRAPHbfsM(G, i);
	M_bfs_fim = clock();
	ans.m_bfs = (double)(M_bfs_fim - M_bfs_ini)/CLOCKS_PER_SEC;
	
	L_bfs_ini = clock();
	f (i, 0, V)
		f(j, 0, 8)
			DIGRAPHbfsL(G, i);
	L_bfs_fim = clock();
	ans.l_bfs = (double)(L_bfs_fim - L_bfs_ini)/CLOCKS_PER_SEC;
	
	ans.arcos = G->A;
	return ans;
}

int comparar_representacoes (resultado r){
	double l, m;
	
	l = r.l_bfs + r.l_dfs;
	m = r.m_bfs + r.m_dfs;
	
	if(fabs(l - m) < EPS)
		return TEMPOS_IGUAIS;
	else if(l < m)
		return LISTA_MELHOR;
	return MATRIZ_MELHOR;
}

