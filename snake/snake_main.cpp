// snake.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "snake_main.h"
#include <time.h>

using namespace cwy_snake;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPTSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    MSG msg;
    HACCEL hAccelTable;

    // Initialize global strings
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_SNAKE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    srand((unsigned int)time(NULL));

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow)) {
        return FALSE;
    }

    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SNAKE));


    // Main message loop:
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SNAKE));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)::GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd;

    hInst = hInstance; // Store instance handle in our global variable
    int scrWidth = GetSystemMetrics(SM_CXSCREEN);
    int scrHeight = GetSystemMetrics(SM_CYSCREEN);

    RECT rect;
    rect.right = WINDOW_WIDTH;
    rect.bottom = WINDOW_HEIGHT;
    rect.left = (scrWidth - rect.right) / 2;
    rect.top = (scrHeight - rect.bottom) / 2;

    hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    MoveWindow(hWnd, rect.left, rect.top, rect.right, rect.bottom, 1);

    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, Uint, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAint	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message) {
    case WM_CREATE:
        GetClientRect(hWnd, &rc);
        boundaryWidth = WINDOW_WIDTH - rc.right;
        boundaryHeight = WINDOW_HEIGHT - rc.bottom;
        isStandardHeight = ((rc.top + BOUNDARY_DISTANCE + GAME_WINDOW_HEIGTH) <= (rc.bottom - BOUNDARY_DISTANCE));
        isStandardWidth = ((rc.left + BOUNDARY_DISTANCE + GAME_WINDOW_WIDTH) <= (rc.right - BOUNDARY_RIGHT_DISTANCE));
        break;

    case WM_COMMAND:
        wmId = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
        // Parse the menu selections:
        switch (wmId) {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;

        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;

    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code here...
        RestartGame(hdc);
        EndPaint(hWnd, &ps);
        break;

    case WM_KEYDOWN:
        switch (wParam) {
        case VK_RETURN:
            if (!isGameBegin) {
                SetTimer(hWnd, 1, 200, NULL);
                CreateSnake(hWnd);
                CreateBean();
                isGameBegin = true;
            }
            break;

        case VK_UP:
            if (direction != dir::DOWN) {
                direction = dir::UP;
            }
            break;

        case VK_DOWN:
            if (direction != dir::UP) {
                direction = dir::DOWN;
            }
            break;

        case VK_LEFT:
            if (direction != dir::RIGHT) {
                direction = dir::LEFT;
            }
            break;

        case VK_RIGHT:
            if (direction != dir::LEFT) {
                direction = dir::RIGHT;
            }
            break;

        default:
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_TIMER:
        hdc = GetDC(hWnd);
        OnTimer(hWnd);
        ReleaseDC(hWnd, hdc);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message) {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void OnTimer(HWND hWnd)
{
    HDC hdc = GetDC(hWnd);

    // 双缓存-防止图片刷新时闪烁
    HDC hComDc = CreateCompatibleDC(hdc);
    HBRUSH hr = CreateSolidBrush(RGB(0, 0, 0));
    HBITMAP hBitmap = CreateCompatibleBitmap(hdc, rc.right - rc.left, rc.bottom - rc.top);
    SelectObject(hComDc, hBitmap);
    FillRect(hComDc, &rc, hr);

    // 铺图
    DrawRectangle(hComDc);

    // 画游戏边界
    DrawBoundary(hComDc);

    if (!SnakeMove()) { // 蛇头触碰边界/蛇身-游戏结束
        KillTimer(hWnd, 1);
        snake_list.clear();
        direction = dir::RIGHT;
        score = 0;
        DrawRectangle(hdc);
        MessageBox(hWnd, L"游戏结束", L"提示", MB_OK);
        RestartGame(hdc);
        isGameBegin = false;
    } else {
        ShowSnake(hComDc);
        ShowBean(hComDc);
        if (JudgeEatBean()) {
            CreateBean();
            AddSnakeLength();
            score += 10;
        }
        ShowText(hComDc, score);
        // 将兼容DC上的图片画到主DC上
        BitBlt(hdc, 0, 0, rc.right, rc.bottom, hComDc, 0, 0, SRCCOPY);
    }

    DeleteDC(hComDc);
    DeleteObject(hr);
    DeleteObject(hBitmap);
    ReleaseDC(hWnd, hdc);

    return;
}

void RestartGame(HDC hdc)
{
    DrawRectangle(hdc);
    ShowText(hdc, L"贪吃蛇游戏", Font(rc.right / 4, rc.bottom / 3, 75, 50, 0, 255, 0));
    ShowText(hdc, L"按Enter键开始", Font(rc.right / 3, rc.bottom / 3 * 2, 30, 20, 0, 0, 255));
}

void DrawRectangle(HDC hdc)
{
    HBRUSH hr = CreateSolidBrush(RGB(0, 0, 0));
    HBRUSH old_brush = (HBRUSH)SelectObject(hdc, hr);
    Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
    SelectObject(hdc, old_brush);
    DeleteObject(hr);
    DeleteObject(old_brush);

    return;
}

void DrawBoundary(HDC hdc)
{
    HPEN hp = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
    HPEN old_pen = (HPEN)SelectObject(hdc, hp);

    HBRUSH hr = CreateSolidBrush(RGB(0, 0, 0));
    HBRUSH old_brush = (HBRUSH)SelectObject(hdc, hr);

    Rectangle(hdc, rc.left + BOUNDARY_DISTANCE, rc.top + BOUNDARY_DISTANCE,
        isStandardWidth ? (rc.left + BOUNDARY_DISTANCE + GAME_WINDOW_WIDTH) : (rc.right - BOUNDARY_RIGHT_DISTANCE),
        isStandardHeight ? (rc.top + BOUNDARY_DISTANCE + GAME_WINDOW_HEIGTH) : (rc.bottom - BOUNDARY_DISTANCE));

    SelectObject(hdc, old_pen);
    SelectObject(hdc, old_brush);

    DeleteObject(hp);
    DeleteObject(old_pen);
    DeleteObject(hr);
    DeleteObject(old_brush);

    return;
}


void ShowText(HDC hdc, WCHAR* text, cwy_snake::Font& font)
{
    if (nullptr == text)
        return;

    HFONT my_font = CreateFont(
        font.sizeHeight_,
        font.sizeWidth_,
        0,
        0,
        700,
        FALSE,
        FALSE,
        FALSE,
        DEFAULT_CHARSET,
        OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
        DEFAULT_QUALITY,
        FF_DONTCARE,
        L"宋体"
    );
    SetTextColor(hdc, RGB(font.red_, font.green_, font.blue_));
    SetBkMode(hdc, TRANSPARENT);
    SelectObject(hdc, my_font);
    TextOut(hdc, font.location_.x_, font.location_.y_, text, wcslen(text));
    DeleteObject(my_font);

    return;
}

void ShowText(HDC hdc, int score)
{
    HFONT font = CreateFont(
        25,
        15,
        0,
        0,
        700,
        FALSE,
        FALSE,
        FALSE,
        DEFAULT_CHARSET,
        OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
        DEFAULT_QUALITY,
        FF_DONTCARE,
        L"宋体"
    );
    SetTextColor(hdc, RGB(0, 255, 0));
    SetBkMode(hdc, TRANSPARENT);
    SelectObject(hdc, font);
    TCHAR text[20] = {0};
    wsprintf(text, L"分数：%d", score);
    TextOut(hdc, rc.right - BOUNDARY_RIGHT_DISTANCE + 50, rc.top + 50, text, wcslen(text));
    DeleteObject(font);

    return;
}

void CreateBean()
{
    int rand_x = (isStandardWidth ? (GAME_WINDOW_WIDTH / 20) : ((rc.right - BOUNDARY_RIGHT_DISTANCE) / 20));
    int rand_y = (isStandardHeight ? (GAME_WINDOW_HEIGTH / 20) : ((rc.bottom - BOUNDARY_DISTANCE * 2) / 20));

    int x = rand() % (rand_x - 2) + 1;
    int y = rand() % (rand_y - 2) + 1;

    // 判断坐标
    while (1) {
        while (x == bean.location_.x_) {
            x = rand() % (rand_x - 2) + 1;
        }

        while (y == bean.location_.y_) {
            y = rand() % (rand_y - 2) + 1;
        }

        for (auto itor = snake_list.cbegin(); itor != snake_list.cend(); ++itor) {
            if ((x == (*itor).location_.x_) && (y == (*itor).location_.y_)) {
                x = rand() % (rand_x - 2) + 1;
                y = rand() % (rand_y - 2) + 1;
            }
        }

        if ((x != bean.location_.x_) && (y != bean.location_.y_)) {
            break;
        }
    }

    bean.location_.x_ = x;
    bean.location_.y_ = y;

    return;
}

void CreateSnake(HWND hwnd)
{
    HDC hdc = GetDC(hwnd);

    int rand_x = (isStandardWidth ? (GAME_WINDOW_WIDTH / 20) : ((rc.right - BOUNDARY_RIGHT_DISTANCE) / 20));
    int rand_y = (isStandardHeight ? (GAME_WINDOW_HEIGTH / 20) : ((rc.bottom - BOUNDARY_DISTANCE * 2) / 20));
    int x = rand() % (rand_x / 3 * 2);
    while ((x - 3) <= 0) {
        x = rand() % (rand_x / 3 * 2);
    }
    int y = rand() % (rand_y / 3 * 2);
    while ((y - 3) <= 0) {
        y = rand() % (rand_y / 3 * 2);
    }
    int i = 0;
    while (i < INIT_SNAKE_LENGTH) {
        ++i;
        snake_list.push_back(Snake((x - i), y));
    }
    bean.location_.x_ = x;
    bean.location_.y_ = y;

    ReleaseDC(hwnd, hdc);

    return;
}

bool SnakeMove()
{
    if (!JudgeSnakeTouchBody()) {
        return false;
    }

    switch (direction) {
    case dir::UP:
    {
        if ((((snake_list.front().location_.y_) * SIDE_LENGTH) + BOUNDARY_DISTANCE) <= (UINT32)(rc.top + BOUNDARY_DISTANCE)) {
            return false;
        }
        Snake snake = snake_list.front();
        snake_list.pop_back();
        snake_list.push_front(Snake(snake.location_.x_, snake.location_.y_ - 1));
    }
    break;

    case dir::DOWN:
    {
        if ((((snake_list.front().location_.y_ + 1) * SIDE_LENGTH) + BOUNDARY_DISTANCE) >=
                (isStandardHeight ? (UINT32)(rc.top + BOUNDARY_DISTANCE + GAME_WINDOW_HEIGTH) :
                                    (UINT32)(rc.bottom - BOUNDARY_DISTANCE))) {
            return false;
        }
        Snake snake = snake_list.front();
        snake_list.pop_back();
        snake_list.push_front(Snake(snake.location_.x_, snake.location_.y_ + 1));
    }

    break;

    case dir::LEFT:
    {
        if ((((snake_list.front().location_.x_) * SIDE_LENGTH) + BOUNDARY_DISTANCE) <= (UINT32)(rc.left + BOUNDARY_DISTANCE)) {
            return false;
        }
        Snake snake = snake_list.front();
        snake_list.pop_back();
        snake_list.push_front(Snake(snake.location_.x_ - 1, snake.location_.y_));
    }

    break;

    case dir::RIGHT:
    {
        if ((((snake_list.front().location_.x_ + 1) * SIDE_LENGTH) + BOUNDARY_DISTANCE) >=
                (isStandardWidth ? (UINT32)(rc.left + BOUNDARY_DISTANCE + GAME_WINDOW_WIDTH) :
                                    (UINT32)(rc.right - BOUNDARY_RIGHT_DISTANCE))) {
            return false;
        }
        Snake snake = snake_list.front();
        snake_list.pop_back();
        snake_list.push_front(Snake(snake.location_.x_ + 1, snake.location_.y_));
    }
    break;

    default:
        break;
    }

    return true;
}

void ShowSnake(HDC hdc)
{
    HBRUSH hr = CreateSolidBrush(RGB(0, 255, 0));
    HBRUSH old_brush = (HBRUSH)SelectObject(hdc, hr);

    for (auto itor = snake_list.cbegin(); itor != snake_list.cend(); ++itor) {
        Rectangle(hdc, BOUNDARY_DISTANCE + (*itor).location_.x_ * SIDE_LENGTH, BOUNDARY_DISTANCE + (*itor).location_.y_ * SIDE_LENGTH,
            BOUNDARY_DISTANCE + ((*itor).location_.x_ + 1) * SIDE_LENGTH, BOUNDARY_DISTANCE + ((*itor).location_.y_ + 1) * SIDE_LENGTH);
    }

    SelectObject(hdc, old_brush);

    DeleteObject(hr);
    DeleteObject(old_brush);

    return;
}

void ShowBean(HDC hdc)
{
    HPEN hp = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
    HPEN old_pen = (HPEN)SelectObject(hdc, hp);

    HBRUSH hr = CreateSolidBrush(RGB(0, 255, 0));
    HBRUSH old_brush = (HBRUSH)SelectObject(hdc, hr);

    Ellipse(hdc, BOUNDARY_DISTANCE + bean.location_.x_ * SIDE_LENGTH + 1, BOUNDARY_DISTANCE + bean.location_.y_ * SIDE_LENGTH + 1,
        BOUNDARY_DISTANCE + (bean.location_.x_ + 1) * SIDE_LENGTH - 1, BOUNDARY_DISTANCE + (bean.location_.y_ + 1) * SIDE_LENGTH - 1);

    SelectObject(hdc, old_brush);
    SelectObject(hdc, old_pen);

    DeleteObject(hr);
    DeleteObject(old_brush);
    DeleteObject(hp);
    DeleteObject(old_pen);

    return;
}

bool JudgeEatBean()
{
    Snake my_first = snake_list.front();
    int x = my_first.location_.x_;
    int y = my_first.location_.y_;

    if ((x == bean.location_.x_) && (y == bean.location_.y_)) {
        return true;
    }

    return false;
}

void AddSnakeLength()
{
    Snake my_last = snake_list.back();
    int x = my_last.location_.x_;
    int y = my_last.location_.y_;
    switch (direction) {
    case dir::UP:
        snake_list.push_back(Snake(x, y + 1));
        break;

    case dir::DOWN:
        snake_list.push_back(Snake(x, y - 1));
        break;

    case dir::LEFT:
        snake_list.push_back(Snake(x + 1, y));
        break;

    case dir::RIGHT:
        snake_list.push_back(Snake(x - 1, y));
        break;

    default:
        break;
    }

    return;
}

bool JudgeSnakeTouchBody()
{
    Snake my_first = snake_list.front();
    int x = my_first.location_.x_;
    int y = my_first.location_.y_;

    auto itor = ++snake_list.cbegin();
    for (; itor != snake_list.cend(); ++itor) {
        if (((*itor).location_.x_ == x) && ((*itor).location_.y_ == y)) {
            return false;
        }
    }
    return true;
}
