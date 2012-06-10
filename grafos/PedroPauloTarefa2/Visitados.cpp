/**
 * Aluno: Pedro Paulo Vezzá Campos - 7538743
 * MAC0328-2012 - Algoritmos em grafos - Tarefa 2: Palavra Sincronizadora
 * Sobre o arquivo: Aqui são implementadas as funções declaradas em Visitados.cpp.
 */

#include "Visitados.h"

/**
 * Função auxiliar de criação de novos nós. Retorna um novo nó alocado
 * com filhos marcados como NULL.
 */
no* cria_novo_no(){
	no *novo = new no;
	novo->esq = NULL;
	novo->dir = NULL;

	return novo;
}

Visitados::Visitados(int N) :
		visitados(cria_novo_no()), N(N) {
}

void desaloca_visitados(no *raiz) {
	if (!raiz)
		return;
	if (raiz->esq)
		desaloca_visitados(raiz->esq);
	if (raiz->dir)
		desaloca_visitados(raiz->dir);
	delete raiz;
}

Visitados::~Visitados() {
	desaloca_visitados(visitados);
}

void Visitados::marcar_visitado(const set<Vertice>& vertices) {
	set<Vertice>::iterator it;
	vector<bool> estado(N);
	no *atual = visitados;

	for (it = vertices.begin(); it != vertices.end(); it++)
		estado[*it] = true;

	for (int i = 0; i < N; i++) {
		if (estado[i]) {
			if (!atual->dir)
				atual->dir = cria_novo_no();
			atual = atual->dir;
		} else {
			if (!atual->esq)
				atual->esq = cria_novo_no();
			atual = atual->esq;
		}
	}
}

bool Visitados::foi_visitado(const set<Vertice>& vertices) {
	set<Vertice>::iterator it;
	vector<bool> estado(N);
	no *atual = visitados;

	for (it = vertices.begin(); it != vertices.end(); it++)
		estado[*it] = true;

	for (int i = 0; i < N; i++) {
		if (estado[i]) {
			if(!atual->dir)
				return false;
			atual = atual->dir;
		} else {
			if(!atual->esq)
				return false;
			atual = atual->esq;
		}
	}

	return true;
}
