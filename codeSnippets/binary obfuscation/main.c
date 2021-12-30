#include <stdio.h>

#define HIDE_LETTER(a)   (a) + 0x50
#define UNHIDE_STRING(str)  do { char * ptr = str ; while (*ptr) *ptr++ -= 0x50; } while(0)
#define HIDE_STRING(str)  do {char * ptr = str ; while (*ptr) *ptr++ += 0x50;} while(0)

char str1[] = { HIDE_LETTER('s') , HIDE_LETTER('e') , HIDE_LETTER('c') , HIDE_LETTER('r') , HIDE_LETTER('e')  , HIDE_LETTER('t') , HIDE_LETTER(' ') , HIDE_LETTER('p') , HIDE_LETTER('a') , HIDE_LETTER('s'),
                HIDE_LETTER('s') ,HIDE_LETTER('w') ,HIDE_LETTER('o') ,HIDE_LETTER('r') ,HIDE_LETTER('d'),'\0' }; 
				
int main()
{   // store the "secret password" as mangled byte array in binary
        

        UNHIDE_STRING(str1);  // unmangle the string in-place
        printf("Here goes the secret we hide: %s", str1);
        HIDE_STRING(str1);  //mangle back

    return 0;
}