#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
    
    // Definição da estrutura Tupla para representar cada elemento na fila de prioridade
    struct Tupla {
        int pesoMaximo;
        int x;
        int y;
        
        // Construtor da Tupla para inicializar seus membros
        Tupla(int pesoMaximo, int x, int y) : pesoMaximo(pesoMaximo), x(x), y(y) {}
        
        // Operador '>' sobrecarregado para a fila de prioridade, usando pesoMaximo como critério de ordenação
        bool operator>(const Tupla& outro) const {
            return pesoMaximo > outro.pesoMaximo;
        }
    };
    
public:
    // Função principal que calcula o caminho mínimo para nadar na água representada pela grade
    int swimInWater(vector<vector<int>>& grade) {
        int n = grade.size(); // Tamanho da grade (n x n)
        
        priority_queue<Tupla, vector<Tupla>, greater<Tupla>> pq; // Fila de prioridade mínima para buscar o menor peso
        vector<vector<int>> visitado(n, vector<int>(n, 0)); // Matriz para controlar os nós visitados
        
        pq.push(Tupla(grade[0][0], 0, 0)); // Inicializa a fila de prioridade com o peso da posição inicial (0, 0)
        
        while (!pq.empty()) {
            Tupla t = pq.top(); // Obtém o topo da fila de prioridade (menor peso atual)
            pq.pop(); 
            int x = t.x; 
            int y = t.y;
            int peso = t.pesoMaximo; 
            if (visitado[x][y] == 1) {
                continue; // Se o nó já foi visitado, continua para o próximo
            }
            
            visitado[x][y] = 1; // Marca o nó como visitado
            
            if (x == n - 1 && y == n - 1) {
                return peso; // Se chegou ao destino (última posição), retorna o peso máximo até então
            }
            
            // Verifica os nós adjacentes e os adiciona à fila de prioridade se ainda não foram visitados
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
        
        return 0; // Retorna 0 se não houver caminho válido encontrado
    }
};
