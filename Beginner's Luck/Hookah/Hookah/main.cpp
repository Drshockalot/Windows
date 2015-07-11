#include <Windows.h>
#include "mainwindow.h"

using namespace std;

LPCTSTR CmdAndConquer::class_name = _T("CmdAndConquer");
ATOM CmdAndConquer::class_atom = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow)
{
	try
	{
		CmdAndConquer::registerWindowClass(hInstance);
		CmdAndConquer cAndC(hInstance, cmdShow, _T("CmdAndConquer"), NULL);

		for (;;)
		{
			MSG msg;

			BOOL bRet = GetMessage(&msg, 0, 0, 0);
			if (bRet == 0)
			{
				return msg.wParam;
			}
			else if (bRet == -1)
			{
				DWORD err_code = GetLastError();
				tstringstream sstr;
				sstr << _T("System Error: ") << err_code;
				MessageBox(NULL, sstr.str().c_str(), _T("Abnormal termination"), MB_OK);
				return -1;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
	catch (std::exception & e)
	{
		tstringstream sstr;
		sstr << _T("Unhandled exception: ") << e.what();
		MessageBox(NULL, sstr.str().c_str(), _T("Abnormal termination"), MB_OK);
	}
	catch (...)
	{
		MessageBox(NULL, _T("Unknown unhandled exception thrown"), _T("Abnormal termination"), MB_OK);
	}

	return -1;
}

