#include "szablon.h"

#include <stdio.h>
#define UNASSIGNED 0
#define N 9

int counter=0;
int grid[N][N] = {{0, 8, 4, 0, 9, 7, 0, 0, 2},
    {5, 2, 0, 0, 3, 0, 0, 0, 7},
    {0, 0, 9, 6, 5, 2, 0, 0, 0},
    {0, 0, 0, 5, 0, 6, 0, 0, 8},
    {0, 0, 0, 0, 7, 4, 0, 0, 0},
    {6, 0, 0, 8, 0, 3, 4, 0, 0},
    {0, 0, 0, 2, 4, 5, 3, 0, 0},
    {4, 7, 2, 0, 0, 0, 0, 0, 6},
    {0, 3, 5, 0, 6, 0, 0, 0, 0}
};
void printGrid() {
    REP(row,N) {
        if(!(row%3))printf("\n\n");
        REP(col,N)
        if(!(col%3))
            grid[row][col]?printf("%4d",grid[row][col]):printf("   .");
        else
            grid[row][col]?printf("%2d",grid[row][col]):printf(" .");
        printf("\n");
    }
}
int sol=0;
bool FindUnassignedLocation(int &row, int &col);
bool isSafe( int row, int col, int num);
bool SolveSudoku() {
    int row, col;
    if (!FindUnassignedLocation(row,col)) {
        ///return true; // success!
        sol=0;
        /*for (int col = 0; col < N; col++) {
            if (grid[3][col] != noico[col]){
            printf("\n solution %d \n",sol);
            printGrid();
            cin>>sol;
            }
        }
        */
        if(sol)
            return false;
        else
            return true;
    }
    FOR(num,1,N) {
        if (isSafe( row, col, num)) {
            grid[row][col] = num;
            if (SolveSudoku()) {
                return true;
            }
            grid[row][col] = UNASSIGNED;
        }
    }
    return false; // this triggers backtracking
}
bool FindUnassignedLocation( int &row, int &col) {
    for (row = 0; row < N; row++)//no REP bc referencja
        for (col = 0; col < N; col++)
            if (grid[row][col] == UNASSIGNED)
                return true;
    return false;
}
bool UsedInRow( int row, int num) {
    REP(col,N)
        if (grid[row][col] == num)
            return true;
    return false;
}
bool UsedInCol( int col, int num) {
    REP(row,N)
        if (grid[row][col] == num)
            return true;
    return false;
}
bool UsedInBox( int boxStartRow, int boxStartCol, int num) {
    REP(row,3)REP(col,3)
    if (grid[row+boxStartRow][col+boxStartCol] == num)
        return true;
    return false;
}
bool isSafe( int row, int col, int num) {
    return !UsedInRow( row, num) &&
           !UsedInCol( col, num) &&
           !UsedInBox( row - row%3 , col - col%3, num);
}
int main() {
    printGrid();
    REP(i,20)printf("_");
    if (SolveSudoku() == true) {
        printGrid();
    } else
        printf("No solution exists %d", sol);
    return 0;
}
