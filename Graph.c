#include <stdio.h>
#define N 7

int isMainGroup(int Graph[N][N], int graph_N, int group[], int group_M){
    int i,j;
    int isMain;
    for(i=0;i<graph_N;i++){
        isMain = 0;
        for(j=0;j<group_M;j++){
            if(i == group[j]) {
                isMain = 1;
                break;
            }
            if(Graph[i][group[j]] == 1) {
                isMain = 1;
                break;
            }
        }
        if(!isMain)
            break;
    }
    return isMain;
}


void Test(){
    int i,j;
    int Graph[N][N];
    int group[3] = {0,3,5};
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            Graph[i][j] = 0;
        }
    }
    Graph[0][1] = 1;
    Graph[0][6] = 1;
    Graph[1][2] = 1;
    Graph[2][1] = 1;
    Graph[2][3] = 1;
    Graph[2][6] = 1;
    Graph[3][1] = 1;
    Graph[3][2] = 1;
    Graph[3][4] = 1;
    Graph[4][3] = 1;
    Graph[4][5] = 1;
    Graph[4][6] = 1;
    Graph[5][1] = 1;
    Graph[5][4] = 1;
    Graph[5][6] = 1;
    Graph[6][0] = 1;
    Graph[6][2] = 1;
    Graph[6][4] = 1;
    Graph[6][5] = 1;

    if(isMainGroup(Graph,7,group,3) == 1){
        printf("OK");
    } else{
        printf("Not main");
    }
}
