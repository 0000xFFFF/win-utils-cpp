#include <iostream>
#include <windows.h>
#include <typeinfo>

// nCode == 0 or HC_ACTION ---> do stuff
// wParam = state, key/mouse down/up
// lParam = struct

// source: https://docs.microsoft.com/en-us/windows/win32/inputdev/mouse-input
// WM_LBUTTONDOWN, WM_LBUTTONUP

int c = 0;

HHOOK keyboardHook;
HHOOK mouseHook;
void handleInput(const int& nCode, const WPARAM& wParam, const LPARAM& lParam, const int& type) {
	
	c++;
	std::cout << ": " << c << std::endl;
	
	std::cout << "TYPE                         = " << (type == 1 ? "KEYBOARD" : "MOUSE") << " CALLBACK" << std::endl;
	
	std::cout << "wParam                       = " << wParam << std::endl;
	std::cout << "lParam                       = " << lParam << std::endl;
	
	KBDLLHOOKSTRUCT* k = (KBDLLHOOKSTRUCT*)lParam;
	if (k != NULL) {
		std::cout << "KBDLLHOOKSTRUCT vkCode       = " << k->vkCode   << std::endl;
		std::cout << "KBDLLHOOKSTRUCT scanCode     = " << k->scanCode << std::endl;
		std::cout << "KBDLLHOOKSTRUCT flags        = " << k->flags    << std::endl;
		std::cout << "KBDLLHOOKSTRUCT time         = " << k->time     << std::endl;
		
		
	}
	
	MOUSEHOOKSTRUCT* m = (MOUSEHOOKSTRUCT*)lParam;
	if (m != NULL) {
		std::cout << "MOUSEHOOKSTRUCT pt.x, pt.y   = " << m->pt.x << ", " << m->pt.y << std::endl;
		std::cout << "MOUSEHOOKSTRUCT hwnd         = " << m->hwnd                    << std::endl;
		std::cout << "MOUSEHOOKSTRUCT wHitTestCode = " << m->wHitTestCode            << std::endl;
		std::cout << "MOUSEHOOKSTRUCT dwExtraInfo  = " << m->dwExtraInfo             << std::endl;
	}
}


LRESULT __stdcall KeyboardHookCallback(int nCode, WPARAM wParam, LPARAM lParam) {
	handleInput(nCode, wParam, lParam, 1);
	return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

LRESULT __stdcall MouseHookCallback(int nCode, WPARAM wParam, LPARAM lParam) {
	handleInput(nCode, wParam, lParam, 2);
	return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	// hooks
	if (!(keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookCallback, NULL, 0)))
	{ fprintf(stderr, "ERROR: failed to install keyboard hook\n"); }
	if (!(mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookCallback, NULL, 0)))
	{ fprintf(stderr, "ERROR: failed to install mouse hook\n");    }
	
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	// unhook
	UnhookWindowsHookEx(keyboardHook);
	UnhookWindowsHookEx(mouseHook);
	
	return msg.wParam;
}