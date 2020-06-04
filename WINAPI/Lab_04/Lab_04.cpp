// Lab_04.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Lab_04.h"
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <string>
#include <wchar.h>
#include <time.h>
#include <iostream>
#include <atltime.h>
using namespace std;

#pragma warning(disable:4996)
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName2[] = _T("MainFrame2");

int g = 255;
int b = 0;
int WINAPI _tWinMain(HINSTANCE This,		 // Дескриптор текущего приложения 
	HINSTANCE Prev, 	// В современных системах всегда 0 
	LPTSTR cmd, 		// Командная строка 
	int mode) 		// Режим отображения окна
{
	HWND hWnd;		// Дескриптор главного окна программы 
	MSG msg; 		// Структура для хранения сообщения 
	WNDCLASS wc; 	// Класс окна
	// Определение класса окна 
	wc.hInstance = This;
	wc.lpszClassName = WinName2; 				// Имя класса окна 
	wc.lpfnWndProc = WndProc; 					// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// Стандартный курсор 
	wc.lpszMenuName = NULL; 					// Нет меню 
	wc.cbClsExtra = 0; 						// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 						// Нет дополнительных данных окна 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); 	// Заполнение окна белым цветом 



	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0;

	// Создание окна 
	hWnd = CreateWindow(WinName2,			// Имя класса окна 
		_T("Многопоточность"), 		// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 Размеры окна 
		800, 				// width 
		600, 				// Height 
		HWND_DESKTOP, 				// Дескриптор родительского окна 
		NULL, 						// Нет меню 
		This, 						// Дескриптор приложения 
		NULL); 					// Дополнительной информации нет 
	//SetWindowLong(, GWL_STYLE, WS_CHILD);
	ShowWindow(hWnd, mode); 				// Показать окно
	HMENU WINAPI a;
	HMENU MainMenu = CreateMenu();
	HMENU hPopupMenu = CreatePopupMenu();
	HMENU hPopupMenu2 = CreatePopupMenu();
	AppendMenu(MainMenu, MF_STRING | MF_POPUP, (UINT)hPopupMenu, L"&Поток 1");
	{
		AppendMenu(hPopupMenu, MF_STRING, 1001, L"Первый поток включить");
		AppendMenu(hPopupMenu, MF_SEPARATOR, 0, L"");
		AppendMenu(hPopupMenu, MF_STRING, 1002, L"Первый поток выключить");
	}
	AppendMenu(MainMenu, MF_STRING | MF_POPUP, (UINT)hPopupMenu2, L"&Поток 2");
	{
		AppendMenu(hPopupMenu2, MF_STRING, 1003, L"Второй поток включить");
		AppendMenu(hPopupMenu2, MF_SEPARATOR, 0, L"");
		AppendMenu(hPopupMenu2, MF_STRING, 1004, L"Второй поток выключить");
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
HANDLE hThread2;
HANDLE hThread1;
DWORD WINAPI Thread1(LPVOID t);
DWORD WINAPI Thread2(LPVOID t);

BOOL bFin = true;
BOOL gfin = true;
POINT My_Massiv[3];

// Оконная функция вызывается операционной системой
// и получает сообщения из очереди для данного приложения
int a = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
	default: 			// Обработка сообщения по умолчанию 
		return DefWindowProc(hWnd, message, wParam, lParam);
		
	case WM_TIMER:
	{
		if (a == 0) 
		{
			g = 255;
			b = 0;
			a++;
		}
		else
		{
			if (a == 1)
			g = 0;
			b = 255;
			a--;
		}
		InvalidateRect(hWnd, NULL, TRUE);

	}
	case WM_CREATE:

		SetTimer(hWnd, 1, 250, NULL);
	case WM_COMMAND:
		switch (wParam)
		{
		case 1001:
		{
			gfin = true;
			hThread1 = CreateThread(NULL, 0, Thread1, hWnd, 0, NULL);
			break;

		}
		case 1002:
		{
			TerminateThread(hThread1, 0);
			gfin = FALSE;
			break;
		}
		case 1003:
		{
			bFin = TRUE;
			hThread2 = CreateThread(NULL, 0, Thread2, hWnd, 0, NULL);
			break;
		}
		case 1004:
		{
			TerminateThread(hThread2, 0);
			bFin = FALSE;
			break;

		}
		}
	}
	return 0;
}

DWORD WINAPI Thread1(LPVOID t)
{
	int width = 0;
	int height = 0;
	RECT rect;
	PAINTSTRUCT ps;
	TCHAR szT[30];
	TCHAR buff[300];
	
	while (gfin)
	{
		int date = GetCurrentTime();
		int second = date / 1000;
		int minute = second / 60;
		int hour = minute / 60;
		int realminute = minute - (hour * 60);
		int realsecond = second - (minute * 60);
		GetClientRect(HWND(t), &rect);
		_stprintf(buff, TEXT("%d:%d:%d"), hour, realminute, realsecond);
		HDC hdc1 = GetDC(HWND(t));
		SetTextColor(hdc1, RGB(0,0,0));
		TextOut(hdc1, 10, 10, buff, _tcslen(buff));
		EndPaint(HWND(t), &ps);
	}
	return 0;
}
DWORD WINAPI Thread2(LPVOID t)
{
	int width = 0;
	int height = 0;
	RECT rect;
	PAINTSTRUCT ps;
	My_Massiv[0].x = 600;  My_Massiv[0].y = 10;
	My_Massiv[1].x = 450;  My_Massiv[1].y = 260;
	My_Massiv[2].x = 750;  My_Massiv[2].y = 260;
	HPEN hPen1;
	while (bFin)
	{
		GetWindowRect(HWND(t), &rect);



		HDC hdc = GetDC(HWND(t));
		HBRUSH hBrush;
		if (a == 0) {
			hPen1 = CreatePen(PS_SOLID, 3, RGB(0, g, b));
			SelectObject(hdc, hPen1);
			hBrush = CreateSolidBrush(RGB(0, g, b));
			HBRUSH old = (HBRUSH)SelectObject(hdc, hBrush);
			Polygon(hdc, My_Massiv, 3);
			//a++;
			DeleteObject(hPen1);
			DeleteObject(SelectObject(hdc, hBrush));
		}
		else
			if (a == 1)
			{

				hPen1 = CreatePen(PS_SOLID, 3, RGB(0, g, b));
				SelectObject(hdc, hPen1);
				hBrush = CreateSolidBrush(RGB(0, g, b));
				HBRUSH old = (HBRUSH)SelectObject(hdc, hBrush);
				Polygon(hdc, My_Massiv, 3);
				//a--;
				DeleteObject(hPen1);
				DeleteObject(SelectObject(hdc, hBrush));
			}
		ReleaseDC(HWND(t), hdc);



	}
	return (0);
}