#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstring>

using namespace std;
int N, M;
vector<vector<int>> matrix;

void readinput(){
    int trash;
    trash = scanf("%d %d", &N, &M);
    printf("%d %d\n", N, M);
    (void) trash;
    matrix = vector<vector<int>> (N, vector<int>(N, 0));
    int x_temp, y_temp;
    for(int i = 0; i < M; i++){
        trash = scanf("%d %d", &x_temp, &y_temp);
        (void) trash;
        if((x_temp -1) < N && (y_temp -1) < N && (x_temp-1) > 0 && (y_temp-1) > 0){
            matrix[x_temp -1][y_temp -1] = 1;
            printf("%d %d %d\n", x_temp, y_temp, matrix[x_temp -1][y_temp -1]);
        }
    }
}

int main(){
    printf("ola");
    readinput();
    return 0;
}
