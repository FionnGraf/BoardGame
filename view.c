//---------------------------------------------------------------------------------------
// Name:	Fionn Graf
// Datum:	08.09.20
// Titel:	View
//---------------------------------------------------------------------------------------

// Includes -----------------------------------------------------------------------------
 #include "includes.h"

// Globale Variablen---------------------------------------------------------------------

HMENU hMenu;
HWND hButton[99][99] = { 0 };
HBITMAP hBMPx;
HBITMAP hBMPo;
HWND hBMP[99][99];
int player = 0;
int board[99][99] = { 0 };
extern int moveCount;

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

    AppendMenuA(hMenu, MF_STRING, Help, "Help");

    SetMenu(hWnd, hMenu);
}

void CreateBoard(HWND hWnd, int width, int height) {
    if ((width < 99) && (height < 99)) {
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
}

void DestroyButton(int coord) {
    int x = coord / 100;
    int y = coord % 100;
    if ((x < 99) && (y < 99)) {
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
    case 0:
        SendMessage(hBMP[x][y], STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBMPo);
        player = 1;
        board[x][y] = 2;
        break;

    case 1:
        SendMessage(hBMP[x][y], STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBMPx);
        player = 0;
        board[x][y] = 3;
        break;
    }
}

void DestroyBitMap(int coord) {
    int x = coord / 100;
    int y = coord % 100;
    if ((x < 99) && (y < 99)) {
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
    DeleteBoard();
    CreateBoard(hWnd, width, height);
    moveCount = 0;
}