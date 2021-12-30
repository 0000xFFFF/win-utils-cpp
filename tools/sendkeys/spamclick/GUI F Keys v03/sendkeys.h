#ifndef SENDKEY_H
#define SENDKEY_H

typedef enum {
	NORMAL = 0x00,
	SHIFT  = 0x01,
	CTRL   = 0x02,
	WIN    = 0x04,
	ALT    = 0x08,
} KB;

extern void send_vk_keyboard(WORD, KB);
extern void send_vk_mouse(DWORD, DWORD);
extern const char* sendkeys_help();
extern int sendkeys(const char*);


#endif