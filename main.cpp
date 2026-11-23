#include "Aresta.h"
#include "Grafo.h"
#include <exception>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print_exception(const exception &e, int level = 0) {
    cerr << "exception: " << string(level, ' ') << e.what() << "\n";
    try {
        rethrow_if_nested(e);
    } catch (const std::exception &nested_exception) {
        print_exception(nested_exception, (level + 2));
    }
}

void imprimir_influenciadores(const vector<int> &s) {
    cout << s.size() << ":";
    for (int v : s) {
        cout << " " << v;
    }
    cout << "\n";
}

int main() {
    try {
        int num_perfis, num_conexoes;
        if (!(cin >> num_perfis >> num_conexoes)) {
            return 0;
        }

        Grafo rede(num_perfis, num_conexoes);

        for (int i = 0; i < num_conexoes; i++) {
            int x, y;
            cin >> x >> y;
            rede.insere_aresta(Aresta(x, y));
        }

        imprimir_influenciadores(rede.influenciadores_a_contratar());

        int num_operacoes;
        cin >> num_operacoes;

        for (int i = 0; i < num_operacoes; i++) {
            int x, y;
            cin >> x >> y;
            rede.remove_aresta(Aresta(x, y));
            imprimir_influenciadores(rede.influenciadores_a_contratar());
        }
    } catch (const exception &e) {
        print_exception(e);
    }

    return 0;
}