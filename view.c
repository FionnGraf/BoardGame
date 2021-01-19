//---------------------------------------------------------------------------------------
// Name:	Fionn Graf
// Datum:	08.09.20
// Titel:	View
//---------------------------------------------------------------------------------------

// Includes -----------------------------------------------------------------------------
 #include "includes.h"

// Globale Variablen---------------------------------------------------------------------
HMENU hMenu;
HWND hSettings[8];

HWND hButton[MAX_BOARD_SIZE][MAX_BOARD_SIZE] = { 0 };

HBITMAP hBMPx;
HBITMAP hBMPo;
HWND hBMP[MAX_BOARD_SIZE][MAX_BOARD_SIZE];

int buffer = 0;

extern enum PLAYER player;
player = cross;

int temp;
int board[MAX_BOARD_SIZE][MAX_BOARD_SIZE] = { 0 };
int* pboard = board;
extern int moveCount;
const wchar_t* items[] = { "Tic Tac Toe", "Connect 4" };
HINSTANCE hInstance;
FILE* file_ptr = NULL;
// Funktionen ---------------------------------------------------------------------------

int pWnd(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    WNDCLASSW wc = { 0 };

    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"Window1_Class";
    wc.lpfnWndProc = WinProc;

    MSG msg = { 0 };

    if (!RegisterClassW(&wc))
        return -1;

    CreateWindowW(
        L"Window1_Class",
        L"Tic Tac Toe",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        0,
        0,
        600,
        600,
        NULL,
        NULL,
        NULL,
        NULL);

    while (GetMessage(&msg, NULL, NULL, NULL)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return 0;
}

void AddMenus(HWND hWnd) {
    hMenu = CreateMenu();

    HMENU FileMenu = CreateMenu();
    HMENU ToolMenu = CreateMenu();

    AppendMenuA(hMenu, MF_POPUP, (UINT_PTR)FileMenu, "File");
    AppendMenuA(FileMenu, MF_STRING, File_Menu_New, "New");
    AppendMenuA(FileMenu, MF_STRING, File_Menu_Open, "Open");
    AppendMenuA(FileMenu, MF_SEPARATOR, NULL, NULL);
    AppendMenuA(FileMenu, MF_STRING, File_Menu_Exit, "Exit");

    AppendMenuA(hMenu, MF_POPUP, (UINT_PTR)ToolMenu, "Tools");
    AppendMenuA(ToolMenu, MF_POPUP, Tools_Menu_Reset, "Reset");
    AppendMenuA(ToolMenu, MF_POPUP, Tools_Menu_Settings, "Settings");

    AppendMenuA(hMenu, MF_STRING, Help, "Help");

    SetMenu(hWnd, hMenu);
}

void CreateBoard(HWND hWnd, int width, int height) {
    SetBoardTo(0);
    if ((width < MAX_BOARD_SIZE) && (height < MAX_BOARD_SIZE)) {
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                hButton[x][y] = CreateWindowW(L"button", L"", WS_VISIBLE | WS_CHILD | BS_FLAT, x * buttonSize, y * buttonSize, buttonSize, buttonSize, hWnd, x * 100 + y, NULL, NULL);
                board[x][y] = 1;
            }
        }
    }
    else {
        printf("tried to create a too big playing field\n");
        while (1);
    }
    /*File_SaveBoard();*/
}

void DestroyButton(int coord) {
    int x = coord / 100;
    int y = coord % 100;
    if ((x < MAX_BOARD_SIZE) && (y < MAX_BOARD_SIZE)) {
        DestroyWindow(hButton[x][y]);
    }
    else {
        printf("tried to destroy non existent button\n");
    }
}

void LoadBitMap(HWND hWnd,int coord) {
    int x = coord / 100;
    int y = coord % 100;
    hBMPx = LoadImageW(NULL, L"BMPx.bmp", IMAGE_BITMAP, buttonSize, buttonSize, LR_LOADFROMFILE);
    hBMPo = LoadImageW(NULL, L"BMPo.bmp", IMAGE_BITMAP, buttonSize, buttonSize, LR_LOADFROMFILE);
    hBMP[x][y] = CreateWindowW(L"Static", L"", WS_CHILD | WS_VISIBLE | SS_BITMAP, x * buttonSize, y * buttonSize, buttonSize, buttonSize, hWnd, NULL, NULL, NULL);
    switch (player) {
    case cross:
        SendMessage(hBMP[x][y], STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBMPo);
        player = circle;
        board[x][y] = 2;
        break;

    case circle:
        SendMessage(hBMP[x][y], STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBMPx);
        player = cross;
        board[x][y] = 3;
        break;
    }
}

