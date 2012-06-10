/**
 * Aluno: Pedro Paulo Vezzá Campos - 7538743
 * MAC0328-2012 - Algoritmos em grafos - Tarefa 2: Palavra Sincronizadora
 * Sobre o arquivo: Visitados é um conjunto de nós em formato de árvore binária
 * que armazena eficientemente se um dado estado já foi visitado. Aqui são
 * declarados os protótipos das funções a serem implementadas em Visitados.cpp além
 * de macros e inclusões relevantes.
 */

#ifndef VISITADOS_H_
#define VISITADOS_H_

#include <set>
#include <vector>
#include <string>
#include <cstdlib>

#define Vertice int

using namespace std;

/**
 * Definição de um nó de Visitados como um nó de árvore binária vazio.
 * Caso um elemento esteja no estado toma-se a direção direita e a
 * direção direita caso contrário. Assim, um percurso da raiz até uma folha indica
 * que o estado já foi visitado anteriormente.
 */
typedef struct no no;
struct no {
	no *esq, *dir;
};

class Visitados {
private:
	/**
	 * Árvore binária representando o conjunto de estados visitados.
	 */
	no *visitados;
	/**
	 * Define a quantidade máxima de elementos em um dado estado.
	 */
	int N;

public:
	/**
	 * Construtor do objeto Visitados. Recebe como parâmetro a
	 * quantidade máxima de elementos em um dado estado.
	 */
	Visitados(int N);
	/**
	 * Destrutor do objeto Visitados. Desaloca todas as estruturas de
	 * dados do objeto.
	 */
	virtual ~Visitados();

	/**
	 * Função que recebe um dado estado e marca-o como visitado.
	 */
	void marcar_visitado(const set<Vertice>& estado);
	/**
	 * Função que recebe um dado estado informa se ele já foi visitado.
	 */
	bool foi_visitado(const set<Vertice>& estado);
};

#endif /* VISITADOS_H_ */
