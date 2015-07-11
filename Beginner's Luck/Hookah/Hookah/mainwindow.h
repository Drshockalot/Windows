#ifndef MAINWINDOWH
#define MAINWINDOWH

#include <Windows.h>
#include <tchar.h>

#include <sstream>
#include <stdexcept>
#include <cassert>

typedef std::basic_stringstream<TCHAR> tstringstream;

class CmdAndConquer
{
public:
	CmdAndConquer(HINSTANCE hInstance, int cmdShow, LPCTSTR windowText, HMENU hMenu);
	~CmdAndConquer();
	void WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	static void registerWindowClass(HINSTANCE hInstance);
	static ATOM getClassATOM(void);
	static LPCTSTR getClassName(void);
private:
	HWND hWnd_;
	static ATOM class_atom;
	static LPCTSTR class_name;
	LRESULT CALLBACK actualWndProc(UINT Msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK InitialWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
};

#endif