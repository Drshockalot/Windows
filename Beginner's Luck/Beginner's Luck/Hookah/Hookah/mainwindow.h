#ifndef MAINWINDOW.H
#define MAINWINDOW.H

#include <Windows.h>

class CmdAndConquer
{
public:
	CmdAndConquer(HINSTANCE hInstance, int cmdShow, LPCTSTR windowText, HMENU hMenu);
	~CmdAndConquer();
	void WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK InitialWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
private:

};

#endif