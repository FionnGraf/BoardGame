#ifndef VIEW_H
#define VIEW_H
#endif
int pWnd(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow);
void AddMenus(HWND);
void CreateBoard(HWND hWnd, int width, int height);
void DestroyButton(int coord);
void LoadBitMap(HWND hWnd, int coord);
void DeleteBoard();
void DestroyBitMap(int coord);
void LoadBoard(HWND hWnd);
void ResetBoard(HWND hWnd, int width, int height);
void Settings(HWND hWnd, int width, int height);
void LoadSettings(HWND hWnd);
void DeleteSettings();
void File_SaveBoard();
void File_ReadBoard();