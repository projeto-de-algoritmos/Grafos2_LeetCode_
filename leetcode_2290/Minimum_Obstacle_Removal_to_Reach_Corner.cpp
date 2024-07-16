#include <vector> // Inclui a biblioteca padrão do C++ para utilizar o tipo de dado vector
#include <deque>  // Inclui a biblioteca padrão do C++ para utilizar o tipo de dado deque
using namespace std; // Utiliza o namespace std para evitar escrever std:: antes de cada tipo ou função da biblioteca padrão

class Solution {
public:
    // Função para encontrar o número mínimo de obstáculos a serem removidos para ir do canto superior esquerdo ao canto inferior direito
    int minimumObstacles(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(); // Obtém as dimensões da grade (m linhas e n colunas)
        vector<vector<int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // Define as direções possíveis de movimento (baixo, cima, direita, esquerda)
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX)); // Cria uma matriz de distâncias inicializada com o valor máximo possível (infinito)
        deque<pair<int, int>> dq; // Cria uma deque para armazenar as coordenadas das células a serem processadas
        
        dq.push_back({0, 0}); // Adiciona a célula inicial (0, 0) na deque
        dist[0][0] = 0; // Define a distância inicial da célula (0, 0) como 0 (pois começamos aqui)
        
        // Enquanto houver células na deque
        while (!dq.empty()) {
            auto [i, j] = dq.front(); // Obtém a célula da frente da deque
            dq.pop_front(); // Remove a célula da frente da deque
            
            // Para cada direção possível de movimento
            for (auto& d : dirs) {
                int di = i + d[0], dj = j + d[1]; // Calcula as novas coordenadas após o movimento
                
                // Verifica se as novas coordenadas estão dentro dos limites da grade
                if (di >= 0 && dj >= 0 && di < m && dj < n) {
                    int newDist = dist[i][j] + grid[di][dj]; // Calcula a nova distância se mover para essa célula
                    
                    // Se a nova distância for menor do que a distância armazenada anteriormente
                    if (newDist < dist[di][dj]) {
                        dist[di][dj] = newDist; // Atualiza a distância
                        
                        // Se a célula tem um obstáculo (valor 1), adiciona a nova célula ao final da deque
                        if (grid[di][dj] == 1) {
                            dq.push_back({di, dj});
                        } 
                        // Se a célula não tem um obstáculo (valor 0), adiciona a nova célula ao início da deque
                        else {
                            dq.push_front({di, dj});
                        }
                    }
                }
            }
        }
        
        // Retorna a distância mínima para chegar à célula no canto inferior direito
        return dist[m - 1][n - 1];
    }
};
