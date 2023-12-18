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
    while (!endValues.empty()) {
    int node = endValues.top();
    endValues.pop();
    cout << "Node: " << node << endl;
}
}

int main() {
    readinput();
    dfs();
    return 0;
}
