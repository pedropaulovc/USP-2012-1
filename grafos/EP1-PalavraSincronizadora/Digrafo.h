/*
 * Digrafo.h
 *
 *  Created on: May 26, 2012
 *      Author: pedropaulovc
 */

#ifndef DIGRAFO_H_
#define DIGRAFO_H_

#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

#define Vertice int

typedef struct {
	int qtdVertices;
	int subComponente;
} subAutomato;

class Digrafo {
public:
	vector<vector<int> > adj;
	int V, A;

	Digrafo();
	virtual ~Digrafo();

	void inserirAresta(Vertice v, Vertice w);
	vector<Vertice> obterOrdemTopologica();
	void exibir();
	int obterQtdSumidouros();
};

#endif /* DIGRAFO_H_ */
