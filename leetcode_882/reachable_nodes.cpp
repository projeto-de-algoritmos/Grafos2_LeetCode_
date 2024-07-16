#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Função principal que calcula o número de nós alcançáveis
    int reachableNodes(vector<vector<int>>& arestas, int M, int N) {
        // Criação da lista de adjacência, onde cada nó tem uma lista de pares (nó adjacente, peso)
        vector<vector<pair<int, int>>> adj(N);
        // Mapa para rastrear a quantidade de nós alcançados em cada aresta
        unordered_map<int, int> alcancados;
        
        // Construção da lista de adjacência a partir das arestas fornecidas
        for (const auto& e : arestas) {
            int u = e[0], v = e[1], n = e[2];
            adj[u].emplace_back(v, n);
            adj[v].emplace_back(u, n);
        }
        
        // Inicialização dos orçamentos, que representam o número máximo de movimentos restantes para cada nó
        vector<int> orcamentos(N, -1);
        orcamentos[0] = M; // Começamos com M movimentos a partir do nó 0
        
        // Fila de prioridade para processar nós, baseada no orçamento (movimentos restantes)
        priority_queue<pair<int, int>> heap;
        heap.emplace(M, 0);
        
        int ans = 0; // Contador de nós alcançáveis
        while (!heap.empty()) {
            auto cur = heap.top();
            heap.pop();
            int orcamento = cur.first;
            int u = cur.second;
            if (orcamento < orcamentos[u]) continue; // Se o orçamento atual for menor que o armazenado, ignora
            
            ans++; // Conta o nó atual como alcançável
            
            // Verifica os nós adjacentes
            for (const auto& [v, n] : adj[u]) {
                alcancados[u * N + v] = orcamento; // Armazena o alcance atual para a aresta (u, v)
                if (orcamento - n - 1 > orcamentos[v]) { // Relaxamento da aresta, se o orçamento permite
                    heap.emplace(orcamento - n - 1, v); // Adiciona o nó adjacente na fila de prioridade
                    orcamentos[v] = orcamento - n - 1; // Atualiza o orçamento para o nó adjacente
                }
            }
        }
        
        // Calcula o número total de nós alcançáveis considerando as arestas
        for (const auto& e : arestas) {
            int u = e[0], v = e[1], n = e[2];
            ans += min(n, alcancados[u * N + v] + alcancados[v * N + u]);
        }
        
        return ans; // Retorna o número total de nós alcançáveis
    }
};
