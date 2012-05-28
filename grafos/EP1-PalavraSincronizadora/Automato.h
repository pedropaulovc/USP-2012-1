#ifndef AUTOMATO_H_
#define AUTOMATO_H_

#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <queue>
#include "Digrafo.h"

using namespace std;

#define MAX_N 2048
#define MAX_K 8
#define Vertice int

#define PALAVRA_ENCONTRADA 0
#define AUTOMATO_NAO_SINCRONIZAVEL 1
#define TEMPO_EXCEDIDO 2
#define PROCESSANDO 3

class Automato {
private:
	int n;
	int k;
	int resultado;
	vector<vector<int> > adj;

	vector<int> sc, s, pre, low;
	int cnt, id, t;

	Digrafo D;
public:
	Automato();
	virtual ~Automato();

	void lerDefinicao();
	string calcularPalavraSincronizadora();
	string calcularPalavraSincronizadora(const set<Vertice>& vertices);
	vector<set<Vertice> > executarHeuristica3();
	vector<set<Vertice> > executarHeuristica3v2();
	string executarHeuristica1(const set<Vertice>& vertices);
	string executarHeuristica2(const set<Vertice>& vertices);
	void calcularComponentesFortes();
	void dfsRsc(Vertice v);
	void exibir();
};

#endif /* AUTOMATO_H_ */
