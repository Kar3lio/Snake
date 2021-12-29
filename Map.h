typedef struct Map
{
    int rows;
    int columns;
    char** matrix; 
}Map_t;

Map_t * map;
int fruit_count;

void Clear_Map();

void Print_Map();

int Is_Valid(int i, int j);

void Generate_Fruits(int fruit_count);