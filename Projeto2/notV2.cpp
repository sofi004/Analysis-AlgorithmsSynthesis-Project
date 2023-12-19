#include <iostream>
#include <vector>
#include <stack>
#include <cstdio>

using namespace std;

int N, M, sccCount;
vector<vector<int>> matrix;
vector<vector<int>> transpose;
vector<vector<int>> dag;
vector<int> sccVector;

void readinput() {
    int trash;
    trash = scanf("%d %d", &N, &M);
    (void)trash;
    matrix = vector<vector<int>>(N, vector<int>());
    transpose = vector<vector<int>>(N, vector<int>());
    int x_temp, y_temp;
    for (int i = 0; i < M; i++) {
        trash = scanf("%d %d", &x_temp, &y_temp);
        (void)trash;
        matrix[x_temp - 1].push_back(y_temp - 1);
        transpose[y_temp - 1].push_back(x_temp - 1);
    }
}


//Fazer a parte que consiste em percorrer a transposta do grafo e com um 
//sccCount ir colocando o valor correto do scc nos indices corretos 
//topologimente ordenados. 
//Para isso só precisamos de ter conhecimento da stack endValues e da matrix.
void findSCCs(stack<int> endValues){
    sccCount = 0;
    stack<int> aux;
    vector<bool> onAux = vector<bool>(N, false);
    sccVector = vector<int>(N, -1);
    vector<bool> visited = vector<bool>(N, false);
    while(!endValues.empty()){
        int i = endValues.top();
        endValues.pop();
        if (!visited[i] && !onAux[i]) {
            aux.push(i);
            while (!aux.empty()) {
                int temp = aux.top();
                if(!visited[temp] && !onAux[temp]){
                    onAux[temp] = true;
                    for (int next : transpose[temp]) {
                        if (!visited[next] && !onAux[next]) {
                            aux.push(next);
                        }
                    
                    }
                } else{
                    if(onAux[temp]){
                        visited[temp] = true;
                        sccVector[temp] = sccCount;
                    }
                    aux.pop();

                }
            }
            sccCount++;
        }
    }
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
}


void builtMatrix(){
    dag = vector<vector<int>>(sccCount, vector<int>());
    for(int i = 0; i < N; i++){
        for (int j : matrix[i]) {
        if(sccVector[i]!=sccVector[j]){
                dag[sccVector[i]].push_back(sccVector[j]);
            }
        }
    }
}


void longestPath(){
    int maximum = 0;
    vector<int> longestPathList = vector<int>(sccCount, 0);
    for(int i = sccCount -1; i >= 0; i--){
        for(int j : dag[i]){
            longestPathList[i] = max(longestPathList[i], longestPathList[j] +1);
            if(longestPathList[i] > maximum){
                maximum = longestPathList[i];
            }
        }
    }
    printf("%d\n", maximum);
}



int main() {
    readinput();
    dfs();
    builtMatrix();
    longestPath();
    return 0;
}
