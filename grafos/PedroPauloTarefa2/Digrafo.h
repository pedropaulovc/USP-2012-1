/**
 * Aluno: Pedro Paulo Vezzá Campos - 7538743
 * MAC0328-2012 - Algoritmos em grafos - Tarefa 2: Palavra Sincronizadora
 * Sobre o arquivo: Definição de um digrafo simples com operações a serem utilizadas
 * no código principal do EP. Aqui são declarados os protótipos das funções a serem
 * implementadas em Digrafo.cpp além de macros e inclusões relevantes.
 */

#ifndef DIGRAFO_H_
#define DIGRAFO_H_

#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

/**
 * Definição de um vértice para o digrafo como sendo um inteiro.
 */
#define Vertice int

class Digrafo {
public:
	/**
	 * Implementação do digrafo como lista de adjacências.
	 */
	vector<vector<Vertice> > adj;
	/**
	 * Quantidade de vértices e arestas.
	 */
	int V, A;

	/**
	 * Construtor do digrafo.
	 */
	Digrafo();
	/**
	 * Destrutor do digrafo. Desaloca as estruturas utilizadas pela classe.
	 */
	virtual ~Digrafo();

	/**
	 * Insere um arco de v a w apenas uma vez, evitando multiarcos.
	 */
	void inserirAresta(Vertice v, Vertice w);
	/**
	 * Função de ordenação topológica do digrafo. Retorna um vetor contendo
	 * a ordenação.
	 */
	vector<Vertice> obterOrdemTopologica();
	/**
	 * Função de debug, exibe a configuração atual do digrafo.
	 */
	void exibir();
	/**
	 * Função responsável por contar quantos sumidouros há no digrafo.
	 */
	int obterQtdSumidouros();
};

#endif /* DIGRAFO_H_ */
