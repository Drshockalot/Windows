#include <Windows.h>

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

using namespace std;

const char *clsName = "Hoorah";
char *title = "Hooch";

bool running = true;

HWND hWnd = NULL;

LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		running = false;
		return 0;
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow)
{
	WNDCLASSEX WndEx;
	MSG msg;

	WndEx.cbSize = sizeof(WndEx);
	WndEx.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	WndEx.lpfnWndProc = (WNDPROC)WndProc;
	WndEx.cbClsExtra = 0;
	WndEx.cbWndExtra = 0;
	WndEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndEx.hbrBackground = NULL;
	WndEx.lpszMenuName = NULL;
	WndEx.lpszClassName = clsName;
	WndEx.hInstance = hInstance;
	WndEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&WndEx))
	{
		MessageBox(NULL, "Failed to register class", "ERROR", MB_OK | MB_ICONERROR);
		return 0;
	}

	if (!(hWnd = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
		clsName,
		title,
		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		460,
		340,
		NULL,
		NULL,
		hInstance,
		NULL)))
	{
		MessageBox(NULL, "Failed to create window", "ERROR", MB_OK | MB_ICONERROR);
		return 0;
	}

	ShowWindow(hWnd, SW_SHOW);

	while (running)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

