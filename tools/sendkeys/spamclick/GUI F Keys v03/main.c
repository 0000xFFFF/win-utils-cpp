#include <stdio.h>
#include <conio.h>
#include <windows.h>

#include "resource.h"
#include "sendkeys.h"

#define WINDOW_W 520
#define WINDOW_H 260
#define WINDOW_MIN_W WINDOW_W
#define WINDOW_MIN_H WINDOW_H
#define WINDOW_MAX_W WINDOW_W
#define WINDOW_MAX_H WINDOW_H

#define controls_count 6
HWND controls[controls_count];
HWND controls_status[controls_count];
HWND controls_counters[4];
HWND controls_customText[2];
HWND controls_buttons[2];
const char* texts_btn[2] = {
	"Help",
	"Reset"
};

const char* texts[controls_count] = {
	"F1    = Left Mouse Click",  // 0
	"F2    = Right Mouse Click", // 1
	"F3    = ",                  // 2
	"F4    = ",                  // 3
	"F5    = Toggle Switch",     // 4
	"F6/F7 = delay(+/-)",        // 5
};

int spamDelay = 3;
BOOL LMB_on = FALSE; unsigned int LMB_clicks = 0;
BOOL RMB_on = FALSE; unsigned int RMB_clicks = 0;
BOOL cu1_on = FALSE; unsigned int cu1_clicks = 0;
BOOL cu2_on = FALSE; unsigned int cu2_clicks = 0;
BOOL gl_toggle = FALSE;

// update status
void updateUI(const unsigned int uiNum) {
	switch (uiNum) {
		case 0: SetWindowText(controls_status[0], LMB_on ? "[+]" : "[ ]"); break;
		case 1: SetWindowText(controls_status[1], RMB_on ? "[+]" : "[ ]"); break;
		case 2: SetWindowText(controls_status[2], cu1_on ? "[+]" : "[ ]"); break;
		case 3: SetWindowText(controls_status[3], cu2_on ? "[+]" : "[ ]"); break;
		
		case 4: SetWindowText(controls_status[4], gl_toggle ? "[+]" : "[ ]"); break;
		case 5: {
			char buff[2];
			sprintf(buff, "%d", spamDelay);
			SetWindowText(controls_status[5], buff);
			break;
		}
		
		case 10: {
			char buff[2];
			sprintf(buff, "%d", LMB_clicks);
			SetWindowText(controls_counters[0], buff);
			break;
		}
		case 11: {
			char buff[2];
			sprintf(buff, "%d", RMB_clicks);
			SetWindowText(controls_counters[1], buff);
			break;
		}
		case 12: {
			char buff[2];
			sprintf(buff, "%d", cu1_clicks);
			SetWindowText(controls_counters[2], buff);
			break;
		}
		case 13: {
			char buff[2];
			sprintf(buff, "%d", cu2_clicks);
			SetWindowText(controls_counters[3], buff);
			break;
		}
	}
}


int clamp(int v, int lo, int hi) {
	return (v < lo) ? lo : (hi < v) ? hi : v;
}

