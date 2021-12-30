#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <cassert>

#include "resource.h"

#define WINDOW_W 300
#define WINDOW_H 350
#define WINDOW_MIN_W WINDOW_W
#define WINDOW_MIN_H WINDOW_H
#define WINDOW_MAX_W WINDOW_W
#define WINDOW_MAX_H WINDOW_H
	
const int controls_count = 8;
HWND controls[controls_count];
const char* texts[controls_count] = {
	"F1 = LMB     ",
	"F2 = RMB     ",
	"F3 = toggle  ",
	"F4 = delay-- ",
	"F5 = delay++ ",
	"LMB clicks   ",
	"RMB clicks   ",
	"delay        "
};

template<class T>
constexpr const T& clamp(const T& v, const T& lo, const T& hi) {
    assert( !(hi < lo) );
    return (v < lo) ? lo : (hi < v) ? hi : v;
}

int gl_DELAY_SPAM = 3;
int gl_DELAY_STATUS = 100;

bool LMB_on = false;
int LMB_clicks = 0;
bool RMB_on = false;
int RMB_clicks = 0;

bool gl_toggle = false;

void updateUI(const int& uiNum) {
	
	switch (uiNum) {
		case 0: SetWindowText(controls[0], std::string(texts[0] + std::string(LMB_on ?    "[+]" : "[ ]")).c_str()); break;
		case 1: SetWindowText(controls[1], std::string(texts[1] + std::string(RMB_on ?    "[+]" : "[ ]")).c_str()); break;
		case 2: SetWindowText(controls[2], std::string(texts[2] + std::string(gl_toggle ? "[+]" : "[ ]")).c_str()); break;
		
		case 5: SetWindowText(controls[5], std::string(texts[5] + std::to_string(LMB_clicks)).c_str());    break;
		case 6: SetWindowText(controls[6], std::string(texts[6] + std::to_string(RMB_clicks)).c_str());    break;
		case 7: SetWindowText(controls[7], std::string(texts[7] + std::to_string(gl_DELAY_SPAM)).c_str()); break;
	}
}

