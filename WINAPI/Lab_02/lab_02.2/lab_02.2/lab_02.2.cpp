#include <Windows.h>
#include <tchar.h>
#include <time.h>
#define RGB(r, g, b) ((COLORREF)(((BYTE)(r) | ((WORD)(g) << 8)) | ((DWORD)(BYTE)(b)) << 16))

int colr = 255;
int colg = 255;
int colb = 255;
int leftmouse = 0;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR Win1[] = _T("MainFrame1");
TCHAR Win2[] = _T("MainFrame2");

int WINAPI wWinMain(HINSTANCE This,		 // Дескриптор текущего приложения 
	HINSTANCE Prev, 	// В современных системах всегда 0 
	LPTSTR cmd, 		// Командная строка 
	int mode) 		// Режим отображения окна
{
	static HWND hWnd;		// Дескриптор главного окна программы 
	MSG msg; 		// Структура для хранения сообщения 
	WNDCLASS wc; 	// Класс окна
	// Определение класса окна 
	wc.hInstance = This;
	wc.lpszClassName = Win2; 				// Имя класса окна 
	wc.lpfnWndProc = WndProc; 					// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// Стандартный курсор 
	wc.lpszMenuName = NULL; 					// Нет меню 
	wc.cbClsExtra = 0; 						// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 						// Нет дополнительных данных окна 
	wc.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(colr, colg, colb)));	// Заполнение окна белым цветом 


	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0;

	// Создание окна 
	hWnd = CreateWindow(Win2,			// Имя класса окна 
		_T("Window2"), 		// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 Размеры окна 
		800, 				// width 
		600, 				// Height 
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
	static HWND hWnd2 = NULL;
	static LPCWSTR textt = NULL;

	switch (message)		 // Обработчик сообщений
	{

		case WM_USER + 1:
		{
			MessageBox(hWnd, _T("Дискриптор окна1 получен."), _T("Win2"), MB_OK);
			hWnd2 = FindWindow(Win1, NULL);
			leftmouse = 1;
			InvalidateRect(hWnd, NULL, TRUE);

			return DefWindowProc(hWnd, message, wParam, lParam);

		}
		case WM_USER + 2:
		{
			MessageBox(hWnd, _T("Смообщение о смени цвета."), _T("Win2"), MB_OK);
			srand(time(NULL));
			colr = rand() % 255;
			colb = rand() % 255;
			colg = rand() % 255;
			InvalidateRect(hWnd, NULL, TRUE);
			// return DefWindowProc(hWnd, message, wParam, lParam);
		}

		case WM_PAINT:
		{
			WCHAR textz[9];
			HDC hdc = GetDC(hWnd);
			PAINTSTRUCT ps;
			hdc = BeginPaint(hWnd, &ps);
			if (leftmouse == 1)
			{
				size_t sizehwnd = GetWindowTextLength(hWnd2) + 1;
				char output[20];
				_i64toa_s(int(hWnd2), output, sizehwnd, 16);
				textz[0] = output[0];
				for (int i = 8; i != 0; --i)
				{
					textz[8 - i] = output[8 - i];
				}
				textt = textz;
				TextOut(hdc, 10, 10, textt, 8);

				int t = 1;
				int asd = 2;
				_i64toa_s(int(hWnd2), output, sizehwnd, 16);
				textz[0] = output[0];
				for (int i = 8; i != 0; --i)
				{
					textz[8 - i] = output[8 - i];
				}
				textt = textz;
				TextOut(hdc, 100, 100, textt, 8);
			}
			EndPage(hdc);
			EndPaint(hWnd, &ps);
			break;
		}
		/*case WM_PAINT:
		{
			HDC hdc = GetDC(hWnd);
			PAINTSTRUCT ps;
			hdc = BeginPaint(hWnd, &ps);
			RECT rect;
			SetRect(&rect, 0, 0, 800, 600);
			//SetBkColor(hdc, RGB(0, colg, colb));
			FillRect(hdc, &rect, (HBRUSH)(CreateSolidBrush(RGB(colr, colg, colb))));
			hdc = BeginPaint(hWnd, &ps);
			if (leftmouse == 1)
			{
				TextOut(hdc, 10, 10, hWnd1, 18);
			}
			EndPaint(hWnd, &ps);
			EndPage(hdc);
			break;
		}*/
		case WM_DESTROY:
			PostQuitMessage(0);
			break; 			// Завершение программы 

		default: 			// Обработка сообщения по умолчанию 
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	return 0;
}