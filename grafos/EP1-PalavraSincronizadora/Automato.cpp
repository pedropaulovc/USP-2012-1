#include "Automato.h"

Automato::Automato() {
}

Automato::~Automato() {
}

void Automato::lerDefinicao() {
	cin >> n >> k;

	adj.resize(n);

	int v, w;
	for (int i = 0; i < n; i++) {
		cin >> v;

		getchar();
		getchar();

		for (int j = 0; j < k; j++) {
			cin >> w;
			adj[v].push_back(w);
		}
	}
}


void imprimeConjunto(const set<Vertice>& conj) {
	set<int>::iterator it;
	for (it = conj.begin(); it != conj.end(); it++)
		cout << *it << " ";
	cout << endl;
}

string Automato::executarHeuristica1(const set<Vertice>& vertices) {
	queue<set<Vertice> > fila;
	map<set<Vertice>, string> caminho;
	map<set<Vertice>, set<Vertice> > pai;
	set<set<Vertice> > visitados;
	set<int>::iterator it;

	fila.push(vertices);
	caminho[vertices] = "";
	pai[vertices] = vertices;
	visitados.insert(vertices);

	set<Vertice> novo, atual;
	while (!fila.empty()) {
		atual = fila.front();
		fila.pop();

//		cout << "Atual: ";
//		imprimeConjunto(atual);
//		cout << "Visitados: " << endl;
//		for (set<set<int> >::iterator iter = visitados.begin();
//				iter != visitados.end(); iter++) {
//			cout << "\t";
//			imprimeConjunto(*iter);
//		}

		if (atual.size() == 1)
			break;

		for (int i = 0; i < k; i++) {
			novo.clear();

			for (it = atual.begin(); it != atual.end(); it++)
				novo.insert(adj[*it][i]);

			if (visitados.find(novo) == visitados.end()) {
//				cout << "Novo: ";
//				imprimeConjunto(novo);

				visitados.insert(novo);
				fila.push(novo);
				pai[novo] = atual;
				caminho[novo] = string(1, i + 'a');
			}
		}
	}

	if (atual.size() != 1) {
		resultado = AUTOMATO_NAO_SINCRONIZAVEL;
		return "";
	}

	stringstream ss;
	resultado = PALAVRA_ENCONTRADA;

	if (vertices.size() == 1)
		ss << "";

	while (pai[atual] != atual) {
		ss << caminho[atual];
		atual = pai[atual];
	}

	return ss.str();
}

