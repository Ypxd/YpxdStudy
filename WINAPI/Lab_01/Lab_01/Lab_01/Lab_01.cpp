﻿// Lab_01.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include <windows.h>
#include "lab_01.h"
#include <iostream>
#define RGB(r, g, b) ((COLORREF)(((BYTE)(r) | ((WORD)(g) << 8)) | ((DWORD)(BYTE)(b)) << 16)))
int rarc = 0;
int garc = 0;
int barc = 255;

int leftmouse = 0;

int rbg = 0;
int gbg = 0;
int bbg = 255;

int xarc1 = 850;
int yarc1 = 175;
int xarc2 = 1050;
int yarc2 = 375;

int zbg = 0;
int zarc = 0;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");

HWND hWnd;
int WINAPI _tWinMain(HINSTANCE This,		 // Дескриптор текущего приложения 
	HINSTANCE Prev, 	// В современных системах всегда 0 
	LPTSTR cmd, 		// Командная строка 
	int mode) 		// Режим отображения окна
{	// Дескриптор главного окна программы 
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
	wc.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(205, 133, 63));

	// Регистрация класса о		кна
	if (!RegisterClass(&wc)) return 0;

	// Создание окна 
	hWnd = CreateWindow(WinName,			// Имя класса окна 
		_T("LAB01_WinApi_Kalashnikov"), 		// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
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

	switch (message)		 // Обработчик сообщений
	{
		case WM_LBUTTONUP:
		{
			leftmouse = 1;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}

		case WM_PAINT:
		{	
			HDC hdc = GetDC(hWnd);
			PAINTSTRUCT ps;
			hdc = BeginPaint(hWnd, &ps);
			if (leftmouse == 1) 
			{
				RECT rect;
				HFONT hFont;
				hFont = CreateFont(28, 0, 450, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
					CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Times New Roman"));
				SelectObject(hdc, hFont);
				SetRect(&rect, 40, 920, 140, 1020);
				SetBkColor(hdc, RGB(205, 133, 63);
				SetTextColor(hdc, RGB(0, 0, 0);
				DrawText(hdc, TEXT("Артем Калашников ИУ5 43-Б "), -1, &rect, DT_NOCLIP);
				DeleteObject(hFont);
				EndPage(hdc);
				break;
			}
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_RBUTTONUP:
		{
			ShowWindow(hWnd, SW_MINIMIZE);
			break;
		}

		case WM_DESTROY:
			PostQuitMessage(0);
			break; 			// Завершение программы 
		default: 			// Обработка сообщения по умолчанию 
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}