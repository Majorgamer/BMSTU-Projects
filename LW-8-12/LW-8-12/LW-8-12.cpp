// LW-8-12.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "LW-8-12.h"

#define MAX_LOADSTRING 100

struct Rect {
	int left, top, right, bottom;
};

struct RectList {
	Rect r;
	RectList * next;
};

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
RectList * rects = NULL;						// List of rectangles
COLORREF borderColor = RGB(255, 0, 255);		// Color of borders
COLORREF hatchColor = RGB(255, 255, 0);			// Color of hatch

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
BOOL				addRect(int left, int top, int right, int bottom);
BOOL				clearRects();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LW812, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LW812));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LW812));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LW812);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	RECT rect;
	static HDC hDC, hMemDcFrame;
	static HBITMAP hBmpFrame;
	static HPEN borderPen;
	static HBRUSH hatchBrush;
	static int left, top, right, bottom;
	static BOOL isPainting = FALSE;

    switch (message)
    {
	case WM_CREATE:
		hDC = GetDC(hWnd);
		GetClientRect(hWnd, &rect);
		hMemDcFrame = CreateCompatibleDC(hDC); // DC � ������
		hBmpFrame = CreateCompatibleBitmap(hDC, rect.right, rect.bottom);
		SelectObject(hMemDcFrame, hBmpFrame);
		borderPen = CreatePen(PS_DASHDOTDOT, 1, borderColor);
		hatchBrush = CreateHatchBrush(HS_DIAGCROSS, hatchColor);
		break;
	case WM_SIZE:
		hDC = GetDC(hWnd);
		GetClientRect(hWnd, &rect);
		hBmpFrame = CreateCompatibleBitmap(hDC, rect.right, rect.bottom);
		DeleteObject(SelectObject(hMemDcFrame, hBmpFrame));
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case ID_FILE_NEW:
				clearRects();
				InvalidateRect(hWnd, NULL, FALSE);
				break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_LBUTTONDOWN:
		left = right = LOWORD(lParam);
		top = bottom = HIWORD(lParam);
		isPainting = TRUE;
		break;
	case WM_MOUSEMOVE:
		if (wParam & MK_LBUTTON)
		{
			right = LOWORD(lParam);
			bottom = HIWORD(lParam);
			InvalidateRect(hWnd, NULL, FALSE);
		}
		break;
	case WM_LBUTTONUP:
		addRect(left, top, right, bottom);
		isPainting = FALSE;
		break;
	case WM_PAINT:
        {
			hDC = BeginPaint(hWnd, &ps);
			GetClientRect(hWnd, &rect);
			SelectObject(hMemDcFrame, borderPen);
			SelectObject(hMemDcFrame, hatchBrush);
			FillRect(hMemDcFrame, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

			RectList * current = rects;
			while (current != NULL)
			{
				Rectangle(hMemDcFrame, current->r.left, current->r.top, current->r.right, current->r.bottom);
				current = current->next;
			}
			if (isPainting) 
				Rectangle(hMemDcFrame, left, top, right, bottom);
            
			BitBlt(hDC, 0, 0, rect.right, rect.bottom, hMemDcFrame, 0, 0, SRCCOPY);
			EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		DeleteObject(borderPen);
		DeleteObject(hatchBrush);
		ReleaseDC(hWnd, hDC);
		DeleteDC(hMemDcFrame);
        PostQuitMessage(0);
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
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

BOOL addRect(int left, int top, int right, int bottom) {
	if (rects == NULL) {
		rects = (RectList *)malloc(sizeof(RectList));
		rects->r.left = left;
		rects->r.top = top;
		rects->r.right = right;
		rects->r.bottom = bottom;
		rects->next = NULL;
		return TRUE;
	}
	else {
		RectList * last = rects;
		while (last->next != NULL) last = last->next;
		last->next = (RectList *)malloc(sizeof(RectList));
		last->next->r.left = left;
		last->next->r.top = top;
		last->next->r.right = right;
		last->next->r.bottom = bottom;
		last->next->next = NULL;
		return TRUE;
	}
}

BOOL clearRects() {
	RectList * current = rects;
	RectList * next;
	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
	rects = NULL;
	return TRUE;
}