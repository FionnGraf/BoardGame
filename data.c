//-----------------------------------------------------------------------------------------
// Name:	Fionn Graf
// Datum:	08.09.20
// Titel:	Data
//-----------------------------------------------------------------------------------------

// Includes -------------------------------------------------------------------------------
#include "includes.h"

// Globale Variablen-----------------------------------------------------------------------
extern int board[99][99];
int moveCount = 0;

// Funktionen ----------------------------------------------------------------------------
int CheckWinner(int coord, int width, int height) {
    int x = coord / 100;
    int y = coord % 100;
    moveCount++;
    int counter = 1;
    
    //check vertical
    for (int i = 1; i < winAmount; i++) {
        if (checkDirection(board[x][y], x, y + i)) {
            counter++;
        }
        if (checkDirection(board[x][y], x, y - i)) {
            counter++;
        }
        if (counter == winAmount) {
            return 1;
        }
    }
    counter = 1;
    //check horizontal
    for (int i = 1; i < winAmount; i++) {
        if (checkDirection(board[x][y], x + i, y)) {
            counter++;
        }
        if (checkDirection(board[x][y], x - i, y)) {
            counter++;
        }
        if (counter == winAmount) {
            return 1;
        }
    }
    counter = 1;
    //check diagonal
    for (int i = 1; i < winAmount; i++) {
        if (checkDirection(board[x][y], x + i, y + i)) {
            counter++;
        }
        if (checkDirection(board[x][y], x - i, y - i)) {
            counter++;
        }
        if (counter == winAmount) {
            return 1;
        }
    }
    counter = 1;
    //check anti diagonal
    for (int i = 1; i < winAmount; i++) {
        if (checkDirection(board[x][y], x + i, y - i)) {
            counter++;
        }
        if (checkDirection(board[x][y], x - i, y + i)) {
            counter++;
        }
        if (counter == winAmount) {
            return 1;
        }
    }

    if (moveCount == height * width){
        return 2;
    }
}

boolean checkDirection(int player, int deltaX, int deltaY) {
    if (board[deltaX][deltaY] == player) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}
