#ifndef GRAFO_H
#define GRAFO_H

#include "Aresta.h"
#include <vector>

class Grafo {
public:
    /** Constroi um grafo simples que possui o numero de vertices recebido por
     *  parametro e que nao possui arestas */
    Grafo(int num_vertices, int num_arestas);

    int num_vertices() const;
    int num_arestas() const;

    bool tem_aresta(Aresta e) const;

    /** Insere uma aresta no grafo caso a aresta ainda nao exista no grafo e
     *  nao seja um laco */
    void insere_aresta(Aresta e);

    /** Remove uma aresta do grafo caso a aresta exista no grafo */
    void remove_aresta(Aresta e);

    /** Retorna o vertice nao marcado com maior grau nao marcado (em caso de
     *  empate, retorna o de menor indice) */
    int vertice_max_grau_nao_marcado(const std::vector<bool> &marcado) const;

    /** Retorna o conjunto dominante S de influenciadores em ordem crescente */
    std::vector<int> influenciadores_a_contratar() const;

private:
    int num_vertices_;
    int num_arestas_;
    std::vector<std::vector<int>> matriz_adj_;

    void valida_vertice(int v) const;
    void valida_aresta(Aresta e) const;
    void valida_qtd_arestas(int num_vertices, int num_arestas) const;
};

#endif /* GRAFO_H */