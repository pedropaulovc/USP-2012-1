/**
 * Aluno: Pedro Paulo Vezzá Campos - 7538743
 * MAC0328-2012 - Algoritmos em grafos - Tarefa 2: Palavra Sincronizadora
 * Sobre o arquivo: Aqui é implementada a função main do programa além dos
 * algoritmos relevantes à solução do problema proposto.
 */

#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <climits>
#include "Visitados.h"
#include "Digrafo.h"

using namespace std;

/**
 * Define para exibição de informações de debug do programa.
 */
#define DEBUG 0
#if DEBUG == 1
#define debug(x) x
#else
#define debug(x)
#endif

/**
 * Indica a quantidade de vezes que executar_heuristica_2() tentará
 * otimizar os resultados parciais de tamanho de redução da quantidade
 * de vértices "sincronizados".
 */
#define MAX_TENTATIVAS 1

/**
 * Estados possíveis da execução do programa.
 */
#define PALAVRA_ENCONTRADA 0
#define PALAVRA_LONGA 1
#define AUTOMATO_NAO_SINCRONIZAVEL 2
#define TEMPO_EXCEDIDO 3
#define PROCESSANDO 4

/**
 * Definição de um vértice do grafão para a heurística 1. Composto pelo
 * caminho percorrido representado pela string palavra e o conjunto
 * de vértices do autômato que o vértice do grafão representa  através
 * do conjunto conj.
 */
typedef struct {
	string palavra;
	set<Vertice> conj;
} estado;

/**
 * Definição das meta-informações das componentes fortemente conexas do
 * autômato. Composto pelas informações de tamanho da componente, sua id
 * e palavra sincronizadora.
 */
typedef struct {
	int tamanho;
	int id;
	string palavra;
} info_componente;

/**
 * Quantidade de vértices do autômato.
 */
int N;
/**
 * Quantidade de arcos saindo de cada vértice.
 */
int K;
/**
 * Matriz de adjacência do autômato.
 */
vector<vector<Vertice> > adj;
/**
 * Palavra sincronizadora atual.
 */
string palavra;
/**
 * Resultado do processamento, armazena algum dos estados do programa
 * indicados anteriormente.
 */
int resultado;

/**
 * Variáveis do algoritmo de Tarjan de busca de componentes fortemente
 * conexas, tal como definidas nas notas de aula.
 */
vector<Vertice> sc, s, pre, low;
int cnt, id, t;
int qtd_componentes;

/**
 * DAG das componentes fortemente conexas.
 */
Digrafo D;

/**
 * Vetor das componentes fortes. Mapeia uma id de componente aos vértices que estão
 * nesta componente forte.
 */
vector<set<Vertice> > componentes;

/**
 * Tempo máximo de execução do programa.
 */
clock_t tempmax;

/**
 * Função main do programa. Invoca a leitura de entrada, processamento
 * e exibição dos resultados.
 */
int main(int argc, char **argv);
/**
 * Função de cálculo de palavra sincronizadora para o autômato completo.
 * Invoca a heurística 3, o processamento da palavra sincronizadora para
 * cada componente fortemente conexa e compõe a resposta final.
 *
 * Ao final da execução resposta informa o resultado do processamento
 * e caso seja PALAVRA_ENCONTRADA ou PALAVRA_LONGA atribui na variável
 * palavra a palavra sincronizadora correspondente.
 */
void calcular_palavra_sincronizadora();
/**
 * Função responsável pelo cálculo da palavra sincronizadora para cada componente
 * fortemente conexa. Recebe como parâmetro o conjunto de vértices do autômato
 * que correspondem à esta componente forte. A função tem o mesmo comportamento
 * do retorno da resposta que calcular_palavra_sincronizadora().
 */
void calcular_palavra_sincronizadora(const set<Vertice>& vertices);
/**
 * Implementação da heurística 1. Recebe como parâmetro o conjunto de vértices
 * do autômato que correspondem à esta componente forte. A função tem o mesmo
 * comportamento do retorno da resposta que calcular_palavra_sincronizadora().
 */
