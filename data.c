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
    int counter = 0;
    
    //check vertical
    for (int i = 1; i < boardHeight; i++) {
        if (checkDirection(board[x][y], x, y + i)) {
            counter++;
        }
    }

    //check horizontal


    //check diagonal


    //check anti diagonal
    

    if (moveCount == height * width){
        return 2;
    }
    //return 0;
}

boolean checkDirection(int player, int deltaX, int deltaY) {
    if (board[deltaX][deltaY] == player) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}