string Automato::executarHeuristica2(const set<Vertice>& vertices) {
	if (vertices.size() == 1) {
		resultado = PALAVRA_ENCONTRADA;
		return "";
	}

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

		imprimeConjunto(copia);
		imprimeConjunto(escolhidos);
		cout << "Resposta parcial: " << ss.str() << endl << endl;

		string respostaEscolhidos = executarHeuristica1(escolhidos);
		cout << "Parte: " << respostaEscolhidos << endl;
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

string Automato::calcularPalavraSincronizadora(const set<Vertice>& vertices) {
	return executarHeuristica1(vertices);
}

bool comparaConjuntos(subAutomato sa1, subAutomato sa2) {
	return sa1.qtdVertices < sa2.qtdVertices;
}

string Automato::calcularPalavraSincronizadorav2(){
	set<Vertice> vertices;
	for(int i = 0; i < n; i++)
		vertices.insert(i);
	string resposta = executarHeuristica1(vertices);
	if (AUTOMATO_NAO_SINCRONIZAVEL == resultado)
		return "Autômato não sincronizável";
	return resposta;
}

string Automato::calcularPalavraSincronizadora() {
	resultado = PROCESSANDO;

	vector<set<Vertice> > subAutomatos = executarHeuristica3();

	if (AUTOMATO_NAO_SINCRONIZAVEL == resultado)
		return "Autômato não sincronizável";

	vector<subAutomato> tamanhos(subAutomatos.size());

	for(unsigned int i = 0; i < subAutomatos.size(); i++){
		tamanhos[i].subComponente = i;
		tamanhos[i].qtdVertices = subAutomatos[i].size();
	}

	sort(tamanhos.begin(), tamanhos.end(), comparaConjuntos);

	vector<string> subPalavras(subAutomatos.size());
	for (unsigned int i = 0; i < subAutomatos.size(); i++) {
		string palavra = calcularPalavraSincronizadora(subAutomatos[tamanhos[i].subComponente]);
		if (PALAVRA_ENCONTRADA != resultado)
			break;
		subPalavras[tamanhos[i].subComponente] = palavra;
	}

	if (AUTOMATO_NAO_SINCRONIZAVEL == resultado)
		return "Autômato não sincronizável";
	if (TEMPO_EXCEDIDO == resultado)
		return "Não foi possível encontrar uma palavra sincronizadora no tempo fornecido.";

	vector<Vertice> ordemTopologica = D.obterOrdemTopologica();

	stringstream ss;
	for(unsigned int i = 0; i < ordemTopologica.size(); i++)
		ss << subPalavras[ordemTopologica[i]];

	return ss.str();
}

vector<set<Vertice> > Automato::executarHeuristica3v2() {
	calcularComponentesFortes();
	int qtdComponentes = id;

	vector<set<Vertice> > subAutomatos(qtdComponentes);
	vector<Vertice> novosVertices(qtdComponentes, -1);

	//Atualizando adjacentes
	for (Vertice v = 0; v < n; v++) {
		subAutomatos[sc[v]].insert(v);

		for (int j = 0; j < k; j++)
			if (sc[v] != sc[adj[v][j]]) {
				if (novosVertices[sc[v]] == -1) {
					novosVertices[sc[v]] = adj.size();
					adj.push_back(vector<int>(k, adj.size()));
					sc.push_back(sc[v]);
					n++;
				}

				adj[v][j] = novosVertices[sc[v]];
			}
	}

	return subAutomatos;
}

vector<set<Vertice> > Automato::executarHeuristica3() {
//	//Imprimir novo autômato
//	for (Vertice v = 0; v < n; v++) {
//		for (int j = 0; j < k; j++)
//			cout << v << " -> " << adj[v][j] << ";" << endl;
//	}
//
//	cout << endl;

	calcularComponentesFortes();
	int qtdComponentes = id;

	//Montando grafo das componentes
	Vertice w;
	for (Vertice v = 0; v < n; v++)
		for (int j = 0; j < k; j++)
			if (sc[v] != sc[w = adj[v][j]])
				D.inserirAresta(sc[v], sc[w]);

	if (D.obterQtdSumidouros() > 1) {
		resultado = AUTOMATO_NAO_SINCRONIZAVEL;
		return vector<set<Vertice> >();
	}

	vector<Vertice> novosVertices(qtdComponentes, -1);

	//Criando novos vertices para cada componente não sumidouro
	for (int i = 0; i < qtdComponentes; i++) {
		if (D.adj[i].size() != 0) {
			novosVertices[i] = adj.size();
			adj.push_back(vector<int>(k, adj.size()));
			sc.push_back(i);
		}
	}

	n = adj.size();
	vector<set<Vertice> > subAutomatos(qtdComponentes);

	//Atualizando adjacentes
	for (Vertice v = 0; v < n; v++) {
		subAutomatos[sc[v]].insert(v);

		for (int j = 0; j < k; j++)
			if (sc[v] != sc[adj[v][j]])
				adj[v][j] = novosVertices[sc[v]];
	}

//	//Imprimir novo autômato
//	for (Vertice v = 0; v < n; v++) {
//		for (int j = 0; j < k; j++)
//			cout << v << " -> " << adj[v][j] << ";" << endl;
//	}

	return subAutomatos;
}

void Automato::calcularComponentesFortes() {
	cnt = id = t = 0;

	s.resize(n);
	sc.resize(n);
	low.resize(n);
	pre.resize(n);

	for (int i = 0; i < n; i++)
		pre[i] = -1;
	for (Vertice v = 0; v < n; v++)
		if (pre[v] == -1)
			dfsRsc(v);
}

void Automato::dfsRsc(Vertice v) {
	Vertice w;
	pre[v] = cnt++;
	low[v] = pre[v];
	s[t++] = v;
	for (int i = 0; i < k; i++) {
		if (pre[w = adj[v][i]] == -1)
			dfsRsc(w);
		if (low[w] < low[v])
			low[v] = low[w];
	}
	if (low[v] < pre[v])
		return;
	do {
		sc[w = s[--t]] = id;
		low[w] = n;
	} while (s[t] != v);
	id++;
}

void Automato::exibir() {
	for (Vertice v = 0; v < n; v++) {
		cout << v << ": ";
		for (unsigned int j = 0; j < adj[v].size(); j++)
			cout << adj[v][j] << " ";
		cout << endl;
	}
}
