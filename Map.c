#include "Map.h"

#include <stdlib.h>
#include <stdio.h>

void Clear_Map()
{
    for(int i=0;i<map->rows;i++)
    {
        for(int j=0;j<map->columns;j++){
            char * aux;
            aux=malloc(map->columns*sizeof(char));
            aux=map->matrix[i];
            if(aux[j]!='x'){
                map->matrix[i][j]='.';
            }
            
        }
    }
        
}

void Print_Map()
{    
    for (size_t i = 0; i < map->rows; i++)
    {
        for (size_t j = 0; j < map->columns; j++)
        {
            char * aux;
            aux=malloc(map->columns*sizeof(char));
            aux=map->matrix[i];
            if(aux[j]=='x')
            {
                printf( "\x1b[31m%c ",aux[j]);
            }
            else if(aux[j]!='.')
            {
                printf( "\x1b[32m%c ",aux[j]);
            }
            else
            {
                printf( "%c ",aux[j]);
            }
            printf("\x1b[0m");
        }
        printf("\n");
        
    }
      
}

int Is_Valid(int i, int j){
    if(i>=map->rows || i<0 || j>=map->columns || j<0){
        return 0;
    }
    char * aux;
    aux=malloc(map->columns*sizeof(char));
    aux=map->matrix[i];
    if(aux[j]=='o')
    {
        return 0;
    }
    return 1;
}

void Generate_Fruits(int fruit_count)
{
    int count = fruit_count;
    while (count)
    {
        
        int rnd1 = rand() % map->rows;
        int rnd2 = rand() % map->columns;
        char * aux;
        aux=malloc(map->columns*sizeof(char));
        aux=map->matrix[rnd1];
        if(aux[rnd2]=='.')
        {
            map->matrix[rnd1][rnd2]='x';
            count--;
        }
    }
      
}