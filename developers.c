#include<windows.h>
#include<stdlib.h>
#include<mmsystem.h>
#include"audio.h"
#include"console_draw3.h"
#include"font.h"
#include"kb_input2.h"
#define SCREEN_X 250   //¾ã­Ó¿Ã¹õ
#define SCREEN_Y 75
extern music_on;
extern Audio audio[3];
int Developers(void)
{
    int i,j;
    char ch;
    clearScreen();
    for(i = 0; i < SCREEN_X; i++)
    {
        for(j = 0; j < SCREEN_Y; j++)
            putString(i, j, " ", 0,15);
    }
    Font *large_font = read_font("font.txt");
    putStringLarge(large_font, 85, 20, "_ Kevin _", 0);
    putStringLarge(large_font, 85, 30, "_ JIMBO _", 0);
    putStringLarge(large_font, 85, 40, "_ IRENE _", 0);
    drawCmdWindow();
    while(1)
    {
        initializeKeyInput();
        ch = getKeyEventVirtual();
        if(ch==VK_LEFT)
        {
            pauseAudio(&audio[1]);
            break;
        }
    }
    return 1;
}
