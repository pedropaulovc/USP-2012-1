/*
 * EP1.cpp
 *
 *  Created on: Jun 7, 2012
 *      Author: pedropaulovc
 */

#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include "Visitados.h"
#include "Digrafo.h"

using namespace std;

#define DEBUG 0
#if DEBUG == 1
#define debug(x) x
#else
#define debug(x)
#endif

#define MAX_N 2048
#define MAX_K 8
#define Vertice int

#define PALAVRA_ENCONTRADA 0
#define AUTOMATO_NAO_SINCRONIZAVEL 1
#define TEMPO_EXCEDIDO 2
#define PROCESSANDO 3

typedef struct {
	string palavra;
	set<Vertice> conj;
} estado;

typedef struct {
	int tamanho;
	int id;
	string palavra;
} info_componente;

int N;
int K;
vector<vector<Vertice> > adj;
string palavra;
int resultado;

vector<int> sc, s, pre, low;
int cnt, id, t;
int qtd_componentes;

Digrafo D;

vector<set<Vertice> > componentes;

void ler_entrada() {
	cin >> N >> K;

	adj.resize(N);

	int v, w;
	for (int i = 0; i < N; i++) {
		cin >> v;

		getchar();
		getchar();

		for (int j = 0; j < K; j++) {
			cin >> w;
			adj[v].push_back(w);
		}
	}
}

void exibir() {
	for (Vertice v = 0; v < N; v++) {
		cout << v << ": ";
		for (unsigned int j = 0; j < adj[v].size(); j++)
			cout << adj[v][j] << " ";
		cout << endl;
	}
}

void dfsRsc(Vertice v) {
	Vertice w;
	pre[v] = cnt++;
	low[v] = pre[v];
	s[t++] = v;

	for (int i = 0; i < K; i++) {
		if (pre[w = adj[v][i]] == -1)
			dfsRsc(w);
		if (low[w] < low[v])
			low[v] = low[w];
	}

	if (low[v] < pre[v])
		return;
	do {
		sc[w = s[--t]] = id;
		low[w] = N;
	} while (s[t] != v);
	id++;
}

void calcular_componentes_fortes() {
	cnt = id = t = 0;

	s.resize(N);
	sc.resize(N);
	low.resize(N);
	pre.resize(N);

	for (int i = 0; i < N; i++)
		pre[i] = -1;
	for (Vertice v = 0; v < N; v++)
		if (pre[v] == -1)
			dfsRsc(v);
}

void executar_heuristica_3() {
	calcular_componentes_fortes();
	qtd_componentes = id;

	//Montando o digrafo das componentes
	Vertice w;
	for (Vertice v = 0; v < N; v++)
		for (int j = 0; j < K; j++)
			if (sc[v] != sc[w = adj[v][j]])
				D.inserirAresta(sc[v], sc[w]);

	if (D.obterQtdSumidouros() > 1) {
		resultado = AUTOMATO_NAO_SINCRONIZAVEL;
		return;
	}

	vector<Vertice> novos_vertices(qtd_componentes, -1);

	//Criando novos vertices para cada componente não sumidouro
	for (int i = 0; i < qtd_componentes; i++) {
		if (D.adj[i].size() != 0) {
			novos_vertices[i] = adj.size();
			adj.push_back(vector<int>(K, adj.size()));
			sc.push_back(i);
		}
	}

	N = adj.size();
	componentes.resize(qtd_componentes);

	//Atualizando adjacentes
	for (Vertice v = 0; v < N; v++) {
		componentes[sc[v]].insert(v);

		for (int j = 0; j < K; j++)
			if (sc[v] != sc[adj[v][j]])
				adj[v][j] = novos_vertices[sc[v]];
	}
}

bool compara_tamanhos(info_componente c1, info_componente c2) {
	return c1.tamanho < c2.tamanho;
}

void imprime_conjunto(const set<Vertice>& conj) {
	set<Vertice>::iterator it;
	for (it = conj.begin(); it != conj.end(); it++)
		cout << *it << " ";
	cout << endl;
}