void DestroyBitMap(int coord) {
    int x = coord / 100;
    int y = coord % 100;
    if ((x < MAX_BOARD_SIZE) && (y < MAX_BOARD_SIZE)) {
        DestroyWindow(hBMP[x][y]);
    }
    else {
        printf("tried to destroy non existent BMP\n");
    }
}

void DeleteBoard() {
    for (int x = 0; x < boardWidth; x++) {
        for (int y = 0; y < boardHeight; y++) {
            if (board[x][y] > 1) {
                DestroyBitMap((x * 100) + y);
            }
            else if(board[x][y] == 1){
                DestroyButton((x * 100) + y);
            }
            board[x][y] = 0;
        }
    }
}

void LoadBoard(HWND hWnd) {

}

void ResetBoard(HWND hWnd, int width, int height) {
    if (hSettings != 0) {
        DeleteSettings();
    }
    DeleteBoard();
    CreateBoard(hWnd, width, height);
    moveCount = 0;
}

void Settings(HWND hWnd, int width, int height) {
    DeleteBoard();
    LoadSettings(hWnd);
}

void LoadSettings(HWND hWnd) {
    hSettings[0] = CreateWindowW(L"static", L"Menu", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER , 1, 1, 582, 25, hWnd, NULL, NULL, NULL);

    hSettings[1] = CreateWindowW(L"static", L"Board Height", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 1, 26, 100, 20, hWnd, NULL, NULL, NULL);
    hSettings[2] = CreateWindowW(L"edit", L"3", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 1, 46, 100, 20, hWnd, NULL, NULL, NULL);
    hSettings[3] = CreateWindowW(L"static", L"Board Width", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 1, 66, 100, 20, hWnd, NULL, NULL, NULL);
    hSettings[4] = CreateWindowW(L"edit", L"3", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 1, 86, 100, 20, hWnd, NULL, NULL, NULL);
    hSettings[5] = CreateWindowW(L"static", L"Win Amount", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 1, 106, 100, 20, hWnd, NULL, NULL, NULL);
    hSettings[6] = CreateWindowW(L"edit", L"3", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 1, 126, 100, 20, hWnd, NULL, NULL, NULL);

    hSettings[7] = CreateWindowW(L"button", L"Exit", WS_VISIBLE | WS_CHILD | BS_FLAT | SS_CENTER, 1, 300, 582, 25, hWnd, Tools_Menu_Settings_Exit, NULL, NULL);
}

void DeleteSettings() {
    for (int i = 0; i < settingsItems; i++) {
        DestroyWindow(hSettings[i]);
    }
}

//void File_SaveBoard() {
//    file_ptr = fopen("C:\\temp\\board.Fionn", "w");
//    if (file_ptr == NULL && file_ptr == 0) {
//        printf("error opening file");
//    }
//    else {
//            for (int i = 0; i < MAX_BOARD_SIZE; i++) {
//                for (int j = 0; j < MAX_BOARD_SIZE; j++) {
//                    if (board[j][i] != 0)
//                        fprintf(file_ptr, "%d,", board[j][i]);
//                }
//                fprintf(file_ptr, "\n");
//            } 
//        fclose(file_ptr);
//    }
//}
//
//void File_ReadBoard() {
//    file_ptr = fopen("C:\\temp\\board.Fionn", "r");
//    if (file_ptr == NULL && file_ptr == 0) {
//        printf("error opening file");
//    }
//    else {
//        for (int i = 3; i < MAX_BOARD_SIZE; i++) {
//            for (int j = 2; j < MAX_BOARD_SIZE; j++) {
//                fscanf(file_ptr, "%d,", &buffer);
//                printf("%d ", buffer);
//            }
//            printf("\n");
//        }
//        printf("\n");
//        fclose(file_ptr);
//    }
//}