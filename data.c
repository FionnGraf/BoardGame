//-----------------------------------------------------------------------------------------
// Name:	Fionn Graf
// Datum:	08.09.20
// Titel:	Data
//-----------------------------------------------------------------------------------------

// Includes -------------------------------------------------------------------------------
#include "includes.h"

// Globale Variablen-----------------------------------------------------------------------
int amtRow[4] = { 0 };
extern int board[99][99];
int moveCount = 0;

// Funktionen ----------------------------------------------------------------------------
int CheckBoard(int coord, int width, int height) {
    int x = coord / 100;
    int y = coord % 100;
    int counter[4] = { 1, 1, 1, 1 };
    moveCount++;
    
    //check vertical
    for (int i = 1; i < winAmount; i++) {
        if (CheckDirection(board[x][y], x, y + i)) {
            counter[0]++;
        }
        if (CheckDirection(board[x][y], x, y - i)) {
            counter[0]++;
        }
        if (counter[0] == winAmount) {
            return 1;
        }
    }

    //check horizontal
    for (int i = 1; i < winAmount; i++) {
        if (CheckDirection(board[x][y], x + i, y)) {
            counter[1]++;
        }
        if (CheckDirection(board[x][y], x - i, y)) {
            counter[1]++;
        }
        if (counter[1] == winAmount) {
            return 1;
        }
    }

    //check diagonal
    for (int i = 1; i < winAmount; i++) {
        if (CheckDirection(board[x][y], x + i, y + i)) {
            counter[2]++;
        }
        if (CheckDirection(board[x][y], x - i, y - i)) {
            counter[2]++;
        }
        if (counter[2] == winAmount) {
            return 1;
        }
    }

    //check anti diagonal
    for (int i = 1; i < winAmount; i++) {
        if (CheckDirection(board[x][y], x + i, y - i)) {
            counter[3]++;
        }
        if (CheckDirection(board[x][y], x - i, y + i)) {
            counter[3]++;
        }
        if (counter[3] == winAmount) {
            return 1;
        }
    }

    for (int i = 0; i < 4; i++) {
        amtRow[i] = counter[i];
    }

    if (moveCount == height * width){
        return 2;
    }
}

boolean CheckDirection(int player, int deltaX, int deltaY) {
    if (board[deltaX][deltaY] == player) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}
