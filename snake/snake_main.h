#pragma once

#include <memory>
#include "resource.h"
#include "public.h"

#define MAX_LOADSTRING                       100

// Global Variables:
HINSTANCE hInst;                                // current instance
TCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
RECT rc;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void                OnTimer(HWND);
void                RestartGame(HDC);
void                DrawRectangle(HDC);
void                DrawBoundary(HDC);
void                ShowText(HDC, WCHAR*, cwy_snake::Font&);
void                ShowText(HDC, int);
void                CreateBean();
void                CreateSnake(HWND);
bool                SnakeMove();
void                ShowSnake(HDC);
void                ShowBean(HDC);
bool                JudgeEatBean();
void                AddSnakeLength();
bool                JudgeSnakeTouchBody();