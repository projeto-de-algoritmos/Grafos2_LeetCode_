#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int reachableNodes(vector<vector<int>>& arestas, int M, int N) {
        vector<vector<pair<int, int>>> adj(N);
        unordered_map<int, int> alcancados;
        
        for (const auto& e : arestas) {
            int u = e[0], v = e[1], n = e[2];
            adj[u].emplace_back(v, n);
            adj[v].emplace_back(u, n);
        }
        
        vector<int> orcamentos(N, -1);
        orcamentos[0] = M;
        
        priority_queue<pair<int, int>> heap;
        heap.emplace(M, 0);
        
        int ans = 0;
        while (!heap.empty()) {
            auto cur = heap.top();
            heap.pop();
            int orcamento = cur.first;
            int u = cur.second;
            if (orcamento < orcamentos[u]) continue;
            ans++;
            
            for (const auto& [v, n] : adj[u]) {
                alcancados[u * N + v] = orcamento;
                if (orcamento - n - 1 > orcamentos[v]) {
                    heap.emplace(orcamento - n - 1, v);
                    orcamentos[v] = orcamento - n - 1;
                }
            }
        }
        
        for (const auto& e : arestas) {
            int u = e[0], v = e[1], n = e[2];
            ans += min(n, alcancados[u * N + v] + alcancados[v * N + u]);
        }
        
        return ans;
    }
};
