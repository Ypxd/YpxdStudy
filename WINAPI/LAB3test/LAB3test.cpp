// Lab3test.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include <windows.h>
#include "LAB3test.h"
#include <stdlib.h >
#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <atlstr.h>
#define RGB(r, g, b) ((COLORREF)(((BYTE)(r) | ((WORD)(g) << 8)) | ((DWORD)(BYTE)(b)) << 16))



LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int start = 0;
TCHAR WinName[] = _T("MainFrame");

HWND hWnd;
int WINAPI _tWinMain(HINSTANCE This,		 // Дескриптор текущего приложения 
	HINSTANCE Prev, 	// В современных системах всегда 0 
	LPTSTR cmd, 		// Командная строка 
	int mode) 		// Режим отображения окна
{	// Дескриптор главного окна программы 
	HWND hWnd;
	MSG msg; 		// Структура для хранения сообщения 
	WNDCLASS wc; 	// Класс окна
	// Определение класса окна 
	wc.hInstance = This;
	wc.lpszClassName = WinName; 				// Имя класса окна 
	wc.lpfnWndProc = WndProc; 					// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// Стандартный курсор 
	wc.lpszMenuName = NULL; 					// Нет меню 
	wc.cbClsExtra = 0; 						// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 						// Нет дополнительных данных окна 
	//wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); 	// Заполнение окна белым цветом 
	wc.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(255, 255, 255)));

	// Регистрация класса о		кна
	if (!RegisterClass(&wc)) return 0;

	// Создание окна 
	hWnd = CreateWindow(WinName,			// Имя класса окна 
		_T("LAB03_WinApi_Kalashnikov"), 		// Заголовок окна 
		WS_SYSMENU | WS_BORDER, 		// Стиль окна 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 Размеры окна 
		//CW_USEDEFAULT,			// width 
		1280,
		//CW_USEDEFAULT, 			// Height 
		1024,
		HWND_DESKTOP, 				// Дескриптор родительского окна 
		NULL, 						// Нет меню 
		This, 						// Дескриптор приложения 
		NULL); 					// Дополнительной информации нет 

	ShowWindow(hWnd, mode); 				// Показать окно
	HMENU WINAPI a;
	HMENU MainMenu = CreateMenu();
	HMENU hPopupMenu = CreatePopupMenu();

	AppendMenu(MainMenu, MF_STRING | MF_POPUP, (UINT)hPopupMenu, L"&Настройки");
	{
		AppendMenu(hPopupMenu, MF_STRING, 1001, L"Bitmap.bmp");
		AppendMenu(hPopupMenu, MF_STRING, 1002, L"Bitmp1.bmp");
		AppendMenu(hPopupMenu, MF_STRING, 1003, L"Bitmp2.bmp");
		AppendMenu(hPopupMenu, MF_STRING, 1004, L"Image1.bmp");
		AppendMenu(hPopupMenu, MF_STRING, 1005, L"Image2.bmp");
		AppendMenu(hPopupMenu, MF_STRING, 1006, L"Image3.bmp");
		AppendMenu(hPopupMenu, MF_SEPARATOR, 0, L"");

	}
	SetMenu(hWnd, MainMenu);
	// Цикл обработки сообщений 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// Функция трансляции кодов нажатой клавиши 
		DispatchMessage(&msg); 		// Посылает сообщение функции WndProc() 
	}
	return 0;
}

