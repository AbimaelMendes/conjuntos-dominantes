#include "Grafo.h"
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

Grafo::Grafo(int num_vertices, int num_arestas) {
    if (num_vertices <= 0) {
        throw invalid_argument("Erro no construtor Grafo(int, int): o numero de "
            "vertices " + to_string(num_vertices) + " eh invalido!");
    }

    this->valida_qtd_arestas(num_vertices, num_arestas);

    num_vertices_ = num_vertices;
    num_arestas_ = 0;

    matriz_adj_.resize(num_vertices);
    for (int i = 0; i < num_vertices; i++) {
        matriz_adj_[i].resize(num_vertices, 0);
    }
}

int Grafo::num_vertices() const {
    return num_vertices_;
}

int Grafo::num_arestas() const {
    return num_arestas_;
}

bool Grafo::tem_aresta(Aresta e) const {
    return matriz_adj_[e.v1][e.v2] != 0;
}

void Grafo::insere_aresta(Aresta e) {
    try {
        valida_aresta(e);
    } catch (...) {
        throw_with_nested(runtime_error("Erro na operacao "
            "insere_aresta(Aresta): a aresta " + e.to_string() + " eh "
            "invalida!"));
    }

    if (!tem_aresta(e) && (e.v1 != e.v2)) {
        matriz_adj_[e.v1][e.v2] = 1;
        matriz_adj_[e.v2][e.v1] = 1;

        num_arestas_++;
    }
}

void Grafo::remove_aresta(Aresta e) {
    try {
        valida_aresta(e);
    } catch (...) {
        throw_with_nested(runtime_error("Erro na operacao "
            "remove_aresta(Aresta): a aresta " + e.to_string() + " eh "
            "invalida!"));
    }

    if (tem_aresta(e)) {
        matriz_adj_[e.v1][e.v2] = 0;
        matriz_adj_[e.v2][e.v1] = 0;

        num_arestas_--;
    }
}

int Grafo::vertice_max_grau_nao_marcado(const std::vector<bool> &marcado) const {
    int vertice_escolhido = -1;
    int max_grau = -1;

    for (int v = 0; v < num_vertices_; v++) {
        if (!marcado[v]) {
            int grau_nao_marcado = 0;
            for (int u = 0; u < num_vertices_; u++) {
                if (matriz_adj_[v][u] != 0 && !marcado[u]) {
                    grau_nao_marcado++;
                }
            }
            if (grau_nao_marcado > max_grau) {
                max_grau = grau_nao_marcado;
                vertice_escolhido = v;
            }
        }
    }

    return vertice_escolhido;
}

std::vector<int> Grafo::influenciadores_a_contratar() const {
    vector<int> s;
    vector<bool> marcado(num_vertices_, false);
    int nao_marcados = num_vertices_;

    while (nao_marcados > 0) {
        int v = vertice_max_grau_nao_marcado(marcado);
        s.push_back(v);

        if (!marcado[v]) {
            marcado[v] = true;
            nao_marcados--;
        }

        for (int u = 0; u < num_vertices_; u++) {
            if (matriz_adj_[v][u] != 0 && !marcado[u]) {
                marcado[u] = true;
                nao_marcados--;
            }
        }
    }

    sort(s.begin(), s.end());
    return s;
}

void Grafo::valida_vertice(int v) const {
    if ((v < 0) || (v >= num_vertices_)) {
        throw out_of_range("Indice de vertice invalido: " + to_string(v));
    }
}

void Grafo::valida_aresta(Aresta e) const {
    valida_vertice(e.v1);
    valida_vertice(e.v2);
}

void Grafo::valida_qtd_arestas(int num_vertices, int num_arestas) const {
    int max_arestas = (num_vertices * (num_vertices - 1)) / 2;
    if (num_arestas < 0 || num_arestas > max_arestas) {
        throw invalid_argument("Erro na operacao valida_qtd_arestas(int, int): "
            "a quantidade de arestas " + to_string(num_arestas) + " eh "
            "invalida! O numero maximo de arestas para um grafo com "
            + to_string(num_vertices) + " vertices eh " + to_string(max_arestas));
    }
}