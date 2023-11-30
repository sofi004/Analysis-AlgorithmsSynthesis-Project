#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstring>

using namespace std;

int X, Y;
vector<vector<int>> vect;
vector<vector<int>> matrix;


void readinput(){
    int n, trash;
    trash = scanf("%d %d", &X, &Y);
    (void) trash;
    trash = scanf("%d", &n);
    (void) trash;
    vect = vector<vector<int>> (n, vector<int>(3));
    matrix = vector<vector<int>> (X + 1, vector<int>(Y + 1, 0));
    int x_temp, y_temp, v_temp;
    for(int i = 0; i < n; i++){
        trash = scanf("%d %d %d", &x_temp, &y_temp, &v_temp);
        (void) trash;
        if((x_temp || y_temp || v_temp) <= 0){
            i--;
            n--;
            continue;
        }
        vect[i][0] = x_temp;
        vect[i][1] = y_temp;
        vect[i][2] = v_temp;
        if(x_temp <= X && y_temp <= Y){
            matrix[vect[i][0]][vect[i][1]] = vect[i][2];
        }
        if(x_temp <= Y && y_temp <= X){
            matrix[vect[i][1]][vect[i][0]] = vect[i][2];
        }
        //printf("%d %d %d\n",  vect[i][0], vect[i][1], vect[i][2]);
    }
}

int main(){
    readinput();
    /*for (int i = 0; i <= X; i++) {
        for (int j = 0; j <= Y; j++) {
            printf("%d  ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");*/
    int temp_value_max = 0;
    int max_value;
    vector<int> x_line_higher(Y + 1, 0);
        for (int i = 1; i <= X; i++) {
            for (int j = 1; j <= Y; j++) {
                //procura na linha atual qual é o maior valor e coloca
                for(int k = 1; k < j; k++){
                    if((matrix[i][k] + matrix[i][j - k]) > temp_value_max){
                        temp_value_max = matrix[i][k] + matrix[i][j - k];
                    }
                }
                
                
                //caso da coluna atual
                for(int z = 1; z < i; z++){
                    if((matrix[z][j] + matrix[i - z][j]) > temp_value_max){
                        temp_value_max = matrix[z][j] + matrix[i - z][j];
                    }
                }
                //comparações
                max_value = max(temp_value_max, matrix[i][j]);
                matrix[i][j] = max_value;
                
            }
            temp_value_max = 0 ;
            
            
        }
    /*for (int i = 0; i <= X; i++) {
        for (int j = 0; j <= Y; j++) {
            printf("%d  ", matrix[i][j]);
        }
    printf("\n");
    }*/
    printf("%d\n", matrix[X][Y]);
    return 0;
}
