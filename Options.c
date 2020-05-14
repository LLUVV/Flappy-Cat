#include<windows.h>
#include<stdlib.h>
#include<mmsystem.h>
#include"audio.h"
#include"console_draw3.h"
#include"font.h"
#include"kb_input2.h"
#define SCREEN_X 250
#define SCREEN_Y 75
int music_on = 1;
extern Audio audio[3];
int Options(void)
{
    char ch;
    int i,j,option_flag=1;
    int on_or_off = 1;
    clearScreen();
    for(i = 0; i < SCREEN_X; i++)
    {
        for(j = 0; j < SCREEN_Y; j++)
            putString(i, j, " ", 0,15);
    }
    Font *large_font = read_font("font.txt");
    putStringLarge(large_font, 50, 25, "MUSIC", 0);
    for(i = 103; i <122 ; i++)
    {
        for(j = 44; j <51 ; j++)
            putString(i, j, " ", 0,0);
    }
    putStringLarge(large_font, 105, 45, "ON", 15);
    putStringLarge(large_font, 135, 45, "OFF", 0);
    putString( 50, 50,"HINT : press backspace to return to menu",0,15);
    saveScreen();
    drawCmdWindow();

    while(option_flag)
    {
        initializeKeyInput();
        ch = getKeyEventVirtual();

        switch(ch)
        {
            case VK_RIGHT :
                for(i = 103; i <122 ; i++)
                {
                    for(j = 44; j <51 ; j++)
                        putString(i, j, " ", 15,15);
                }
                putStringLarge(large_font, 105, 45, "ON", 0);
                for(i = 133; i <159 ; i++)
                {
                    for(j = 44; j <51 ; j++)
                        putString(i, j, " ", 0,0);
                }
                putStringLarge(large_font, 135, 45, "OFF", 15);
                on_or_off = 0;
                drawCmdWindow();
                break;
            case VK_RETURN :
                //music(0);
                //music_on = 0;
                if(on_or_off == 0)
                {
                    music_on = 0;
                    pauseAudio(&audio[0]);
                    pauseAudio(&audio[1]);
                    pauseAudio(&audio[2]);
                }
                else if(on_or_off == 1)
                {
                    music_on = 1;
                    restartAudio(&audio[0]);
                }

                break;
            case VK_LEFT:
                restoreScreen();
                on_or_off = 1;
                drawCmdWindow();
                break;
            case VK_BACK:
                option_flag=0;
                return 1;
                break;
        }
    }
}
