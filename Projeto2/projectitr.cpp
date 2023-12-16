#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int N, M;
vector<vector<int>> matrix;
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
    (void) trash;
    matrix = vector<vector<int>>(N, vector<int>(N, 0));
    int x_temp, y_temp;
    for (int i = 0; i < M; i++) {
        trash = scanf("%d %d", &x_temp, &y_temp);
        (void) trash;
        printf("%d %d\n", x_temp, y_temp);
        if (((x_temp - 1) < N) && ((y_temp - 1) < N) && ((x_temp) > 0) && ((y_temp) > 0)) {
            matrix[x_temp - 1][y_temp - 1] = 1;
            printf("%d %d %d\n", x_temp, y_temp, matrix[x_temp - 1][y_temp - 1]);
        }
    }
    ids = vector<int>(N, -1);
    low = vector<int>(N, -1);
    onStack = vector<bool>(N, false);
}

void dfs(int start) {
    tarjanStack.push(start);
    onStack[start] = true;
    ids[start] = low[start] = id++;

    while (!tarjanStack.empty()) {
        int currentId = tarjanStack.top();
        int neighbor = 0;
        bool found = false;

        while (neighbor < N) {
            if (matrix[currentId][neighbor] == 1) {
                if (ids[neighbor] == -1) {
                    tarjanStack.push(neighbor);
                    onStack[neighbor] = true;
                    ids[neighbor] = low[neighbor] = id++;
                    found = true;
                    break;
                }
                if (onStack[neighbor]) {
                    low[currentId] = min(low[currentId], low[neighbor]);
                }
            }
            neighbor++;
        }

        if (!found) {
            int node = tarjanStack.top();
            tarjanStack.pop();
            onStack[node] = false;
            low[node] = low[currentId];

            if (node == start) break;
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

int main() {
    printf("ola\n");
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
    return 0;
}
