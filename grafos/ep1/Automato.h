#ifndef AUTOMATO_H_
#define AUTOMATO_H_

#include <cstdio>
#include <iostream>

using namespace std;

#define MAX_N 2048
#define MAX_K 8

class Automato {
private:
	int n;
	int k;
	int adj[MAX_N][MAX_K];

public:
	Automato();
	virtual ~Automato();
	
	void lerDefinicao();
};

#endif /* AUTOMATO_H_ */
