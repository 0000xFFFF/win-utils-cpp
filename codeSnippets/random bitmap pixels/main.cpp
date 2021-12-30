#include <iostream>
#include <windows.h>
#include <cassert>
#include <gdiplus.h>
#include <windows.h>
#include <ctime>
#include <stdio.h>  // printf, scanf, puts, NULL
#include <stdlib.h> // srand, rand
#include <time.h>   // time

int main(int argc, char* argv[]){
	
	int w = 100;
    int h = 100;
	
	if (argc == 3){
		
		w = atoi(argv[1]);
		h = atoi(argv[2]);
	}
	else if (argc == 2){
		
		if (argv[1] == std::string("--help")){
			
			std::cout << "USAGE: " << argv[0] << " <width> <height>" << std::endl;
			return 0;
		}
		
		w = atoi(argv[1]);
		h = atoi(argv[1]);
	}
	
    FILE *f;
    unsigned char *img = NULL;
    int filesize = 54 + 3*w*h;  //w is your image width, h is image height, both int
	
    if(img){ free(img); }
            
    img = (unsigned char *)malloc(3*w*h);
    memset(img,0,sizeof(img));
    int x = 0;
    int y = 0;
    int r = 0;
    int g = 0;
    int b = 0;
	
	for(int j = 0; j < h; j++)  //fill height
	{
		for(int i = 0; i < w; i++) // fill width
		{
			x = i; y = (h - 1) - j;
			// v1    = rand() % 100;         // in the range 0 to 99
			// v2    = rand() % 100 + 1;     // in the range 1 to 100
			// v3    = rand() % 30 + 1985;   // in the range 1985-2014
			// color = rand() % 255 + 1;     // in the range 1 to 255 (for colors)
			// 1   = black
			// 255 = white
			
			// r=g=b= rand() % 255 + 1; //this is only black, gray or white since all RGB colors are set within one random number
			
			img[(x+y*w)*3+2] = (unsigned char)(r);
			img[(x+y*w)*3+1] = (unsigned char)(g);
			img[(x+y*w)*3+0] = (unsigned char)(b);
			
			r = rand() % 255 + 1;
			g = rand() % 255 + 1;
			b = rand() % 255 + 1;
		}
	}

    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
    unsigned char bmppad[3] = {0,0,0};

    bmpfileheader[ 2] = (unsigned char)(filesize    );
    bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
    bmpfileheader[ 4] = (unsigned char)(filesize>>16);
    bmpfileheader[ 5] = (unsigned char)(filesize>>24);

    bmpinfoheader[ 4] = (unsigned char)(w    );
    bmpinfoheader[ 5] = (unsigned char)(w>> 8);
    bmpinfoheader[ 6] = (unsigned char)(w>>16);
    bmpinfoheader[ 7] = (unsigned char)(w>>24);
    bmpinfoheader[ 8] = (unsigned char)(h    );
    bmpinfoheader[ 9] = (unsigned char)(h>> 8);
    bmpinfoheader[10] = (unsigned char)(h>>16);
    bmpinfoheader[11] = (unsigned char)(h>>24);

    f = fopen("img.bmp","wb");
    fwrite(bmpfileheader, 1, 14, f);
    fwrite(bmpinfoheader, 1, 40, f);
    for(int i = 0; i < h; i++){
		
            fwrite(img+(w*(h-i-1)*3),3,w,f);
            fwrite(bmppad,1,(4-(w*3)%4)%4,f);
    }
	
    fclose(f);
	
	return 0;
}
