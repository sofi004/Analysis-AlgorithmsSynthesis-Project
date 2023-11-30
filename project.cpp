#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

int X, Y;
vector<vector<int>> vect;


void readinput(){
    int n;
    scanf("%d %d", &X, &Y);
    scanf("%d", &n);
    vector<vector<int>> vect(n, vector<int>(3));
    for(int i = 0; i < n; i++){
        scanf("%d %d %d", &vect[i][0], &vect[i][1], &vect[i][2]);
        printf("%d %d %d\n",  vect[i][0], vect[i][1], vect[i][2]);
    }
}

int main(){
    readinput();
}
