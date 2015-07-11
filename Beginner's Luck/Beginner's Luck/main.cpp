#include <Windows.h>
#include "resource.h"

//Globals
HWND hwndStatic;
TCHAR* Simple = TEXT("A test");

//int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nShow)
//{
//	MessageBox(NULL, (LPCWSTR)L"Hello World", (LPCWSTR)L"Funky Town", MB_OK);
//	return 0;
//}

void CreateWindowItems(HWND hwnd, HINSTANCE hInst)
{
	hwndStatic = CreateWindow(TEXT("static"), TEXT("This is a test"),
		WS_CHILD | WS_VISIBLE, 150, 30, 400, 200, hwnd, NULL, hInst, NULL);
	return;
}

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CREATE:
			//Empty for now
			break;
		case WM_LBUTTONDOWN:
			//SetWindowText(hwndStatic, (LPCWSTR)L"Left");
			{
				wchar_t szFileName[MAX_PATH];
				HINSTANCE hinstance = GetModuleHandle(NULL);
				GetModuleFileName(hinstance, szFileName, MAX_PATH);
				SetWindowText(hwndStatic, L"Left");
				MessageBox(hwnd, szFileName, L"This program is: ", MB_OK | MB_ICONINFORMATION);
			}
			break;
		case WM_RBUTTONDOWN:
			SetWindowText(hwndStatic, (LPCWSTR)L"Right");
			break;
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

BOOL InitializeWindow(HWND hwnd, HINSTANCE hInst, int cmdShow)
{
	WNDCLASS wc;

	wc.lpfnWndProc = WinProc;
	wc.hInstance = hInst;
	wc.style = CS_BYTEALIGNCLIENT;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = Simple;
	wc.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_TEST));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;

	if (!RegisterClass(&wc))
		MessageBox(hwnd, (LPCWSTR)L"Register Class Failed!", (LPCWSTR)L"Whoopee", MB_OK);

	hwnd = CreateWindow(Simple, Simple, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, HWND_DESKTOP, NULL, hInst, NULL);
		
	if (!hwnd)
	{
		MessageBox(hwnd, (LPCWSTR)L"That don't ring", (LPCWSTR)L"Fantastic", MB_OK);
	}
		
	CreateWindowItems(hwnd, hInst);
	ShowWindow(hwnd, cmdShow);
	UpdateWindow(hwnd);
	return true;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nShow)
{
	HWND hwnd = NULL;
	MSG Msg;

	InitializeWindow(hwnd, hInst, nShow);

	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
	}

	return (int)Msg.wParam;
}