HHOOK keyboardHook;
LRESULT __stdcall KeyboardHookCallback(int nCode, WPARAM wParam, LPARAM lParam) {
	
	KBDLLHOOKSTRUCT* k = (KBDLLHOOKSTRUCT*)lParam;
	if (k != NULL) {
		
		if (wParam == 256) {
			switch (k->vkCode) {
				case VK_F1: if (!gl_toggle) { LMB_on = true; } updateUI(0);                               return 1; break;
				case VK_F2: if (!gl_toggle) { RMB_on = true; } updateUI(1);                               return 1; break;
				case VK_F3:                                                                               return 1; break;
				case VK_F4: gl_DELAY_SPAM--; gl_DELAY_SPAM = clamp(gl_DELAY_SPAM, 1, 10000); updateUI(7); return 1; break;
				case VK_F5: gl_DELAY_SPAM++; gl_DELAY_SPAM = clamp(gl_DELAY_SPAM, 1, 10000); updateUI(7); return 1; break;
			}
		}
		
		if (wParam == 257) {
			switch (k->vkCode) {
				case VK_F1: LMB_on = gl_toggle ? !LMB_on : false; updateUI(0); return 1; break;
				case VK_F2: RMB_on = gl_toggle ? !RMB_on : false; updateUI(1); return 1; break;
				case VK_F3: gl_toggle = !gl_toggle;               updateUI(2); return 1; break;
				case VK_F4:                                                    return 1; break;
				case VK_F5:                                                    return 1; break;
			}
		}
	}
	
	return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

void send_vk_mouse(DWORD flags) {
	INPUT input;
	ZeroMemory(&input, sizeof(input));
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = flags;
	SendInput(1, &input, sizeof(INPUT));
}
void LMB() {
	send_vk_mouse(MOUSEEVENTF_LEFTDOWN);
	send_vk_mouse(MOUSEEVENTF_LEFTUP);
}
void RMB() {
	send_vk_mouse(MOUSEEVENTF_RIGHTDOWN);
	send_vk_mouse(MOUSEEVENTF_RIGHTUP);
}

bool isSpamThreadRunning = false;
DWORD WINAPI SpamThread(void*) {
	isSpamThreadRunning = true;
	while (isSpamThreadRunning) {
		if (LMB_on) { LMB_clicks++; LMB(); updateUI(5); }
		if (RMB_on) { RMB_clicks++; RMB(); updateUI(6); }
		Sleep(gl_DELAY_SPAM);
	}
	return 0;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
		
		case WM_CREATE: {
			
			HFONT hFont = CreateFont(25, 0, 0, 0,
				FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS,
				CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
				TEXT("Consolas")
			);
			
			// create controls
			int n = 0;
			for (int i = 0; i < controls_count; i++) {
				controls[i] = CreateWindow(TEXT("static"), TEXT(texts[i]), WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 10+35*n++, 260, 30, hwnd, NULL, NULL, NULL);
				SendMessage(controls[i], WM_SETFONT, (WPARAM)hFont, TRUE);
				updateUI(i);
			}
			
			break;
		}
		
		// control color
		case WM_CTLCOLORSTATIC: {
			HDC hdc = (HDC)wParam;
			SetDCPenColor(hdc, RGB(10, 10, 10));
			SetBkColor   (hdc, RGB(10, 10, 10));
			SetTextColor (hdc, RGB(255, 255, 255));
			return (INT_PTR)(HBRUSH)GetStockObject(DC_PEN);
			break;
		}
		
		case WM_GETMINMAXINFO: {
			LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
			lpMMI->ptMinTrackSize.x = WINDOW_MIN_W;
			lpMMI->ptMinTrackSize.y = WINDOW_MIN_H;
			lpMMI->ptMaxTrackSize.x = WINDOW_MAX_W;
			lpMMI->ptMaxTrackSize.y = WINDOW_MAX_H;
			break;
		}
		

		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: PostQuitMessage(0); break;
		
		case WM_COMMAND: {
			switch(LOWORD(wParam)) {		
				
			}
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default: return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    
	WNDCLASSEX wc; // A properties struct of our window
	HWND hwnd;     // A 'HANDLE', hence the H, or a pointer to our window
	MSG msg;       // A temporary location for all messages

	// zero out the struct and set the stuff we want to modify
	memset(&wc, 0, sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; // This is where we will send messages to
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	HBRUSH brush = CreateSolidBrush(RGB(15, 15, 15)); // COLOR FROM RGB
	
	wc.hbrBackground = brush;
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(APPLICATION_ICON), IMAGE_ICON, ::GetSystemMetrics(SM_CXICON),   ::GetSystemMetrics(SM_CYICON),   0);
	wc.hIconSm		 = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(APPLICATION_ICON), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	
	/*
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);
	*/
	
	if(!RegisterClassEx(&wc)) { fprintf(stderr, "ERROR: failed to register window\n"); return 0; }
	
	// get desktop rect to center the window on spawn
	RECT rect;
	GetClientRect(GetDesktopWindow(), &rect);
    rect.left = (rect.right/2) - (WINDOW_W/2);
    rect.top = (rect.bottom/2) - (WINDOW_H/2);
	
	// spawn window
	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "WindowClass", "Spam Clicker", WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		rect.left, // x
		rect.top,  // y
		WINDOW_W,  // width
		WINDOW_H,  // height
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL) { fprintf(stderr, "ERROR: failed to create window\n"); }
	
	// hook
	if (!(keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookCallback, NULL, 0)))
	{ fprintf(stderr, "ERROR: failed to install keyboard hook\n"); }
	
	// create spam thread
	if (!CreateThread(NULL, 0, SpamThread, NULL, 0, NULL)) {  fprintf(stderr, "ERROR: failed to create spam click thread\n"); }
	
	// main loop
	while (GetMessage(&msg, NULL, 0, 0)) { TranslateMessage(&msg); DispatchMessage(&msg); }
	
	// stop spam thread
	isSpamThreadRunning = false;
	
	// unhook
	UnhookWindowsHookEx(keyboardHook);
	
	return msg.wParam;
}