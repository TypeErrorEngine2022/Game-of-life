#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define alive 1
#define dead 0

void Print(int cell[], int size){
    for (int i = 0; i < size; i++){
        (cell[i] == alive)? printf(" 1 "):printf(" 0 ");
    }
    printf("\n");
}

void life(int cell[], int size){ //receive 1D array
    Print(cell, size);
    srand(time(NULL)); //initialize random
    int relative_generation; //not actual generation
    printf("Enter relative number of generations:");
    scanf("%d", &relative_generation);

    for (int gen = 0; gen < relative_generation; gen++){
        for (int current = 0; current < size; current++){
            int l_neighbourhood = (current == 0)? 0:current - 1;
            int r_neighbourhood = (current == size)? current:current + 1;
            if (r_neighbourhood >= size) current = rand() % 8; //reset the current position by pseudo-random

            /* both neighbours alive => no room for survival / too fierce competition => dead ultimately
               both neighbours dead => no food to survive/ so boring => dead ultimately
               only one neighbour alive => 50% chance survive
            */
            if (cell[l_neighbourhood++] && cell[r_neighbourhood++]){ //both alive
                cell[current] = dead;
            }
            else if ( !(cell[l_neighbourhood] || cell[r_neighbourhood]) ){ //both dead
                cell[current] = dead;
            }
            else if (cell[l_neighbourhood] ^ cell[r_neighbourhood]){ //either one alive
                cell[current] = rand() % 2;
            }

            Print(cell, size);
        }
    }
}

int main()
{
    int cell[8] = {0,0,0,1,0,0,0,0}; //choose an initial state
    life(cell, 8);
    return 0;
}
