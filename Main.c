#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#include "Map.h"
#include "Node.h"

static Node_t * head;
int growth_count;
int count;
int game_on;
int score;


void Add_Snake_To_Map(Node_t * head)
{
    Node_t * current = head;
    while (current!=NULL)
    {
        map->matrix[current->position_i][current->position_j]=current->value;
        current=current->next;
    }
}

void Move_Snake(int next_i, int next_j)
{
    if(growth_count>0)
    {
        Node_t * aux;
        aux=malloc(sizeof(Node_t));
        aux->value='o';
        aux->position_i=head->position_i;
        aux->position_j=head->position_j;
        aux->next=head->next;
        head->next=aux;
        head->position_i=next_i;
        head->position_j=next_j;
        growth_count--;
        count++;
    }
    else
    {
        Node_t * temp=head;
        for (size_t i = 0; i < count; i++)
        {
            int aux_i=temp->position_i;
            int aux_j=temp->position_j;
            temp->position_i=next_i;
            temp->position_j=next_j;
            temp=temp->next;
            next_i=aux_i;
            next_j=aux_j;
        }
        
    }
}

void To_Initialize()
{
    printf("-1");
    head = (Node_t *)malloc(sizeof(Node_t));
    head->value='@';
    printf("1");
    printf("0%c",head->value);
    head->position_i=map->rows/2;
    head->position_j=(map->columns)/2+1;
    printf("1%c",head->value);
    Node_t * current;
    current =(Node_t *)malloc(sizeof(Node_t));
    head->next=current;
    current->value='o';
    current->position_i=map->rows/2;
    current->position_j=map->columns/2;
    printf("2%c",head->value);

    current =(Node_t *)malloc(sizeof(Node_t));
    head->next->next=current;
    current->value='o';
    current->position_i=map->rows/2;
    current->position_j=(map->columns/2)-1;
    current->next=NULL;

    count=3;
}

int main()
{

    srand(getpid());

    map = NULL;
    map = (Map_t *)malloc(sizeof(Map_t*));
    scanf("%d %d",&map->columns, &map->rows);
    
    To_Initialize();

    score=0;
    game_on=1;

    map->matrix = malloc(map->rows*sizeof(char*));
    for(int i=0;i<map->rows;i++){
        map->matrix[i]=malloc(map->columns*sizeof(char));
        for(int j=0;j<map->columns;j++){
            map->matrix[i][j]='.';            
        }
    }


    Clear_Map();
    Add_Snake_To_Map(head);
    Generate_Fruits(fruit_count);
    
    Print_Map();

    while(game_on)
    {
        if(fruit_count==0)
        {
            fruit_count=5;
            Generate_Fruits(fruit_count);
        }
        int possibilities = 0;
        int dc[] = {0, 1, 0, -1};
        int df[] = {-1, 0, 1, 0};
        int next_pos_i[4];
        int next_pos_j[4];
        int snake_x = head->position_i;
        int snake_y = head->position_j;
        for(int i = 0; i<4;i++){
            if(Is_Valid(snake_x+df[i],snake_y+dc[i]))
            {
                next_pos_i[possibilities]=snake_x+df[i];
                next_pos_j[possibilities]=snake_y+dc[i];
                possibilities++;
            }
        }
        if(possibilities==0)
        {
            game_on=0;
            printf("Game Over\n");
        }
        else
        {
            system("@cls||clear");
            int rnd = rand() % possibilities;
            int next_i = next_pos_i[rnd];
            int next_j = next_pos_j[rnd];
            char * aux;
            aux=malloc(map->columns*sizeof(char));
            aux=map->matrix[next_i];
            if(aux[next_j]=='x')
            {
                growth_count+=3;
                fruit_count--;
                score++;
            }
            Move_Snake(next_i,next_j);
            Clear_Map();
            Add_Snake_To_Map(head);
            Print_Map();
            printf("Score:%d\n",score);
            sleep(1);
        }
        
    }


    return 0;
}