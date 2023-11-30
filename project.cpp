#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstring>

using namespace std;

int X, Y;
vector<vector<int>> vect;
vector<vector<int>> matrix;


void readinput(){
    int n;
    scanf("%d %d", &X, &Y);
    scanf("%d", &n);
    vect = vector<vector<int>> (n, vector<int>(3));
    matrix = vector<vector<int>> (X, vector<int>(Y, 0));

    for(int i = 0; i < n; i++){
        scanf("%d %d %d", &vect[i][0], &vect[i][1], &vect[i][2]);
        matrix[vect[i][0]][vect[i][1]] = vect[i][2];
        printf("%d %d %d\n",  vect[i][0], vect[i][1], vect[i][2]);
    }
}

int main(){
    readinput();
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            printf("%d", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
