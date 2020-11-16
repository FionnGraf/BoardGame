//-----------------------------------------------------------------------------------------
// Name:	Fionn Graf
// Datum:	08.09.20
// Titel:	View
//-----------------------------------------------------------------------------------------

// Includes -------------------------------------------------------------------------------
#include "includes.h"

// Konstanten -----------------------------------------------------------------------------
#define CELL_WIDTH 16           //        Possible: 8  12  16
#define CELL_HEIGHT 8           //    Combinations: 4   6   8
#define FIELD_HEIGHT 3
#define FIELD_WIDTH 3
// Globale Variablen-----------------------------------------------------------------------

// Funktions-Prototypen -------------------------------------------------------------------
void view(void);
void printGuideLines(int xLength, int yLength);
void printSquare(int xCoord, int yCoord);
void printPlayers(int player, int xCoord, int yCoord);
void goToxy(int x, int y);
void printInColor(int color, boolean bold);

// Funktionen ----------------------------------------------------------------------------
void view(void){
    printGuideLines(FIELD_WIDTH,FIELD_HEIGHT);
}
// *** Funktionen *** //--------------------------------------------------------------------------

// Spielrahmen ausgeben ------------------------------------------------------------------
void printGuideLines(int xLength, int yLength) {  //use ASCII \xDB
    for (int x = 0; x < xLength; x++) {
        for (int y = 0; y < yLength; y++) { 
            printSquare(x * CELL_WIDTH, y * CELL_HEIGHT);
        }
    }
    
}
// Einzelne Zellen des Spielrahmens ausgeben ---------------------------------------------
void printSquare(int xCoord, int yCoord) {
    for (int x = 0; x <= CELL_WIDTH; x++) {
        goToxy(xCoord + x, yCoord);
        printf("\xDB");
    }
    for (int x = 0; x <= CELL_WIDTH; x++) {
        goToxy(xCoord + x, yCoord+CELL_HEIGHT);
        printf("\xDB");
    }
    for (int y = 0; y < (CELL_HEIGHT + 1); y++) {
        goToxy(xCoord, yCoord + y);
        printf("\xDB\xDB");
    }
    for (int y = 0; y < (CELL_HEIGHT + 1); y++) {
        goToxy(xCoord + CELL_WIDTH, yCoord + y);
        printf("\xDB\xDB");
    }
}
// Spielsteine auseben -------------------------------------------------------------------
void printPlayers(int player, int xCoord, int yCoord) {
    int xStart = CELL_HEIGHT - 2;
    int yStart = CELL_WIDTH - 7;
    for (int x = 0; x < CELL_WIDTH - 2; x = x + 2) {
            goToxy(xStart + x, yStart + x / 2);
            printInColor(0, TRUE);
            printf("\xDB\xDB");
    }
    goToxy(0, 20);
}
// Set cursor to position  ---------------------------------------------------------------
void goToxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
// Color output --------------------------------------------------------------------------
void printInColor(int color, boolean bold) {
    switch (color) {
    case 0:
        if (bold == TRUE) {
            printf("\033[1;31m");   //Bold Red
        }

        else {
            printf("\033[0;31m");   //Red
        }
        break;

    case 1:
        if (bold == TRUE) {
            printf("\033[1;32m");   //Bold Green
        }

        else {
            printf("\033[0;32m");   //Green
        }
        break;

    case 2:
        if (bold == TRUE) {
            printf("\033[1;33m");   //Bold Yellow
        }

        else {
            printf("\033[0;33m");   //Yellow
        }
        break;

    case 3:
        if (bold == TRUE) {
            printf("\033[1;34m");   //Bold Blue
        }

        else {
            printf("\033[0;34m");   //Blue
        }
        break;

    case 4:
        if (bold == TRUE) {
            printf("\033[1;35m");   //Bold Magenta
        }

        else {
            printf("\033[0;35m");   //Magenta
        }
        break;

    case 5:
        if (bold == TRUE) {
            printf("\033[1;36m");   //Bold Cyan
        }

        else {
            printf("\033[0;36m"); //Cyan
        }
        break;
    default:
        printf("\033[0m");  //Reset to Normal
        break;
    }
}