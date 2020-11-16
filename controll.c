//-----------------------------------------------------------------------------------------
// Name:	Fionn Graf
// Datum:	08.09.20
// Titel:	Controll
//-----------------------------------------------------------------------------------------

// Includes -------------------------------------------------------------------------------
#include "includes.h"

// Globale Variablen-----------------------------------------------------------------------
extern int player;
extern int board;
int test = 0;
// Main -----------------------------------------------------------------------------------

LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_COMMAND:

        switch (wp) {
        case File_Menu_Exit:
            DestroyWindow(hWnd);
            break;
        case File_Menu_New:
            MessageBeep(MB_ICONINFORMATION);
            break;
        case Tools_Menu_Reset:
            ResetBoard(hWnd, boardWidth, boardHeight);
            break;
        }

        if (wp < 10000) {
            DestroyButton(wp);
            LoadBitMap(hWnd, wp);
            test = CheckWinner(wp,  boardWidth, boardHeight);
            if (test == 1) {
                printf("%i won\n", player);
            }
            else if (test == 2) {
                printf("draw");
            }
        }

        break;
    case WM_CREATE:
        AddMenus(hWnd);
        CreateBoard(hWnd, boardWidth, boardHeight);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_EXITSIZEMOVE:

        break;

    default:
        return DefWindowProcW(hWnd, msg, wp, lp);
    }
}