void executar_heuristica_1(const set<Vertice>& vertices);
/**
 * Implementação da heurística 2. Escolhe randomicamente um par de vértices da
 * componente para calcular a palavra sincronizadora. Realiza este procedimento
 * MAX_TENTATIVAS vezes visando maximizar a "sincronização" de vértices da
 * componente. Recebe como parâmetro o conjunto de vértices
 * do autômato que correspondem à esta componente forte. A função tem o mesmo
 * comportamento do retorno da resposta que calcular_palavra_sincronizadora().
 */
void executar_heuristica_2(const set<Vertice>& vertices);
/**
 * Implementação da heurística 3. Com o resultado da busca de componentes fortes
 * monta o DAG das componentes e o vetor componente e atualiza o autômato inserindo
 * vértices adicionais para cada componente não sumidouro tal como foi descrito na
 * especificação do EP.
 */
void executar_heuristica_3();
/**
 * Implementação do algoritmo de Tarjan de busca de componentes fortemente conexas
 * segundo as notas de aula.
 */
void calcular_componentes_fortes();
/**
 * Implementação da DFS utilizada pelo algoritmo de Tarjan.
 */
void dfsRsc(Vertice v);
/**
 * Função de comparação de structs do tipo info_componente. Retorna true
 * se c1.tamanho < c2.tamanho e false caso contrário.
 */
bool compara_tamanhos(info_componente c1, info_componente c2);
/**
 * Função de debug, imprime um conjunto de vértices do autômato na saída padrão.
 */
void imprime_conjunto(const set<Vertice>& conj);
/**
 * Função de leitura dos dados de entrada dos dados.
 */
void ler_entrada();
/**
 * Função de debug, exibe o autômato no formato descrito pelo EP.
 */
void exibir();
/**
 * Função responsável por analisar se a palavra gerada é curta ou não.
 * Retorna true caso ela seja curta e false caso contrário.
 */
bool palavra_curta();
/**
 * Função de exibição do resultado final do programa segundo a especificação do EP.
 */
void exibir_resultado();

int main(int argc, char **argv) {
	tempmax = INT_MAX;
	if (argc > 1)
		tempmax = time(NULL) + atoi(argv[1]);
	srand(time(NULL));
	ler_entrada();
	calcular_palavra_sincronizadora();
	exibir_resultado();

	return 0;
}

void calcular_palavra_sincronizadora() {
	resultado = PROCESSANDO;

	executar_heuristica_3();

	if (AUTOMATO_NAO_SINCRONIZAVEL == resultado)
		return;
	if (time(NULL) > tempmax) {
		resultado = TEMPO_EXCEDIDO;
		return;
	}

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
	resultado = palavra_curta() ? PALAVRA_ENCONTRADA : PALAVRA_LONGA;
}

