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
    boolean stop[8] = {TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE};
    moveCount++;
    
    //check vertical
    for (int i = 1; i < winAmount; i++) {
        if (CheckDirection(board[x][y], x, y + i) && stop[0]) {
            counter[0]++;
        }
        else {
            stop[0] = FALSE;
        }

        if (CheckDirection(board[x][y], x, y - i) && stop[1]) {
            counter[0]++;
        }
        else {
            stop[1] = FALSE;
        }

        if (counter[0] == winAmount) {
            return 1;
        }
    }

    //check horizontal
    for (int i = 1; i < winAmount; i++) {
        if (CheckDirection(board[x][y], x + i, y) && stop[2]) {
            counter[1]++;
        }
        else {
            stop[2] = FALSE;
        }

        if (CheckDirection(board[x][y], x - i, y) && stop[3]) {
            counter[1]++;
        }
        else {
            stop[3] = FALSE;
        }

        if (counter[1] == winAmount) {
            return 1;
        }
    }

    //check diagonal
    for (int i = 1; i < winAmount; i++) {
        if (CheckDirection(board[x][y], x + i, y + i) && stop[4]) {
            counter[2]++;
        }
        else {
            stop[4] = FALSE;
        }
        if (CheckDirection(board[x][y], x - i, y - i) && stop[5]) {
            counter[2]++;
        }
        else {
            stop[5] = FALSE;
        }

        if (counter[2] == winAmount) {
            return 1;
        }
    }

    //check anti diagonal
    for (int i = 1; i < winAmount; i++) {
        if (CheckDirection(board[x][y], x + i, y - i) && stop[6]) {
            counter[3]++;
        }
        else {
            stop[6] = FALSE;
        }
        if (CheckDirection(board[x][y], x - i, y + i) && stop[7]) {
            counter[3]++;
        }
        else {
            stop[7] = FALSE;
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