void executar_heuristica_1(const set<Vertice>& vertices) {
	queue<estado> fila;
	Visitados visitados(N);
	set<Vertice>::iterator it;

	estado e;
	e.conj = vertices;
	e.palavra = "";

	fila.push(e);
	visitados.marcar_visitado(vertices);

	estado novo, atual;
	while (!fila.empty()) {
		atual = fila.front();
		fila.pop();

		debug(cout << "Atual: "; imprime_conjunto(atual.conj));

		if (atual.conj.size() == 1)
			break;

		for (int i = 0; i < K; i++) {
			novo.conj.clear();

			for (it = atual.conj.begin(); it != atual.conj.end(); it++)
				novo.conj.insert(adj[*it][i]);

			if (!visitados.foi_visitado(novo.conj)) {
				debug(cout << "Novo: "; imprime_conjunto(novo.conj));

				visitados.marcar_visitado(novo.conj);
				novo.palavra = atual.palavra +  string(1, i + 'a');
				fila.push(novo);
			}
		}
	}

	if (atual.conj.size() != 1) {
		resultado = AUTOMATO_NAO_SINCRONIZAVEL;
		return;
	}

	resultado = PALAVRA_ENCONTRADA;
	palavra = atual.palavra;
	while(!fila.empty())
		fila.pop();
}

void executar_heuristica_2(const set<Vertice>& vertices) {
	palavra = "";

	stringstream ss;
	set<Vertice> copia(vertices);
	set<Vertice> escolhidos;
	set<Vertice> novos;
	set<Vertice>::iterator it;

	while (copia.size() != 1) {
		novos.clear();
		escolhidos.clear();

		it = copia.begin();
		for (int i = 0; i < 2; i++) {
			escolhidos.insert(*it);
			it++;
		}

		cout << "Resposta parcial: " << ss.str() << endl << endl;

		string respostaEscolhidos = executarHeuristica1(escolhidos);
		if (resultado == AUTOMATO_NAO_SINCRONIZAVEL)
			return "Autômato não sincronizável.";

		for (it = copia.begin(); it != copia.end(); it++) {
			Vertice novo = *it;
			for (unsigned int i = 0; i < respostaEscolhidos.size(); i++)
				novo = adj[novo][respostaEscolhidos[i] - 'a'];
			novos.insert(novo);
		}

		copia = novos;
		ss << respostaEscolhidos;
	}

	return ss.str();

}

void calcular_palavra_sincronizadora(const set<Vertice>& vertices) {
	executar_heuristica_1(vertices);
}

void calcular_palavra_sincronizadora_v2() {
	resultado = PROCESSANDO;

	set<Vertice> vertices;
	for(int i = 0; i < N; i++)
		vertices.insert(i);

	executar_heuristica_1(vertices);
}

void calcular_palavra_sincronizadora() {
	resultado = PROCESSANDO;

	executar_heuristica_3();

	if (AUTOMATO_NAO_SINCRONIZAVEL == resultado)
		return;

	//Vamos calcular a palavra sincronizadora em ordem crescente de
	//tamanho de subcomponente fortemente conexa e depois juntar
	//os resultados em ordem topológica das componentes
	vector<info_componente> info_componentes(qtd_componentes);

	for (int i = 0; i < qtd_componentes; i++) {
		info_componentes[i].id = i;
		info_componentes[i].tamanho = componentes[i].size();
	}

	sort(info_componentes.begin(), info_componentes.end(), compara_tamanhos);

	for (int i = 0; i < qtd_componentes; i++) {
		int id = info_componentes[i].id;
		calcular_palavra_sincronizadora(componentes[id]);
		if (PALAVRA_ENCONTRADA != resultado)
			break;
		info_componentes[id].palavra = palavra;
	}

	if (PALAVRA_ENCONTRADA != resultado)
		return;

	vector<Vertice> ordem_topologica = D.obterOrdemTopologica();

	stringstream ss;
	for (int i = 0; i < qtd_componentes; i++)
		ss << info_componentes[ordem_topologica[i]].palavra;

	palavra = ss.str();
}

void exibir_resultado() {
	switch (resultado) {
	case PALAVRA_ENCONTRADA:
		cout << palavra << endl;
		break;
	case AUTOMATO_NAO_SINCRONIZAVEL:
		cout << "Autômato não sincronizável" << endl;
		break;
	default:
		cout << "Não foi possível encontrar uma palavra "
				<< "sincronizadora no tempo fornecido." << endl;
		break;
	}
}

int main(int argc, char **argv) {
	//TODO: Getopts
	//TODO: Timeout

	ler_entrada();
	calcular_palavra_sincronizadora();
	exibir_resultado();

	return 0;
}
