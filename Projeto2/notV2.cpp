#include <iostream>
#include <vector>
#include <stack>
#include <cstdio>

using namespace std;

int N, M;
vector<vector<int>> matrix;

void readinput() {
    int trash;
    trash = scanf("%d %d", &N, &M);
    (void)trash;
    matrix = vector<vector<int>>(N, vector<int>());
    int x_temp, y_temp;
    for (int i = 0; i < M; i++) {
        trash = scanf("%d %d", &x_temp, &y_temp);
        (void)trash;
        if (x_temp > 0 && y_temp > 0) {
            matrix[x_temp - 1].push_back(y_temp - 1);
        }
    }
}


//Fazer a parte que consiste em percorrer a transposta do grafo e com um 
//sccCount ir colocando o valor correto do scc nos indices corretos 
//topologimente ordenados. 
//Para isso só precisamos de ter conhecimento da stack endValues e da matrix.
void findSCCs(stack<int> endValues){
    int sccCount = 0;
    vector<int> onStackS = vector<int>(N, -1);
}


void dfs() {
    stack<int> s;
    stack<int> endValues;
    vector<bool> onStackS = vector<bool>(N, false);
    vector<bool> visited = vector<bool>(N, false);

    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            s.push(i);
            onStackS[i] = true;

            while (!s.empty()) {
                int temp = s.top();
                bool hasUnvisitedNeighbor = false;

                for (int j = 0; j < matrix[temp].size(); j++) {
                    int next = matrix[temp][j];

                    if (!visited[next]) {
                        if (!onStackS[next]) {
                            s.push(next);
                            onStackS[next] = true;
                            hasUnvisitedNeighbor = true;
                            break;
                        }
                    }
                }

                if (!hasUnvisitedNeighbor) {
                    s.pop();
                    onStackS[temp] = false;
                    if (!visited[temp]) {
                        visited[temp] = true;
                        endValues.push(temp);
                    }
                }
            }
        }
    }
    findSCCs(endValues);

    while (!endValues.empty()) {
    int node = endValues.top();
    endValues.pop();
    cout << "Node: " << node << endl;
    }
}

/*
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


int main() {
    readinput();
    dfs();
    //builtMatrix();
    //longestPath();
    return 0;
}
