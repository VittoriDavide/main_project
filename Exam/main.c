//
//  main.c
//  Exam
//
//  Created by David Vittori on 2/4/17.
//  Copyright © 2017 David Vittori. All rights reserved.
//

#include <stdio.h>
#include "vector.h"
#define n_r 3
#define n_c 3

typedef struct{
    char name[20];
    int num;
}STP;

void  mapfn(const void * elem, const void * elemNotUsed){
    STP *t =(STP *) elem;
    printf("%s %d\n",t->name,t->num);
}

int comparefn(const void *elem, const void * elem2){
    STP *t =(STP *) elem;
    STP *t1 = (STP *)elem2;
    return !strcmp(t->name,t1->name) && (t1->num - t->num == 0);
}

int matrixIsWhite(int **grid){
    int i ,j;
    for ( i = 0; i < n_r; i++) {
        for ( j = 0; j < n_c; j++) {
            if(grid[i][j] == 1)return 0;
        }
    }
    return 1;
}
void printGrid(int ** grid){
    int i,j;
    printf("\n");
    for ( i = 0; i < n_c; i++) {
        for ( j = 0 ; j < n_r; j++) {
            printf("%d",grid[i][j]);
        }
        printf("\n");
    }
}
void cambiaColore(int **grid, char *r_c, int num){
    int j;
    if (strcmp(r_c, "riga") == 0) {
        for (j = 0; j < n_c; j++) {
            grid[num][j] = !grid[num][j];
        }
    }else{
        for (j = 0; j < n_c; j++) {
            grid[j][num] = !grid[j][num];
        }
    }
}

char *r_c(int i){
    return (i < n_c) ? "riga" : "colonna";
}

int backtrack(int *grid[3], vector *vec, int *count){
    if(matrixIsWhite(grid)){
        return 1;
    }else{
        for (int i = 0 ; i < n_c + n_r; i++) {
            if(count[i])continue;
            int j = (i < n_c) ? i : i-n_c;
            cambiaColore(grid, r_c(i), j);
            count[i] = 1;
            if(backtrack(grid, vec,count)){
                STP t;
                strcpy(t.name, r_c(i));
                t.num = j;
                VectorAppend(vec, &t);
                return 1;
            }
            count[i] = 0;
            cambiaColore(grid, r_c(i), j);
        }
    }
    return 0;
}
int **MATRIXint(int r, int c, int val) {
    int i, j;
    int **t = malloc(r * sizeof(int *));
    for (i=0; i < r; i++){
        t[i] = malloc(c * sizeof(int));
        for (j=0; j < c; j++)
            if ((i + j) % 2  == 0) {
                t[i][j] = val;
            }else{
                t[i][j] = 0;
            }
    }
    return t;
}

int main(int argc, const char * argv[]) {
    vector p;
    VectorNew(&p, sizeof(STP), NULL, 10);
    int ** grid = MATRIXint(n_c, n_r, 1);
    printGrid(grid);
    int *n = malloc(sizeof(int) * 10);
    int i;
    for (i = 0; i < 10; i++) {
        n[i] = 0;
    }
    backtrack(grid, &p, n);
    printf("Il cammino a seguire: \n");
    for (int i = VectorLength(&p) -1; i >= 0 ; i--) {
        STP *t =(STP *) VectorNth(&p, i);
        printf("%s %d\n",t->name,t->num);
    }
    return 0;
}