void calcular_palavra_sincronizadora(const set<Vertice>& vertices) {
	executar_heuristica_2(vertices);
	if (PALAVRA_ENCONTRADA == resultado && !palavra_curta()) {
		string longa = palavra;
		executar_heuristica_1(vertices);

		if (TEMPO_EXCEDIDO == resultado) {
			palavra = longa;
			resultado = PALAVRA_ENCONTRADA;
		}
	}
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
		if (time(NULL) > tempmax) {
			resultado = TEMPO_EXCEDIDO;
			return;
		}

		atual = fila.front();
		fila.pop();

		debug(cout << "Atual: "; imprime_conjunto(atual.conj));

		if (atual.conj.size() == 1)
			break;

		for (int i = 0; i < K; i++) {
			if (time(NULL) > tempmax) {
				resultado = TEMPO_EXCEDIDO;
				return;
			}

			novo.conj.clear();

			for (it = atual.conj.begin(); it != atual.conj.end(); it++)
				novo.conj.insert(adj[*it][i]);

			if (!visitados.foi_visitado(novo.conj)) {
				debug(cout << "Novo: "; imprime_conjunto(novo.conj));

				visitados.marcar_visitado(novo.conj);
				novo.palavra = atual.palavra + string(1, i + 'a');
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
	while (!fila.empty())
		fila.pop();
}

void executar_heuristica_2(const set<Vertice>& vertices) {
	vector<Vertice> copia(vertices.begin(), vertices.end());
	set<Vertice> escolhidos;
	set<Vertice> novos;

	string parcial, final = "";
	int rand1, rand2;
	while (copia.size() != 1) {
		debug(cout << copia.size() << endl);
		if (time(NULL) > tempmax) {
			resultado = TEMPO_EXCEDIDO;
			return;
		}

		novos.clear();
		escolhidos.clear();

		rand1 = rand() % copia.size();
		do
			rand2 = rand() % copia.size();
		while (rand2 == rand1);

		escolhidos.insert(copia[rand1]);
		escolhidos.insert(copia[rand2]);

		debug(cout << "Escolhidos: " << copia[rand1] <<
				" " << copia[rand2] << endl);
		executar_heuristica_1(escolhidos);

		if (PALAVRA_ENCONTRADA != resultado)
			return;

		parcial = palavra;

		for (int i = 1; i < MAX_TENTATIVAS; i++) {
			if (time(NULL) > tempmax) {
				resultado = TEMPO_EXCEDIDO;
				return;
			}

			escolhidos.clear();

			rand1 = rand() % copia.size();
			do
				rand2 = rand() % copia.size();
			while (rand2 == rand1);

			escolhidos.insert(copia[rand1]);
			escolhidos.insert(copia[rand2]);

			debug(cout << "Escolhidos: " << copia[rand1] <<
					" " << copia[rand2] << endl);
			executar_heuristica_1(escolhidos);
			debug(cout << palavra << endl);

			if (AUTOMATO_NAO_SINCRONIZAVEL == resultado)
				return;

			if (palavra.size() < parcial.size())
				parcial = palavra;
		}

		debug(cout << "Parcial: " << parcial << endl);

		Vertice v;
		for (unsigned int i = 0; i < copia.size(); i++) {
			v = copia[i];
			for (unsigned int j = 0; j < parcial.size(); j++)
				v = adj[v][parcial[j] - 'a'];
			novos.insert(v);
		}

		debug(cout << "Novo conjunto: " << endl; imprime_conjunto(novos));

		copia.clear();
		copia.insert(copia.end(), novos.begin(), novos.end());
		final = final + parcial;
		debug(cout << "Palavra atualizada: " << final << endl);
	}

	resultado = PALAVRA_ENCONTRADA;
	palavra = final;
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

bool compara_tamanhos(info_componente c1, info_componente c2) {
	return c1.tamanho < c2.tamanho;
}

void imprime_conjunto(const set<Vertice>& conj) {
	set<Vertice>::iterator it;
	for (it = conj.begin(); it != conj.end(); it++)
		cout << *it << " ";
	cout << endl;
}

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

bool palavra_curta() {
	return (int) palavra.size() <= (N - 1) * (N - 1);
}

void exibir_resultado() {
	switch (resultado) {
	case PALAVRA_ENCONTRADA:
		cout << palavra.size() << " " << palavra << endl;
		break;
	case AUTOMATO_NAO_SINCRONIZAVEL:
		cout << "0" << endl;
		break;
	case PALAVRA_LONGA:
		cout << "-1 " << "Foi encontrada uma palavra sincronizadora "
				<< "longa (" << palavra.size() << " > " << (N - 1) * (N - 1)
				<< ") no tempo fornecido: " << palavra << endl;
		break;
	case TEMPO_EXCEDIDO:
		cout << "-1 " << "Não foi possível encontrar uma palavra "
				<< "sincronizadora no tempo fornecido." << endl;
		break;
	default:
		break;
	}

}
