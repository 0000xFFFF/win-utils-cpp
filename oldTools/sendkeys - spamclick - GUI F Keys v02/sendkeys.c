#include <stdbool.h>
#include <windows.h>
#include "vk.h"
#include "sendkeys.h"

void send_vk_keyboard(WORD vkey, KB flags) {
	
	// SHIFT
	INPUT shift; ZeroMemory(&shift, sizeof(shift));
	INPUT ctrl;  ZeroMemory(&ctrl,  sizeof(ctrl));
	INPUT alt;   ZeroMemory(&alt,   sizeof(alt));
	INPUT win;   ZeroMemory(&win,   sizeof(win));
	
	if (flags & SHIFT) {
		shift.type = INPUT_KEYBOARD;
		shift.ki.wScan = MapVirtualKey(VK_LSHIFT, MAPVK_VK_TO_VSC);
		shift.ki.time = 0;
		shift.ki.dwExtraInfo = 0;
		shift.ki.wVk = VK_LSHIFT;
		shift.ki.dwFlags = 0; // KEYEVENTF_KEYDOWN existn't
		SendInput(1, &shift, sizeof(INPUT));
	}
	
	if (flags & CTRL) {
		ctrl.type = INPUT_KEYBOARD;
		ctrl.ki.wScan = MapVirtualKey(VK_LCONTROL, MAPVK_VK_TO_VSC);
		ctrl.ki.time = 0;
		ctrl.ki.dwExtraInfo = 0;
		ctrl.ki.wVk = VK_LCONTROL;
		ctrl.ki.dwFlags = 0; // KEYEVENTF_KEYDOWN existn't
		SendInput(1, &ctrl, sizeof(INPUT));
	}
	
	if (flags & ALT) {
		alt.type = INPUT_KEYBOARD;
		alt.ki.wScan = MapVirtualKey(VK_LMENU, MAPVK_VK_TO_VSC);
		alt.ki.time = 0;
		alt.ki.dwExtraInfo = 0;
		alt.ki.wVk = VK_LMENU;
		alt.ki.dwFlags = 0; // KEYEVENTF_KEYDOWN existn't
		SendInput(1, &alt, sizeof(INPUT));
	}
	
	if (flags & WIN) {
		win.type = INPUT_KEYBOARD;
		win.ki.wScan = MapVirtualKey(VK_LWIN, MAPVK_VK_TO_VSC);
		win.ki.time = 0;
		win.ki.dwExtraInfo = 0;
		win.ki.wVk = VK_LWIN;
		win.ki.dwFlags = 0; // KEYEVENTF_KEYDOWN existn't
		SendInput(1, &win, sizeof(INPUT));
	}
	
	INPUT input; ZeroMemory(&input, sizeof(input));
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wVk = vkey;
	
	input.ki.dwFlags = 0; // KEYEVENTF_KEYDOWN existn't
	SendInput(1, &input, sizeof(INPUT));
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
	
	if (flags & SHIFT) { shift.ki.dwFlags = KEYEVENTF_KEYUP; SendInput(1, &shift, sizeof(INPUT)); }
	if (flags & CTRL)  { ctrl.ki.dwFlags  = KEYEVENTF_KEYUP; SendInput(1, &ctrl,  sizeof(INPUT)); }
	if (flags & ALT)   { alt.ki.dwFlags   = KEYEVENTF_KEYUP; SendInput(1, &alt,   sizeof(INPUT)); }
	if (flags & WIN)   { win.ki.dwFlags   = KEYEVENTF_KEYUP; SendInput(1, &win,   sizeof(INPUT)); }
}

void send_vk_mouse(DWORD down, DWORD up) {
	INPUT input; ZeroMemory(&input, sizeof(input));
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = down;
	SendInput(1, &input, sizeof(INPUT));
	input.mi.dwFlags = up;
	SendInput(1, &input, sizeof(INPUT));
}

