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
    (void)trash;
    matrix = vector<vector<int>>(N, vector<int>(N, 0));
    int x_temp, y_temp;
    for (int i = 0; i < M; i++) {
        trash = scanf("%d %d", &x_temp, &y_temp);
        (void)trash;
        if (x_temp > 0 && y_temp > 0) {
            matrix[x_temp - 1][y_temp - 1] = 1;
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

void findSCC() {
    for (int i = 0; i < N; i++) {
        if (ids[i] == -1) {
            dfs(i);
        }
    }
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
                if(matrix[i][j] == 1 && temp != j){
                        matrix[temp][j] = 1;
                }
                if(matrix[j][i] == 1 && temp != j){
                    matrix[j][temp] = 1;
                }
            }
        }
    }
    dag = vector<vector<int>>(sccCount, vector<int>(sccCount, 0));
    for(int i = 0; i < sccCount; i++){
        for(int j = 0; j < sccCount; j++){
            dag[i][j] = matrix[foundScc[1][i]][foundScc[1][j]];
        }
    }
}

void longestPath(){
    int currentNode;
    vector<int> receptors = vector<int>(sccCount, 0);
    vector<int> longestPathList = vector<int>(sccCount, 0);
    stack<int> longestPathStack;
    for(int i = 0; i < sccCount; i++){
        for(int j =0; j < sccCount; j++){
            receptors[i] += dag[j][i];
        }
        if(receptors[i] == 0){
            longestPathStack.push(i);
        }
    }
    while(!longestPathStack.empty()){
        currentNode = longestPathStack.top();
        longestPathStack.pop();
        for(int i = 0; i < sccCount; i++){
            if(dag[currentNode][i] == 1){
                receptors[i]--;
                longestPathList[i] = max(longestPathList[i], longestPathList[currentNode] + 1);
                if(receptors[i] == 0){
                    longestPathStack.push(i);
                }
            }
        }
    }
    int res = 0;
    for(int i = 0; i < sccCount; i++){
        res = max(res, longestPathList[i]);
    }
    printf("%d\n", res);
}

int main() {
    readinput();
    findSCC();
    builtMatrix();
    longestPath();
    return 0;
}
