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
    
    //check vertical
    int lineCount = 0;
    for (int i = 0; i < boardHeight; i++) {
        if (board[x][i] == board[x][y]) {
            lineCount++;
        }
        else {
            lineCount = 0;;
        }
        if (lineCount == winAmount) {
            return 1;
        }
    }
    
    //check horizontal
    lineCount = 0;
    for (int i = 0; i < boardHeight; i++) {
        if (board[i][y] == board[x][y]) {
            lineCount++;
        }
        else {
            lineCount = 0;;
        }
        if (lineCount == winAmount) {
            return 1;
        }
    }

    //check diagonal
    lineCount = 0;
    for (int i = 0; i < boardHeight; i++) {
        if (board[i + x - y][i] != board[x][y]) {
            lineCount = 0;
        }
        else {
            lineCount++;
        }
        if (lineCount == winAmount) {
            return 1;
        }
    }

    //check anti diagonal
    lineCount = 0;
    for (int i = 0; i < boardHeight; i++) {
        if (board[i + x - y][boardHeight - i - 1] != board[x][y]) {
            lineCount = 0;
        }
        else {
            lineCount++;
        }
        if (lineCount == winAmount) {
            return 1;
        }
    }
    
    if (moveCount == height * width){
        return 2;
    }
    //return 0;
}