HHOOK keyboardHook;
LRESULT __stdcall KeyboardHookCallback(int nCode, WPARAM wParam, LPARAM lParam) {
	
	#define NUM_KEYDOWN 256
	#define NUM_KEYUP   257
	#define DELAY_MIN 1
	#define DELAY_MAX 9999
	
	KBDLLHOOKSTRUCT* k = (KBDLLHOOKSTRUCT*)lParam;
	if (k != NULL) {
		
		if (wParam == NUM_KEYDOWN) {
			switch (k->vkCode) {
				case VK_F1: if (!gl_toggle) { LMB_on = TRUE; } updateUI(0); return 1; break;
				case VK_F2: if (!gl_toggle) { RMB_on = TRUE; } updateUI(1); return 1; break;
				case VK_F3: if (!gl_toggle) { cu1_on = TRUE; } updateUI(2); return 1; break;
				case VK_F4: if (!gl_toggle) { cu2_on = TRUE; } updateUI(3); return 1; break;
				
				case VK_F5:                                                                               return 1; break;
				case VK_F6: spamDelay--; spamDelay = clamp(spamDelay, DELAY_MIN, DELAY_MAX); updateUI(5); return 1; break;
				case VK_F7: spamDelay++; spamDelay = clamp(spamDelay, DELAY_MIN, DELAY_MAX); updateUI(5); return 1; break;
			}
		}
		
		if (wParam == NUM_KEYUP) {
			switch (k->vkCode) {
				case VK_F1: LMB_on = gl_toggle ? !LMB_on : FALSE; updateUI(0); return 1; break;
				case VK_F2: RMB_on = gl_toggle ? !RMB_on : FALSE; updateUI(1); return 1; break;
				case VK_F3: cu1_on = gl_toggle ? !cu1_on : FALSE; updateUI(2); return 1; break;
				case VK_F4: cu2_on = gl_toggle ? !cu2_on : FALSE; updateUI(3); return 1; break;
				
				case VK_F5: gl_toggle = !gl_toggle; updateUI(4); return 1; break;
				case VK_F6:                                      return 1; break;
				case VK_F7:                                      return 1; break;
			}
		}
	}
	
	return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

void LMB() { send_vk_mouse(MOUSEEVENTF_LEFTDOWN,  MOUSEEVENTF_LEFTUP);  }
void RMB() { send_vk_mouse(MOUSEEVENTF_RIGHTDOWN, MOUSEEVENTF_RIGHTUP); }
void CUS(const int ctrl) {
	int buffs = GetWindowTextLengthA(controls_customText[ctrl]);
	TCHAR buff[buffs];
	GetWindowText(controls_customText[ctrl], buff, buffs+1);
	sendkeys(buff);
}

BOOL isSpamThreadRunning = FALSE;
DWORD WINAPI SpamThread() {
	isSpamThreadRunning = TRUE;
	while (isSpamThreadRunning) {
		if (LMB_on) { LMB_clicks++; LMB();  updateUI(10); }
		if (RMB_on) { RMB_clicks++; RMB();  updateUI(11); }
		if (cu1_on) { cu1_clicks++; CUS(0); updateUI(12); }
		if (cu2_on) { cu2_clicks++; CUS(1); updateUI(13); }
		Sleep(spamDelay);
	}
	return 0;
}

HBRUSH color_fg;
HBRUSH color_bg;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
		
		case WM_CREATE: {
			
			HFONT hFont = CreateFont(24, 0, 0, 0,
				FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS,
				CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
				TEXT("Consolas")
			);
			
			// create controls
			int n = 0;
			for (unsigned int i = 0; i < controls_count; i++) {
				
				// controls
				if (i == 2 || i == 3) {
					controls[i] = CreateWindow(TEXT("static"), TEXT(texts[i]), WS_VISIBLE | WS_CHILD | WS_BORDER, 10,  10+35*n, 95, 30, hwnd, NULL, NULL, NULL);
					SendMessage(controls[i],  WM_SETFONT, (WPARAM)hFont, TRUE);
					
					// 2 custom texts
					controls_customText[i-2] = CreateWindow(
						TEXT("Edit"),
						TEXT(""),
						WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_LEFT,
						110, 10+35*n, 215,  30, hwnd, NULL, NULL, NULL
					);
					SendMessage(controls_customText[i-2],  WM_SETFONT, (WPARAM)hFont, TRUE);
				}
				else {
					controls[i] = CreateWindow(TEXT("static"), TEXT(texts[i]), WS_VISIBLE | WS_CHILD | WS_BORDER, 10,  10+35*n, 315, 30, hwnd, NULL, NULL, NULL);
					SendMessage(controls[i],  WM_SETFONT, (WPARAM)hFont, TRUE);
				}
				
				// status boxes
				controls_status[i] = CreateWindow(TEXT("static"), TEXT(""), WS_VISIBLE | ES_CENTER | WS_CHILD | WS_BORDER, 330, 10+35*n, 60,  30, hwnd, NULL, NULL, NULL);
				SendMessage(controls_status[i], WM_SETFONT, (WPARAM)hFont, TRUE);
				
				// counters
				if (i <= 3)  {
					controls_counters[i] = CreateWindow(TEXT("static"), TEXT(""), WS_VISIBLE | ES_CENTER | WS_CHILD | WS_BORDER, 395, 10+35*n, 110,  30, hwnd, NULL, NULL, NULL);
					SendMessage(controls_counters[i],  WM_SETFONT, (WPARAM)hFont, TRUE);
				}
				
				// buttons
				if (i == 4 || i == 5) {
					controls_buttons[i-4] = CreateWindowEx(0,
						TEXT("button"),
						texts_btn[i-4],
						WS_VISIBLE | WS_CHILD | BS_CENTER | BS_FLAT | BS_OWNERDRAW | WS_BORDER,
						395, 10+35*n, 110, 30, hwnd, (HMENU)(1337 + i - 4), NULL, NULL
					);
					SendMessage(controls_buttons[i-4], WM_SETFONT, (WPARAM)hFont, TRUE);
				}
				
				n++;
			}
			
			// update all controls
			for (int i = 0; i < 15; i++) { updateUI(i); }
			
			break;
		}
		
		case WM_COMMAND: {
			switch (LOWORD(wParam)) {
				
				// Help
				case 1337: MessageBox(hwnd, TEXT(sendkeys_help()), TEXT("Help"), 0); break;
				
				// Clear
				case 1338: {
					spamDelay = 3;
					LMB_on = FALSE; LMB_clicks = 0;
					RMB_on = FALSE; RMB_clicks = 0;
					cu1_on = FALSE; cu1_clicks = 0;
					cu2_on = FALSE; cu2_clicks = 0;
					gl_toggle = FALSE;
					
					// clear text boxes
					for (unsigned int i = 0; i < 2; i++)
					{ SetWindowText(controls_customText[i], ""); }
					
					// update all controls
					for (unsigned int i = 0; i < 15; i++) { updateUI(i); }
					break;
				}
			}
			break;
		}
		
		case WM_DRAWITEM: {
			
			// draw buttons
			if (wParam == 1337 || wParam == 1338) {
				LPDRAWITEMSTRUCT lpDIS = (LPDRAWITEMSTRUCT)lParam;
				SetBkColor(lpDIS->hDC, RGB(10, 10, 10));
				SetTextColor(lpDIS->hDC, RGB(34, 111, 169));
				lpDIS->rcItem.top += 2;
				DrawText(lpDIS->hDC, texts_btn[wParam - 1337], -1, &lpDIS->rcItem, DT_CENTER | DT_SINGLELINE);
				return TRUE;
			}
			break;
		
		}
		
		
		case WM_CTLCOLORBTN: {
			HDC hdc = (HDC)wParam;
			SetBkColor  (hdc, RGB(10, 10, 10));
			SetTextColor(hdc, RGB(34, 111, 169));
			return (INT_PTR)color_bg;
			break;
		}
		
		// static text labels/textboxes
		case WM_CTLCOLORSTATIC: {
			HDC hdc = (HDC)wParam;
			SetBkColor  (hdc, RGB(10, 10, 10));
			SetTextColor(hdc, RGB(34, 111, 169));
			SetBkMode(hdc, TRANSPARENT);
			return (INT_PTR)color_bg;
			break;
		}
		
		// editable textboxes
		case WM_CTLCOLOREDIT: {
			HDC hdc = (HDC)wParam;
			SetBkColor(hdc,   RGB(10, 10, 10));
			SetTextColor(hdc, RGB(34, 111, 169));
			//SetBkMode((HDC)wParam, TRANSPARENT);
			return (INT_PTR)color_bg;
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
		
		/* All other messages (a lot of them) are processed using default procedures */
		default: return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	
	return 0;
}

#define UNUSED(x) (void)(x)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE x1, LPSTR x2, int x3) {
	
	UNUSED(x1);
	UNUSED(x2);
	UNUSED(x3);
	
	// set colors
	color_fg = CreateSolidBrush(RGB(255, 255, 255));
	color_bg = CreateSolidBrush(RGB(10, 10, 10));
    
	WNDCLASSEX wc; // A properties struct of our window
	HWND hwnd;     // A 'HANDLE', hence the H, or a pointer to our window
	MSG msg;       // A temporary location for all messages

	// zero out the struct and set the stuff we want to modify
	memset(&wc, 0, sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; // This is where we will send messages to
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	wc.hbrBackground = color_bg;
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(APPLICATION_ICON), IMAGE_ICON, GetSystemMetrics(SM_CXICON),   GetSystemMetrics(SM_CYICON),   0);
	wc.hIconSm		 = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(APPLICATION_ICON), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0);
	// LoadIcon(NULL, IDI_APPLICATION); // default app icon
	
	// register window
	if(!RegisterClassEx(&wc))
	{ fprintf(stderr, "ERROR: failed to register window\n"); return 1; }
	
	// get desktop rect to center the window on spawn
	RECT rect;
	GetClientRect(GetDesktopWindow(), &rect);
    rect.left = (rect.right/2) - (WINDOW_W/2);
    rect.top = (rect.bottom/2) - (WINDOW_H/2);
	
	// spawn window
	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "WindowClass", "Spam Clicker",
		WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		rect.left, // x
		rect.top,  // y
		WINDOW_W,  // width
		WINDOW_H,  // height
		NULL, NULL, hInstance, NULL
	);

	if (hwnd == NULL) { fprintf(stderr, "ERROR: failed to create window\n"); return 1; }
	
	// hook
	if (!(keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookCallback, NULL, 0)))
	{ fprintf(stderr, "ERROR: failed to install keyboard hook\n"); return 1; }
	
	// create spam thread
	if (!CreateThread(NULL, 0, SpamThread, NULL, 0, NULL))
	{ fprintf(stderr, "ERROR: failed to create spam click thread\n"); return 1; }
	
	// main loop
	while (GetMessage(&msg, NULL, 0, 0)) { TranslateMessage(&msg); DispatchMessage(&msg); }
	
	// stop spam thread
	isSpamThreadRunning = FALSE;
	
	// unhook
	UnhookWindowsHookEx(keyboardHook);
	
	return msg.wParam;
}