const char* sendkeys_help() {
	return
	"  \\n - ENTER\n"
	"  \\b - BACKSPACE\n"
	"  \\e - ESCAPE\n"
	"  \\a - ALT\n"
	"  \\c - CTRL\n"
	"  \\w - WINDOWS\n"
	"  \\x - DEL\n"
	"\n"
	"  \\t - ALT + F4\n"
	"  \\h - WIN + D\n"
	"  \\r - WIN + R\n"
	"\n"
	"  \\1 - LMB\n"
	"  \\2 - MMB\n"
	"  \\3 - RMB\n"
	"\n"
	"  \\A - CTRL + A\n"
	"  \\C - CTRL + C\n"
	"  \\V - CTRL + V\n"
	"\n"
	"  \\u - PAGE UP\n"
	"  \\d - PAGE DOWN\n"
	"\n"
	"  \\^ - up arrow\n"
	"  \\v - down arrow\n"
	"  \\< - left arrow\n"
	"  \\> - right arrow\n"
	;
}

int sendkeys(const char* str) {
	
	bool mod = false;
	for (unsigned int i = 0; i < strlen(str); i++) {
		
		if (mod) {
			mod = false;
			switch(str[i]) {
				case '\\': send_vk_keyboard(VK_OEM_5, NORMAL); break;
				
				case 'n': send_vk_keyboard(VK_RETURN,   NORMAL); break; // enter
				case 'b': send_vk_keyboard(VK_BACK,     NORMAL); break; // backspace
				case 'e': send_vk_keyboard(VK_ESCAPE,   NORMAL); break; // escape
				case 'a': send_vk_keyboard(VK_LMENU,    NORMAL); break; // ALT
				case 'c': send_vk_keyboard(VK_LCONTROL, NORMAL); break; // CTRL
				case 'w': send_vk_keyboard(VK_LWIN,     NORMAL); break; // WIN / MOD
				case 'x': send_vk_keyboard(VK_DELETE,   NORMAL); break; // DEL
				
				case 't': send_vk_keyboard(VK_F4,    ALT); break; // ALT + F4
				case 'h': send_vk_keyboard(VK_KEY_D, WIN); break; // WIN + D
				case 'r': send_vk_keyboard(VK_KEY_R, WIN); break; // WIN + R
				
				case '1': send_vk_mouse(MOUSEEVENTF_LEFTDOWN,   MOUSEEVENTF_LEFTUP);   break; // LMB
				case '2': send_vk_mouse(MOUSEEVENTF_MIDDLEDOWN, MOUSEEVENTF_MIDDLEUP); break; // MMB
				case '3': send_vk_mouse(MOUSEEVENTF_RIGHTDOWN,  MOUSEEVENTF_RIGHTUP);  break; // RMB
				
				case 'A': send_vk_keyboard(VK_KEY_A, CTRL); break; // CTRL + A
				case 'C': send_vk_keyboard(VK_KEY_C, CTRL); break; // CTRL + C
				case 'V': send_vk_keyboard(VK_KEY_V, CTRL); break; // CTRL + V
				
				case 'u': send_vk_keyboard(VK_PRIOR, NORMAL); break; // PAGE UP
				case 'd': send_vk_keyboard(VK_NEXT,  NORMAL);  break; // PAGE DOWN
				
				case '^': send_vk_keyboard(VK_UP,    NORMAL);    break; // up arrow
				case 'v': send_vk_keyboard(VK_DOWN,  NORMAL);  break; // down arrow
				case '<': send_vk_keyboard(VK_LEFT,  NORMAL);  break; // left arrow
				case '>': send_vk_keyboard(VK_RIGHT, NORMAL); break; // right arrow
				
				/// add more : https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-mouse_event
				/// TODO: add wheel and more clicks
				/// will add more stuff...
			}
			continue;
		}
		
		switch(str[i]) {
			
			case -1: break;
			case '\\': mod = true; continue; break;
			
			case ' ': send_vk_keyboard(VK_SPACE, NORMAL); break;
			
			case 'a': send_vk_keyboard(VK_KEY_A, NORMAL); break;
			case 'b': send_vk_keyboard(VK_KEY_B, NORMAL); break;
			case 'c': send_vk_keyboard(VK_KEY_C, NORMAL); break;
			case 'd': send_vk_keyboard(VK_KEY_D, NORMAL); break;
			case 'e': send_vk_keyboard(VK_KEY_E, NORMAL); break;
			case 'f': send_vk_keyboard(VK_KEY_F, NORMAL); break;
			case 'g': send_vk_keyboard(VK_KEY_G, NORMAL); break;
			case 'h': send_vk_keyboard(VK_KEY_H, NORMAL); break;
			case 'i': send_vk_keyboard(VK_KEY_I, NORMAL); break;
			case 'j': send_vk_keyboard(VK_KEY_J, NORMAL); break;
			case 'k': send_vk_keyboard(VK_KEY_K, NORMAL); break;
			case 'l': send_vk_keyboard(VK_KEY_L, NORMAL); break;
			case 'm': send_vk_keyboard(VK_KEY_M, NORMAL); break;
			case 'n': send_vk_keyboard(VK_KEY_N, NORMAL); break;
			case 'o': send_vk_keyboard(VK_KEY_O, NORMAL); break;
			case 'p': send_vk_keyboard(VK_KEY_P, NORMAL); break;
			case 'q': send_vk_keyboard(VK_KEY_Q, NORMAL); break;
			case 'r': send_vk_keyboard(VK_KEY_R, NORMAL); break;
			case 's': send_vk_keyboard(VK_KEY_S, NORMAL); break;
			case 't': send_vk_keyboard(VK_KEY_T, NORMAL); break;
			case 'u': send_vk_keyboard(VK_KEY_U, NORMAL); break;
			case 'v': send_vk_keyboard(VK_KEY_V, NORMAL); break;
			case 'w': send_vk_keyboard(VK_KEY_W, NORMAL); break;
			case 'x': send_vk_keyboard(VK_KEY_X, NORMAL); break;
			case 'y': send_vk_keyboard(VK_KEY_Y, NORMAL); break;
			case 'z': send_vk_keyboard(VK_KEY_Z, NORMAL); break;
			
			case 'A': send_vk_keyboard(VK_KEY_A, SHIFT); break;
			case 'B': send_vk_keyboard(VK_KEY_B, SHIFT); break;
			case 'C': send_vk_keyboard(VK_KEY_C, SHIFT); break;
			case 'D': send_vk_keyboard(VK_KEY_D, SHIFT); break;
			case 'E': send_vk_keyboard(VK_KEY_E, SHIFT); break;
			case 'F': send_vk_keyboard(VK_KEY_F, SHIFT); break;
			case 'G': send_vk_keyboard(VK_KEY_G, SHIFT); break;
			case 'H': send_vk_keyboard(VK_KEY_H, SHIFT); break;
			case 'I': send_vk_keyboard(VK_KEY_I, SHIFT); break;
			case 'J': send_vk_keyboard(VK_KEY_J, SHIFT); break;
			case 'K': send_vk_keyboard(VK_KEY_K, SHIFT); break;
			case 'L': send_vk_keyboard(VK_KEY_L, SHIFT); break;
			case 'M': send_vk_keyboard(VK_KEY_M, SHIFT); break;
			case 'N': send_vk_keyboard(VK_KEY_N, SHIFT); break;
			case 'O': send_vk_keyboard(VK_KEY_O, SHIFT); break;
			case 'P': send_vk_keyboard(VK_KEY_P, SHIFT); break;
			case 'Q': send_vk_keyboard(VK_KEY_Q, SHIFT); break;
			case 'R': send_vk_keyboard(VK_KEY_R, SHIFT); break;
			case 'S': send_vk_keyboard(VK_KEY_S, SHIFT); break;
			case 'T': send_vk_keyboard(VK_KEY_T, SHIFT); break;
			case 'U': send_vk_keyboard(VK_KEY_U, SHIFT); break;
			case 'V': send_vk_keyboard(VK_KEY_V, SHIFT); break;
			case 'W': send_vk_keyboard(VK_KEY_W, SHIFT); break;
			case 'X': send_vk_keyboard(VK_KEY_X, SHIFT); break;
			case 'Y': send_vk_keyboard(VK_KEY_Y, SHIFT); break;
			case 'Z': send_vk_keyboard(VK_KEY_Z, SHIFT); break;
			
			case '0': send_vk_keyboard(VK_KEY_0, NORMAL); break;
			case '1': send_vk_keyboard(VK_KEY_1, NORMAL); break;
			case '2': send_vk_keyboard(VK_KEY_2, NORMAL); break;
			case '3': send_vk_keyboard(VK_KEY_3, NORMAL); break;
			case '4': send_vk_keyboard(VK_KEY_4, NORMAL); break;
			case '5': send_vk_keyboard(VK_KEY_5, NORMAL); break;
			case '6': send_vk_keyboard(VK_KEY_6, NORMAL); break;
			case '7': send_vk_keyboard(VK_KEY_7, NORMAL); break;
			case '8': send_vk_keyboard(VK_KEY_8, NORMAL); break;
			case '9': send_vk_keyboard(VK_KEY_9, NORMAL); break;
			
			case ')': send_vk_keyboard(VK_KEY_0, SHIFT); break;
			case '!': send_vk_keyboard(VK_KEY_1, SHIFT); break;
			case '@': send_vk_keyboard(VK_KEY_2, SHIFT); break;
			case '#': send_vk_keyboard(VK_KEY_3, SHIFT); break;
			case '$': send_vk_keyboard(VK_KEY_4, SHIFT); break;
			case '%': send_vk_keyboard(VK_KEY_5, SHIFT); break;
			case '^': send_vk_keyboard(VK_KEY_6, SHIFT); break;
			case '&': send_vk_keyboard(VK_KEY_7, SHIFT); break;
			case '*': send_vk_keyboard(VK_KEY_8, SHIFT); break;
			case '(': send_vk_keyboard(VK_KEY_9, SHIFT); break;
			
			case ';' : send_vk_keyboard(VK_OEM_1, NORMAL); break;
			case '/' : send_vk_keyboard(VK_OEM_2, NORMAL); break;
			case '`' : send_vk_keyboard(VK_OEM_3, NORMAL); break;
			case '[' : send_vk_keyboard(VK_OEM_4, NORMAL); break;
			//case '\\': send_vk_keyboard(VK_OEM_5, NORMAL); break; // reserved for special mod key
			case ']' : send_vk_keyboard(VK_OEM_6, NORMAL); break;
			case '\'': send_vk_keyboard(VK_OEM_7, NORMAL); break;
			
			case ':': send_vk_keyboard(VK_OEM_1, SHIFT); break;
			case '?': send_vk_keyboard(VK_OEM_2, SHIFT); break;
			case '~': send_vk_keyboard(VK_OEM_3, SHIFT); break;
			case '{': send_vk_keyboard(VK_OEM_4, SHIFT); break;
			case '|': send_vk_keyboard(VK_OEM_5, SHIFT); break;
			case '}': send_vk_keyboard(VK_OEM_6, SHIFT); break;
			case '"': send_vk_keyboard(VK_OEM_7, SHIFT); break;
			
			case '-': send_vk_keyboard(VK_OEM_MINUS, NORMAL); break;
			case '=': send_vk_keyboard(VK_OEM_PLUS, NORMAL);  break;
			
			case '_': send_vk_keyboard(VK_OEM_MINUS, SHIFT); break;
			case '+': send_vk_keyboard(VK_OEM_PLUS,  SHIFT); break;
			
			case ',': send_vk_keyboard(VK_OEM_COMMA, NORMAL); break;
			case '<': send_vk_keyboard(VK_OEM_COMMA, SHIFT);  break;
			
			case '.': send_vk_keyboard(VK_OEM_PERIOD, NORMAL); break;
			case '>': send_vk_keyboard(VK_OEM_PERIOD, SHIFT);  break;
		}
		
		//Sleep(10);
	}
	
	return 0;
}