#include "Automato.h"

Automato::Automato() {
}

void Automato::lerDefinicao() {
	cin >> n >> k;
	
	int v;
	for(int i = 0; i < n; i++){
		cin >> v;
		
		getchar();
		getchar();
		
		for(int j = 0; j < k; j++)
			cin >> adj[v][j];
	}
}


Automato::~Automato() {
}

