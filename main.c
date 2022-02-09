#include <stdio.h>
#include <stdlib.h>

#define alive 1
#define dead 0

//Assume we are trying n^2 grid

#define SIZE 10

typedef struct cells{
    int state;
    int next_state;
} cells;

void Print(cells board[][SIZE]){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            (board[i][j].state == alive)? printf(" # "):printf(" 0 ");
        }
        printf("\n");
    }
    printf("-------------------------\n");
}

void comp_state(cells board[][SIZE], int row, int col){
    int ct_alive = 0;
    for (int r = row - 1; r <= row + 1; r++){
        if (r < 0 || r > SIZE - 1) continue; //out of bound
        for (int c = col - 1; c <= col + 1; c++){
            if (c < 0 || c > SIZE - 1) continue; //out of bound
            if (r == row && c == col) continue; //slip itself
            if (board[r][c].state == alive) ct_alive++;
        }
    }
    if (ct_alive >= 4 || ct_alive <= 1) board[row][col].next_state = dead; //overpopulation/underpopulation/loneliness
    else if (ct_alive == 3) board[row][col].next_state = alive; //birth
    else board[row][col].next_state = board[row][col].state; //statis
}

void life(cells board[][SIZE]){ //receive 1D array
    printf("Life begins!\n");
    Print(board);
    int gen; //not actual generation
    printf("Enter relative number of generations:");
    scanf("%d", &gen);
    for (int ct = 0; ct < gen; ct++){
        for (int row = 0; row < SIZE; row++){
            for (int col = 0; col < SIZE; col++){
                comp_state(board,row, col);
            }
        }
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE; j++){
                board[i][j].state = board[i][j].next_state;
            }
        }
        Print(board);
    }
}

int main()
{
    cells board[SIZE][SIZE] = {{0,0}};
    /*for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            if (4 <= i && i <= 6){
                Print(board);
                printf("Enter 1(alive) or 0(dead) for board[%d][%d]:", i, j);
                scanf("%d", &board[i][j].state);
                while (board[i][j].state != alive && board[i][j].state != dead){
                    printf("Invalid! Try again:");
                    scanf("%d", &board[i][j].state);
                }
                board[i][j].next_state = dead; //default
            }
            else{
                board[i][j].state = board[i][j].next_state = dead;
            }
        }
    }*/
    board[4][4].state = board[5][5].state = board[6][3].state = board[6][4].state = board[6][5].state = alive;
    life(board);
    return 0;
}
