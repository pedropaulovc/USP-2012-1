/**
 * MAC0328-2012 - Algoritmos em grafos - Tarefa 3: Descobrindo se um grafo é denso
 * Alunos: 
 *		Stefano Tommasini        - 7278080
 *		Pedro Paulo Vezzá Campos - 7538743
 * Sobre o arquivo: Neste arquivo estão implementadas as funções previamente
 * declaradas em driver.h relevantes à seção 2 do EP (O teste).
 */

#include"driver.h"

/**
 * Testes padrão para uma análise genérica dos valores de p que demarcam se 
 * um digrafo é esparso ou denso.
 */
int qtd_testes = 8;
int testes[] = {10, 20, 50, 80, 100, 150, 250, 500};

resultado rodar_teste (int V, double p){
	int i;
	resultado r, total;
	total.arcos = total.m_dfs = total.l_dfs = total.m_bfs = total.l_bfs = 0;

	f (i, 0, REPETICOES_EXPERIMENTO){
		r = Experimento(V, p);
		
		total.m_dfs += r.m_dfs;
		total.l_dfs += r.l_dfs;
		total.m_bfs += r.m_bfs;
		total.l_bfs += r.l_bfs;
	}

	return total;
}

void imprimir_cabecalho(){
	printf("V;alfa;m_dfs;m_bfs;l_dfs;l_bfs;diferenca\n");
}

void imprimir_resultado(int V, double alfa, resultado r){
	double diferenca = r.m_dfs + r.m_bfs - r.l_dfs - r.l_bfs;

	printf("%d;%.8f;%.8f;%.8f;%.8f;%.8f;%.8f\n", V, alfa, r.m_dfs,
	r.m_bfs, r.l_dfs, r.l_bfs, diferenca);
}

void imprimir_ajuda(){
	puts(" - Classe p = \\alpha:");
	puts("\t - 'a V': Busca p para um grafo de V vértices aleatórios, exibe parciais.");
	puts("\t - 'A V': Idem anterior, não exibe parciais.");
	puts("\t - 'b': Roda uma bateria de testes para determinar o valor de p para digrafos");
	puts("\tcontendo 10, 20, 50, 80, 100, 150, 250 e 500 vértices, exibe parciais.");
	puts("\t - 'B': Idem anterior, não exibe parciais.");
	puts(" - Classe p = \\alpha/lg(V)");
	puts("\t - 'l V': Busca p para um grafo de V vértices aleatórios, exibe parciais.");
	puts("\t - 'L V': Idem anterior, não exibe parciais.");
	puts("\t - 'm': Roda uma bateria de testes para determinar o valor de p para digrafos");
	puts("\tcontendo 10, 20, 50, 80, 100, 150, 250 e 500 vértices, exibe parciais.");
	puts("\t - 'M': Idem anterior, não exibe parciais.");
	puts(" - 'e V p' para rodar um experimento com V vértices e probabilidade p.");
	puts(" - 'f' para encerrar o programa ");
}

void buscar_alfa(int V, double den, int parcial){
	int i = 0, comp = -1;
	double ini = 0., fim = 1.0/den, mid;
	resultado r;
	
	imprimir_cabecalho();
	
	while(comp != TEMPOS_IGUAIS && i < MAX_TENTATIVAS) {
		mid = (ini+fim)/2;
		r = rodar_teste(V, mid);
		comp = comparar_representacoes(r);

		if(parcial)
			imprimir_resultado(V, mid * den, r);
		
		if(comp == LISTA_MELHOR)
			ini = mid;
		else
			fim = mid;
		
		i++;
	}
	
	if(!parcial)
		imprimir_resultado(V, mid * den, r);
}


void driver(){
	char c;
	int V, i;
	double p;
	resultado r;
	
	scanf("%c", &c);
	
	while(c != 'f'){
		switch(c){
		case 'a':
			scanf("%d", &V);
			buscar_alfa(V, 1.0, TRUE);
			break;
		case 'A':
			scanf("%d", &V);
			buscar_alfa(V, 1.0, FALSE);
			break;
		case 'b':
			f(i, 0, qtd_testes)
				buscar_alfa(testes[i], 1.0, TRUE);
			break;
		case 'B':
			f(i, 0, qtd_testes)
				buscar_alfa(testes[i], 1.0, FALSE);
			break;
		case 'l':
			scanf("%d", &V);
			buscar_alfa(V, log(V)/log(2), TRUE);
			break;
		case 'L':
			scanf("%d", &V);
			buscar_alfa(V, log(V)/log(2), FALSE);
			break;
		case 'm':
			f(i, 0, qtd_testes)
				buscar_alfa(testes[i], log(testes[i])/log(2), TRUE);
			break;
		case 'M':
			f(i, 0, qtd_testes)
				buscar_alfa(testes[i], log(testes[i])/log(2), FALSE);
			break;
		case 'e':
			scanf("%d %lf", &V, &p);
			r = Experimento(V, p);
			imprimir_resultado(V, p, r);
			break;
		case 'h':
			imprimir_ajuda();
			break;
		default:
			break;
		}
		
		if(scanf("%c", &c) != 1)
			return;
	}
}

