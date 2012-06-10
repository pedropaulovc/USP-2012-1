#include <vector>
#include <iostream>
#include <cstdio>

#define Vertice int

using namespace std;

static int N, K;
static int resultado;
static string resposta;
static vector<vector<Vertice> > adj;

void ler_entrada_2() {
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

void ler_resposta (){
	cin >> resultado >> resposta;
} 

void verificar_resposta(){
	Vertice v;
	for(int i = 0; i < N; i++){
		v = i;
		for(unsigned int j = 0; j < resposta.size(); j++){
			v = adj[v][resposta[j] - 'a'];
		}
		cout << v << " ";
	}
	
	cout << endl;
}

int main_2(){
	ler_entrada_2();
	ler_resposta();
	verificar_resposta();
	
	return 0;
}
