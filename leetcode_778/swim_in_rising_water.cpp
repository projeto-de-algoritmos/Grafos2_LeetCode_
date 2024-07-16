#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
    
    struct Tupla {
        int pesoMaximo;
        int x;
        int y;
        
        Tupla(int pesoMaximo, int x, int y) : pesoMaximo(pesoMaximo), x(x), y(y) {}
        
        bool operator>(const Tupla& outro) const {
            return pesoMaximo > outro.pesoMaximo;
        }
    };
    
public:
    int swimInWater(vector<vector<int>>& grade) {
        int n = grade.size();
        
        priority_queue<Tupla, vector<Tupla>, greater<Tupla>> pq;
        vector<vector<int>> visitado(n, vector<int>(n, 0));
        
        pq.push(Tupla(grade[0][0], 0, 0));
        
        while (!pq.empty()) {
            Tupla t = pq.top();
            pq.pop();
            int x = t.x;
            int y = t.y;
            int peso = t.pesoMaximo;
            
            if (visitado[x][y] == 1) {
                continue;
            }
            
            visitado[x][y] = 1;
            
            if (x == n - 1 && y == n - 1) {
                return peso;
            }
            
            if (x > 0 && visitado[x - 1][y] == 0) {
                int pesoAtual = max(peso, grade[x - 1][y]);
                pq.push(Tupla(pesoAtual, x - 1, y));
            }
            if (y > 0 && visitado[x][y - 1] == 0) {
                int pesoAtual = max(peso, grade[x][y - 1]);
                pq.push(Tupla(pesoAtual, x, y - 1));
            }
            if (x < n - 1 && visitado[x + 1][y] == 0) {
                int pesoAtual = max(peso, grade[x + 1][y]);
                pq.push(Tupla(pesoAtual, x + 1, y));
            }
            if (y < n - 1 && visitado[x][y + 1] == 0) {
                int pesoAtual = max(peso, grade[x][y + 1]);
                pq.push(Tupla(pesoAtual, x, y + 1));
            }
        }
        
        return 0;
    }
};
