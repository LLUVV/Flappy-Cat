#include<windows.h>
#include<stdlib.h>
#include<mmsystem.h>
#include"console_draw3.h"
#include"font.h"
#include"kb_input2.h"
#define SCREEN_X 270  //¾ã­Ó¿Ã¹õ
#define SCREEN_Y 75
//extern music_on;
//extern Audio audio[3];
void ExitGame(void)
{
    int i,j;
    clearScreen();
    for(i = 0; i < SCREEN_X; i++)
    {
        for(j = 0; j < SCREEN_Y; j++)
            putString(i, j, " ", 0,15);
    }
    Font *large_font = read_font("font.txt");
    putStringLarge(large_font, 50, 30, "Oh NO NO NO NO", 0);
    drawCmdWindow();
    Sleep(1000);
    clearScreen();
    for(i = 0; i < SCREEN_X; i++)
    {
        for(j = 0; j < SCREEN_Y; j++)
            putString(i, j, " ", 0,15);
    }
    putStringLarge(large_font, 60, 30, "Bye Bye", 0);
    drawCmdWindow();
    Sleep(500);
    for(i = 0; i < SCREEN_X; i++)
    {
        for(j = 0; j < SCREEN_Y; j++)
            putString(i, j, " ", 0,0);
    }
    drawCmdWindow();
    return;
}
