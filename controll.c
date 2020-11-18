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
            case Tools_Menu_Settings:
                Settings(hWnd, settingsSize, settingsSize);
                break;
            case Help:
                Settings(hWnd, settingsSize, settingsSize);
                break;
            case Tools_Menu_Settings_Exit:
                DeleteSettings();
                CreateBoard(hWnd, boardWidth, boardHeight);
                break;
            }

            if (wp < 10000) {
                DestroyButton(wp);
                LoadBitMap(hWnd, wp);
                switch(CheckBoard(wp, boardWidth, boardHeight)){
                case 1:
                    if (player == 1) {
                        if (MessageBoxW(hWnd, L"Player 1 Won", L"Winner", MB_OK) == IDOK) {
                            ResetBoard(hWnd, boardWidth, boardHeight);
                        }
                    }
                    else {
                        if (MessageBoxW(hWnd, L"Player 2 Won", L"Winner", MB_OK) == IDOK) {
                            ResetBoard(hWnd, boardWidth, boardHeight);
                        }
                    }
                    break;
                
                case 2:
                    if (MessageBoxW(hWnd, L"Draw", L"Winner", MB_OK) == IDOK) {
                        ResetBoard(hWnd, boardWidth, boardHeight);
                    }
                    break;
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