/*
 * Visitados.h
 *
 *  Created on: Jun 7, 2012
 *      Author: pedropaulovc
 */

#ifndef VISITADOS_H_
#define VISITADOS_H_

#include <set>
#include <vector>
#include <string>
#include <cstdlib>

#define Vertice int

using namespace std;

typedef struct no no;
struct no {
	no *esq, *dir;
};

class Visitados {
private:
	no *visitados;
	int N;

public:
	Visitados(int N);
	virtual ~Visitados();

	void marcar_visitado(const set<Vertice>& estado);
	bool foi_visitado(const set<Vertice>& estado);
};

#endif /* VISITADOS_H_ */
