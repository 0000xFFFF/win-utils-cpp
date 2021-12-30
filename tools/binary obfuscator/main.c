#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMALLSIZ 256

typedef struct node {
    char* val1;
	char* val2;
    struct node* next;
} node_t;

void push(node_t* head, const char* val1, const char* val2) {
    node_t* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    // add new var
    current->next = (node_t*)malloc(sizeof(node_t));
    current->next->val1 = strdup(val1);
	current->next->val2 = strdup(val2);
    current->next->next = NULL;
}

int str_1n2(const char* str, char* str1, char* str2) {
	int sawSpace = 0;
	int i1 = 0;
	int i2 = 0;
	for (size_t i = 0; i < strlen(str); i++) {
		if (!sawSpace && str[i] == ' ') { sawSpace = 1; continue; }
		if (sawSpace) {
			str2[i2] = str[i];
			i2++;
		}
		else {
			str1[i1] = str[i];
			i1++;
		}
	}
	return 1;
}

void header(node_t* head) {
	
	const char* header_head =
	"// binary obfuscation macros\n"
	"#define HIDE_LETTER(a)   (a) + 0x50\n"
	"#define UNHIDE_STRING(str)  do { char * ptr = str ; while (*ptr) *ptr++ -= 0x50; } while(0)\n"
	"#define HIDE_STRING(str)  do {char * ptr = str ; while (*ptr) *ptr++ += 0x50;} while(0)\n"
	"\n"
	"extern void main_strings();\n"
	;
	
	// print header
	printf("%s\n", header_head);
	
	node_t* current = head->next;
	while (current != NULL) {
		if (current->val1 != NULL && current->val2 != NULL) {
			printf("extern char %s[];\n", current->val1);
		}
		current = current->next;
	}
}

void code(node_t* head) {
	node_t* current = head->next;
	while (current != NULL) {
		if (current->val1 != NULL && current->val2 != NULL) {
			printf("char %s[] = { ", current->val1);
			size_t l = strlen(current->val2);
			for (size_t i = 0; i < l; i++) {
				printf("HIDE_LETTER('%c'), ", current->val2[i]);
			}
			printf("'\\0' };\n");
		}
		current = current->next;
	}
}

void code2(node_t* head) {
	printf("\n// call this in your main function\nvoid main_strings() {\n");
	node_t* current = head->next;
	while (current != NULL) {
		if (current->val1 != NULL && current->val2 != NULL) {
			printf("	UNHIDE_STRING(%s);\n", current->val1);
		}
		current = current->next;
	}
	printf("}");
}

int main(int argc, char** argv) {
	
	// if args use args
	if (argc < 2) {
		printf(
		"USAGE: %s <mode> < fileWithVars.txt\n"
		"  modes:\n"
		"        h - header file\n"
		"        c - c code file\n"
		"\n"
		"example: fileWithVars.txt:\n"
		"SOME_VAR This is the value of some var\n"
		"ANOTHER_VAR More string values\n"
		"\n"
		, argv[0]);
		
		return 0;
	}
	
	// get values
	node_t* head = (node_t*)malloc(sizeof(node_t));
	head->val1 = NULL;
	head->val2 = NULL;
	head->next = NULL;
	
	char buffer[SMALLSIZ];
    while (fgets(buffer, SMALLSIZ-1, stdin)) {
        buffer[strcspn(buffer, "\n")] = 0; // remove newline
		char buf1[SMALLSIZ] = {0};
		char buf2[SMALLSIZ] = {0};
		str_1n2(buffer, buf1, buf2);
		push(head, buf1, buf2);
    }
	
	switch (argv[1][0]) {
		case 'h': header(head); break;
		case 'c': code(head); code2(head); break;
	}
	
	return 0;
}
