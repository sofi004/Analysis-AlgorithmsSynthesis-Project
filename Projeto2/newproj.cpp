#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstdio>

using namespace std;

int N, M;
vector<vector<int>> matrix;
vector<vector<int>> dag;
int sccCount = 0;
vector<int> low;

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
    low = vector<int>(N, 0);
}

void tarjan() {
    int id = 0;
    stack<int> tarjanStack;
    vector<bool> onStack = vector<bool>(N, false);
    stack<pair<int, int>> s;
    vector<int> ids = vector<int>(N, -1);
    for (int i = 0; i < N; i++) {
        if (ids[i] == -1) {
            s.push({i, 0});

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
                        while (!tarjanStack.empty()) {
                            int v = tarjanStack.top();
                            tarjanStack.pop();
                            onStack[v] = false;
                            low[v] = low[currentId];
                            if (v == currentId) break;
                        }
                        sccCount++;
                    }
                }
            }
        }
    }
}

void topologicalSort(){
    int count = 0;
    vector<int> auxCount = vector<int>(N, -1);
    for(int i = 0; i < N; i++){
        if(auxCount[low[i]] == -1){
            auxCount[low[i]] = count;
            low[i] = count;
            count ++;
        }
        else{
            low[i] = auxCount[low[i]];
        }
    }
}

void builtMatrix(){
    dag = vector<vector<int>>(sccCount, vector<int>(sccCount, 0));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(matrix[i][j] == 1){
                if(low[i] != low[j]){
                    dag[low[i]][low[j]] = 1;
                }
            }
        }
    }
}
/*
void longestPath(){
    int maximum = 0;
    vector<int> longestPathList = vector<int>(sccCount, 0);
    for(int i = sccCount -1; i >= 0; i--){
        for(int j = 0; j < sccCount; j++){
            if(dag[i][j] == 1){
                longestPathList[i] = max(longestPathList[i], longestPathList[j] +1);
                if(longestPathList[i] > maximum){
                    maximum = longestPathList[i];
                }
            }
        }
    }
    printf("%d\n", maximum);
}
*/

void longestPath(){
    int res = 0;
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
                if(longestPathList[i] > res){
                    res = longestPathList[i];
                }
                if(receptors[i] == 0){
                    longestPathStack.push(i);
                }
            }
        }
    }
    printf("%d\n", res);
}

int main() {
    readinput();
    tarjan();
    topologicalSort();
    builtMatrix();
    longestPath();
    return 0;
}
