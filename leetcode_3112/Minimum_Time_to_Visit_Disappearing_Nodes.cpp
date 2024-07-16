#include <vector> // Inclui a biblioteca de vetores do C++
#include <queue> // Inclui a biblioteca de filas do C++
#include <unordered_map> // Inclui a biblioteca de mapas não ordenados do C++
#include <limits.h> // Inclui a biblioteca para usar o valor INT_MAX
using namespace std; // Usa o namespace padrão do C++ para evitar prefixos std::

// Definição da classe Solution
class Solution {
public:
    // Função que calcula o tempo mínimo para alcançar cada nó a partir do nó 0
    vector<int> minimumTime(int n, vector<vector<int>>& edges, vector<int>& disappear) {
        // Definir o grafo como um mapa não ordenado de listas de pares (peso, nó)
        unordered_map<int, vector<pair<int, int>>> graph;
        // Construir o grafo a partir da lista de arestas
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            graph[u].emplace_back(w, v); // Adiciona a aresta de u para v com peso w
            graph[v].emplace_back(w, u); // Adiciona a aresta de v para u com peso w (grafo não direcionado)
        }

        // Inicializar a fila de prioridade e a resposta
        // A fila de prioridade é usada para encontrar o caminho mais curto (menor tempo)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
        vector<int> ans(n, -1); // Inicializa a resposta com -1 (inacessível)

        // Começar do nó 0 com tempo 0
        heap.emplace(0, 0); // Adiciona o nó 0 na fila com tempo 0

        // Enquanto a fila não estiver vazia
        while (!heap.empty()) {
            auto [w1, node1] = heap.top(); // Obtém o nó com o menor tempo
            heap.pop(); // Remove o nó da fila

            // Se já visitamos este nó, continue
            if (ans[node1] != -1) continue;

            // Atualizar o tempo para alcançar este nó
            ans[node1] = w1;

            // Verificar os nós adjacentes
            for (const auto& [w2, node2] : graph[node1]) {
                int total_time = w1 + w2; // Calcula o tempo total para alcançar o nó adjacente
                // Se o nó desaparecer antes de podermos alcançá-lo, ignore
                if (total_time >= disappear[node2]) continue;
                heap.emplace(total_time, node2); // Adiciona o nó adjacente na fila
            }
        }

        // Retorna o vetor de tempos mínimos
        return ans;
    }
};
