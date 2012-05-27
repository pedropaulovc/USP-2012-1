/*
 * Digrafo.cpp
 *
 *  Created on: May 26, 2012
 *      Author: pedropaulovc
 */

#include "Digrafo.h"

Digrafo::Digrafo() : V(1), A(0) {
	adj.resize(1);
}

Digrafo::~Digrafo() {
}

void Digrafo::inserirAresta(Vertice v, Vertice w){
	if(max(v, w) >= V){
		V = max(v, w) + 1;
		adj.resize(V);
	}

	if(find(adj[v].begin(), adj[v].end(), w) == adj[v].end()){
		adj[v].push_back(w);
		A++;
	}
}

vector<Vertice> Digrafo::obterOrdemTopologica(){
	vector<Vertice> ts, grauEntrada(V);
	queue<Vertice> fila;

	for(Vertice v = 0; v < V; v++)
		for(unsigned int j = 0; j < adj[v].size(); j++)
			grauEntrada[adj[v][j]]++;

	for(Vertice v = 0; v < V; v++)
		if(grauEntrada[v] == 0)
			fila.push(v);
	for(int i = 0; !fila.empty(); i++){
		Vertice v = fila.front();
		ts.push_back(v);
		fila.pop();

		for(unsigned int j = 0; j < adj[v].size(); j++){
			if(--grauEntrada[adj[v][j]] == 0)
				fila.push(adj[v][j]);
		}
	}

	return ts;
}

int Digrafo::obterQtdSumidouros(){
	int qtdSumidouros = 0;

	for(Vertice v = 0; v < V; v++)
		if(adj[v].size() == 0)
			qtdSumidouros++;

	return qtdSumidouros;
}

void Digrafo::exibir(){
	for(Vertice v = 0; v < V; v++){
		cout << v << ": ";
		for(int j = 0; j < adj[v].size(); j++)
			cout << adj[v][j] << " ";
		cout << endl;
	}
}