// Оконная функция вызывается операционной системой
// и получает сообщения из очереди для данного приложения

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hDC, hCompatibleDC;
	PAINTSTRUCT PaintStruct;
	HANDLE hBitmap, hOldBitmap;
	RECT Rect;
	BITMAP Bitmap;
	switch (wParam)
	{
	case 1001:
	{
		start = 1;
		InvalidateRect(hWnd, NULL, TRUE);
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	case 1002:
	{
		start = 2;
		InvalidateRect(hWnd, NULL, TRUE);
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	case 1003:
	{
		start = 3;
		InvalidateRect(hWnd, NULL, TRUE);
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	case 1004:
	{
		start = 4;
		InvalidateRect(hWnd, NULL, TRUE);
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	case 1005:
	{
		start = 5;
		InvalidateRect(hWnd, NULL, TRUE);
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	case 1006:
	{
		start = 6;
		InvalidateRect(hWnd, NULL, TRUE);
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	}
	switch (message)		 // Обработчик сообщений
	{
	case WM_PAINT:
		{
			hDC = BeginPaint(hWnd, &PaintStruct);
			if (start == 0)
			{
				hBitmap = LoadImage(NULL, L"Start.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
				hCompatibleDC = CreateCompatibleDC(hDC);
				hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
				GetClientRect(hWnd, &Rect);
				StretchBlt(hDC, 0, 0, Rect.right, Rect.bottom, hCompatibleDC, 0, 0, Bitmap.bmWidth,
					Bitmap.bmHeight, SRCCOPY);
				SelectObject(hCompatibleDC, hOldBitmap);
				DeleteObject(hBitmap);
				DeleteDC(hCompatibleDC);
			}
			if (start == 1) 
			{
				hBitmap = LoadImage(NULL, L"Bitmap.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
				hCompatibleDC = CreateCompatibleDC(hDC);
				hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
				GetClientRect(hWnd, &Rect);
				StretchBlt(hDC, 0, 0, Rect.right, Rect.bottom, hCompatibleDC, 0, 0, Bitmap.bmWidth,
					Bitmap.bmHeight, SRCCOPY);
				SelectObject(hCompatibleDC, hOldBitmap);
				DeleteObject(hBitmap);
				DeleteDC(hCompatibleDC);
			}
			if (start == 2)
			{
				hBitmap = LoadImage(NULL, L"Bitmp1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
				hCompatibleDC = CreateCompatibleDC(hDC);
				hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
				GetClientRect(hWnd, &Rect);
				StretchBlt(hDC, 0, 0, Rect.right, Rect.bottom, hCompatibleDC, 0, 0, Bitmap.bmWidth,
					Bitmap.bmHeight, SRCCOPY);
				SelectObject(hCompatibleDC, hOldBitmap);
				DeleteObject(hBitmap);
				DeleteDC(hCompatibleDC);
			}
			if (start == 3)
			{
				hBitmap = LoadImage(NULL, L"Bitmp2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
				hCompatibleDC = CreateCompatibleDC(hDC);
				hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
				GetClientRect(hWnd, &Rect);
				StretchBlt(hDC, 0, 0, Rect.right, Rect.bottom, hCompatibleDC, 0, 0, Bitmap.bmWidth,
					Bitmap.bmHeight, SRCCOPY);
				SelectObject(hCompatibleDC, hOldBitmap);
				DeleteObject(hBitmap);
				DeleteDC(hCompatibleDC);
			}
			if (start == 4)
			{
				hBitmap = LoadImage(NULL, L"Image1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
				hCompatibleDC = CreateCompatibleDC(hDC);
				hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
				GetClientRect(hWnd, &Rect);
				StretchBlt(hDC, 0, 0, Rect.right, Rect.bottom, hCompatibleDC, 0, 0, Bitmap.bmWidth,
					Bitmap.bmHeight, SRCCOPY);
				SelectObject(hCompatibleDC, hOldBitmap);
				DeleteObject(hBitmap);
				DeleteDC(hCompatibleDC);
			}
			if (start == 5)
			{
				hBitmap = LoadImage(NULL, L"Image2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
				hCompatibleDC = CreateCompatibleDC(hDC);
				hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
				GetClientRect(hWnd, &Rect);
				StretchBlt(hDC, 0, 0, Rect.right, Rect.bottom, hCompatibleDC, 0, 0, Bitmap.bmWidth,
					Bitmap.bmHeight, SRCCOPY);
				SelectObject(hCompatibleDC, hOldBitmap);
				DeleteObject(hBitmap);
				DeleteDC(hCompatibleDC);
			}
			if (start == 6)
			{
				hBitmap = LoadImage(NULL, L"Image3.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
				hCompatibleDC = CreateCompatibleDC(hDC);
				hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
				GetClientRect(hWnd, &Rect);
				StretchBlt(hDC, 0, 0, Rect.right, Rect.bottom, hCompatibleDC, 0, 0, Bitmap.bmWidth,
					Bitmap.bmHeight, SRCCOPY);
				SelectObject(hCompatibleDC, hOldBitmap);
				DeleteObject(hBitmap);
				DeleteDC(hCompatibleDC);
			}
			EndPaint(hWnd, &PaintStruct);
			return 0;
		}

	case WM_DESTROY:
			PostQuitMessage(0);
			break; 			// Завершение программы 
	default: 			// Обработка сообщения по умолчанию 
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}