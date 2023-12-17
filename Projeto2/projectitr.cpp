#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstdio>

using namespace std;

int N, M;
vector<vector<int>> matrix;
vector<vector<int>> dag;
int id = 0;
int sccCount = 0;
stack<int> tarjanStack;
vector<int> ids;
vector<int> low;
vector<bool> onStack;

void readinput() {
    int trash;
    trash = scanf("%d %d", &N, &M);
    printf("%d %d\n", N, M);
    (void)trash;
    matrix = vector<vector<int>>(N, vector<int>(N, 0));
    int x_temp, y_temp;
    for (int i = 0; i < M; i++) {
        trash = scanf("%d %d", &x_temp, &y_temp);
        (void)trash;
        printf("%d %d\n", x_temp, y_temp);
        if (x_temp > 0 && y_temp > 0) {
            matrix[x_temp - 1][y_temp - 1] = 1;
            printf("%d %d %d\n", x_temp, y_temp, matrix[x_temp - 1][y_temp - 1]);
        }
    }
    ids = vector<int>(N, -1);
    low = vector<int>(N, 0);
    onStack = vector<bool>(N, false);
}

void dfs(int start) {
    stack<pair<int, int>> s;
    s.push({start, 0});

    while (!s.empty()) {
        int currentId = s.top().first;
        int nextNeighbor = s.top().second;
        s.pop();

        if (nextNeighbor == 0) {
            tarjanStack.push(currentId);
            onStack[currentId] = true;
            ids[currentId] = low[currentId] = id++;
        }

        bool found = false;
        for (int neighbor = nextNeighbor; neighbor < N; neighbor++) {
            if (matrix[currentId][neighbor] == 1) {
                if (ids[neighbor] == -1) {
                    s.push({currentId, neighbor + 1});
                    s.push({neighbor, 0});
                    found = true;
                    break;
                } else if (onStack[neighbor]) {
                    low[currentId] = min(low[currentId], ids[neighbor]);
                }
            }
        }

        if (!found) {
            if (nextNeighbor > 0) {
                int node = tarjanStack.top();
                low[currentId] = min(low[currentId], low[node]);
            }

            if (low[currentId] == ids[currentId]) {
                // currentId é o início de uma nova componente fortemente conectada
                while (!tarjanStack.empty()) {
                    int v = tarjanStack.top();
                    tarjanStack.pop();
                    onStack[v] = false;
                    low[v] = low[currentId]; // atualizar todos os nós na SCC com o mesmo valor
                    if (v == currentId) break;
                }
                sccCount++;
            }
        }
    }
}

vector<int> findSCC() {
    for (int i = 0; i < N; i++) {
        if (ids[i] == -1) {
            dfs(i);
        }
    }
    return low;
}

void builtMatrix(){
    vector<vector<int>> foundScc = vector<vector<int>>(2, vector<int>(sccCount, -1));
    int foundSccCount = 0;
    for(int i = 0; i < N; i++){
        int temp = -1;
        for(int j = 0; j < foundSccCount; j++){
            if(low[i] == foundScc[0][j]){
                temp = foundScc[1][j];
            }
        }
        if(temp == -1){
            foundScc[0][foundSccCount] = low[i];
            foundScc[1][foundSccCount] = i;
            foundSccCount++;
        }
        else{
            for(int j = 0; j< N; j++){
                if(matrix[i][j] == 1){
                    matrix[temp][j] = 1;
                }
                if(matrix[j][i] == 1){
                    matrix[j][temp] = 1;
                }
            }
        }
    }
    dag = vector<vector<int>>(sccCount, vector<int>(sccCount, 0));
    printf("\n");
    printf("\n");
    for(int j = 0; j < sccCount; j++){
        printf("%d ", foundScc[1][j]);
    }
    printf("\n");
    printf("\n");
    for(int i = 0; i < sccCount; i++){
        for(int j = 0; j < sccCount; j++){
            dag[i][j] = matrix[foundScc[1][i]][foundScc[1][j]];
            printf("%d ", dag[i][j]);
        }
        printf("\n");
    }
}

int main() {
    readinput();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    findSCC();
    printf("\n");
    printf("\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", low[i]);
    }
    printf("\n");
    builtMatrix();
    printf("\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}
