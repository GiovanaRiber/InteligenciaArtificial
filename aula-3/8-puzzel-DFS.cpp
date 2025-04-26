#include <vector> // vetor dinâmico
#include <algorithm> // funções prontas
#include <iostream> // imprimir coisas no terminal
#include <stack> // pilha 
#include <unordered_set> //guardar estados visitados

using namespace std;
using Estado = vector<int>;

bool objetivo(const Estado& estado) {
    
    return estado == Estado{1, 2, 3, 4, 5, 6, 7, 8, 0};
}

vector<Estado> gerarVizinhos(const Estado& estado) {

    vector<Estado> vizinhos;

    int posicaoZero = find(estado.begin(), estado.end(), 0) - estado.begin();

    const int movimentos[] = {-3, 3, -1, 1}; // cima, baixo, esquerda, direita

    for (int movimento : movimentos) {
        int novaPosicao = posicaoZero + movimento;
        bool valido = true;

        if (novaPosicao < 0 || novaPosicao >= 9) valido = false;
        if (posicaoZero % 3 == 0 && movimento == -1) valido = false; // borda esquerda
        if (posicaoZero % 3 == 2 && movimento == 1) valido = false;  // borda direita

        if (valido) {
            Estado novoEstado = estado;
            swap(novoEstado[posicaoZero], novoEstado[novaPosicao]);
            vizinhos.push_back(novoEstado);
        }
    }
    return vizinhos;
}

void imprimir(const Estado& estado) {

    for (int i = 0; i < 9; i++) {
        cout << estado[i] << " ";

        if ((i + 1) % 3 == 0) {
            cout << endl; // quebra de linha
        }
    }
    cout << endl; // linha extra ao final
}

void resolverPuzzle(const Estado& estadoInicial) {

    stack<Estado> pilha;

    unordered_set<string> visitados;

    pilha.push(estadoInicial);
    visitados.insert(string(estadoInicial.begin(), estadoInicial.end()));

    int temp = 0;

    while (!pilha.empty()) {
        Estado atual = pilha.top();
        pilha.pop();

        temp++;

        cout << "Estado atual:" << endl;
        imprimir(atual);  // Imprime o tabuleiro atual
        cout << endl;

        if (objetivo(atual)) {
            cout << "Estado Final:" << endl;
            imprimir(atual);  // Imprime o tabuleiro atual
            cout <<"Iteracoes: " << temp << endl;
            cout << "Solucao encontrada!" << endl;
            return;
        }

        for (const Estado& vizinho : gerarVizinhos(atual)) {
            string chave(vizinho.begin(), vizinho.end());
            if (!visitados.count(chave)) {
                visitados.insert(chave);
                pilha.push(vizinho);
            }
        }
    }

    cout << "Nao foi possivel encontrar uma solucao" << endl;
}

int main(){

    // estado inicial exemplo
    Estado estadoInicial ={1, 2, 3,
                           5, 0, 6,
                           4, 7, 8};

    cout << "Tabuleiro Inicial:" << endl;
        imprimir(estadoInicial);  // Imprime o tabuleiro inicial
    cout << endl;

    resolverPuzzle(estadoInicial);
 
     return 0;
}