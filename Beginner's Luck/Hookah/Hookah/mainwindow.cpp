#include "mainwindow.h"

CmdAndConquer::CmdAndConquer(HINSTANCE hInstance, int cmdShow, LPCTSTR windowText, HMENU hMenu) : hWnd_(NULL)
{
	assert(HIWORD(class_atom) == 0);
	assert(class_atom);
	if (!class_atom)
		throw std::logic_error("Attempted to create window without registering class");
	HWND hWnd = CreateWindow(reinterpret_cast<LPCTSTR>(class_atom),
							 windowText,
							 WS_OVERLAPPEDWINDOW,
							 CW_USEDEFAULT,
							 CW_USEDEFAULT,
							 CW_USEDEFAULT,
							 CW_USEDEFAULT,
							 NULL,
							 hMenu,
							 hInstance,
							 this);

	if (!hWnd) throw std::runtime_error("Unable to create window");
	assert(hWnd == hWnd_);
	ShowWindow(hWnd_, cmdShow);
}

CmdAndConquer::~CmdAndConquer(){};

void CmdAndConquer::registerWindowClass(HINSTANCE hInstance)
{
	assert(!class_atom);
	if (class_atom)
		throw std::runtime_error("registerWindowClass() called multiple times");

	WNDCLASS wc = {
		CS_HREDRAW | CS_VREDRAW,
		&CmdAndConquer::InitialWndProc,
		0,
		sizeof(CmdAndConquer *),
		hInstance,
		NULL,
		NULL,
		reinterpret_cast<HBRUSH>(COLOR_BACKGROUND),
		NULL,
		CmdAndConquer::class_name
	};

	class_atom = RegisterClass(&wc);
	if (class_atom == 0) throw std::runtime_error("Unable to register window class");
}

ATOM CmdAndConquer::getClassATOM(void)
{
	assert(class_atom != 0);
	if (class_atom == 0) throw std::logic_error("Attempted to get class ATOM without registering class");
	return class_atom;
}

LPCTSTR CmdAndConquer::getClassName(void)
{
	return class_name;
}

LRESULT CALLBACK CmdAndConquer::actualWndProc(UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
	{
		LPCREATESTRUCT create_struct = reinterpret_cast<LPCREATESTRUCT>(lParam);
		void * lpCreateParam = create_struct->lpCreateParams;
		CmdAndConquer * this_window = reinterpret_cast<CmdAndConquer *>(lpCreateParam);
		assert(this_window == this);
		return DefWindowProc(hWnd_, Msg, wParam, lParam);
		break;
	}
	default:
		return DefWindowProc(hWnd_, Msg, wParam, lParam);
	}

	return 0;
}

LRESULT CALLBACK CmdAndConquer::InitialWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if (Msg = WM_NCCREATE)
	{
		LPCREATESTRUCT create_struct = reinterpret_cast<LPCREATESTRUCT>(lParam);
		void * lpCreateParam = create_struct->lpCreateParams;
		CmdAndConquer * this_window = reinterpret_cast<CmdAndConquer *>(lpCreateParam);
		assert(this_window->hWnd_ == 0);

		this_window->hWnd_ = hWnd;
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this_window));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&CmdAndConquer::StaticWndProc));
		return this_window->actualWndProc(Msg, wParam, lParam);
	}

	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

LRESULT CALLBACK CmdAndConquer::StaticWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	LONG_PTR user_data = GetWindowLongPtr(hWnd, GWLP_USERDATA);
	CmdAndConquer * this_window = reinterpret_cast<CmdAndConquer *>(user_data);
	assert(this_window);
	assert(hWnd == this_window->hWnd_);
	return this_window->actualWndProc(Msg, wParam, lParam);
}