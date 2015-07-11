#include <Windows.h>
#include "resource.h"
#include <tchar.h>
#include <string>
#include "mainwindow.cpp"

using namespace std;

typedef basic_string<TCHAR> ustring;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int onCreate(const HWND, CREATESTRUCT*);
HWND createEdit(const HWND, const HINSTANCE, DWORD, const RECT&, const int, const ustring&);
inline int errMsg(const ustring&);

WNDCLASS wc = {};

enum {
	IDCE_SINGLELINE = 200,
	IDCE_MULTILINE,
};

HWND hWnd = NULL;

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow)
{
	ustring classname = _T("HumbleBeginnings");
	WNDCLASSEX wcx = { 0 };

	wc.lpfnWndProc = &CmdAndConquer::InitialWndProc;

	wcx.cbSize = sizeof(WNDCLASSEX);
	wcx.lpfnWndProc = WndProc;
	wcx.hInstance = hInstance;
	wcx.hIcon = reinterpret_cast<HICON>(LoadImage(0, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_SHARED));
	wcx.hCursor = reinterpret_cast<HCURSOR>(LoadImage(0, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_SHARED));
	wcx.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1);
	wcx.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wcx.lpszClassName = classname.c_str();
	

	if (!RegisterClassEx(&wcx))
	{
		errMsg(_T("Failed to register window class"));
		return -1;
	}

	int desktopwidth = GetSystemMetrics(SM_CXSCREEN);
	int desktopheight = GetSystemMetrics(SM_CYSCREEN);

	HWND hWnd = CreateWindowEx(0,
							   classname.c_str(),
							   _T("Humble Beginnings"),
							   WS_OVERLAPPEDWINDOW,
							   desktopwidth / 4,
							   desktopheight / 4,
							   desktopwidth / 2,
							   desktopheight / 2,
							   0,
							   0,
							   hInstance,
							   0);


	if (!hWnd)
	{
		errMsg(_T("Failed to create window"));
		return -1;
	}

	ShowWindow(hWnd, cmdShow);
	UpdateWindow(hWnd);

	MSG msg;

	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		return onCreate(hWnd, reinterpret_cast<CREATESTRUCT*>(lParam));
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

inline int errMsg(const ustring& s)
{
	return MessageBox(0, s.c_str(), _T("ERROR"), MB_OK | MB_ICONERROR);
}

int onCreate(const HWND hWnd, CREATESTRUCT *cs)
{
	RECT rc{ 0, 0, 100, 20 };

	createEdit(hWnd, cs->hInstance, ES_MULTILINE | WS_VSCROLL, rc, IDCE_MULTILINE, _T("Multi\r\nline"));

	return 0;
}

HWND createEdit(const HWND hParent, const HINSTANCE hInstance, DWORD style, const RECT& rc, const int id, const ustring& caption)
{
	style |= WS_CHILD | WS_VISIBLE;

	return CreateWindowEx(WS_EX_CLIENTEDGE,
		_T("edit"),
		caption.c_str(),
		style,
		rc.left,
		rc.top,
		rc.right,
		rc.bottom,
		hParent,
		reinterpret_cast<HMENU>(static_cast<int>(id)),
		hInstance,
		0);
}