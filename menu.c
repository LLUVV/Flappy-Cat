#include<windows.h>
#include<stdlib.h>
#include<mmsystem.h>
#include"audio.h"
#include"console_draw3.h"
#include"font.h"
#include"kb_input2.h"
#define VERTICAL_SPACE  10 //點點
#define CONSTANT_X 80     //點點的X
#define CONSTANT_Y 27     //點點初始y
#define SCREEN_X 250   //整個螢幕
#define SCREEN_Y 75
extern music_on;
extern Audio audio[3];
int menu(void)
{
    int i, j,flag=1,mainkeep=1;
    Font *large_font = read_font("font.txt");
    pauseAudio(&audio[1]);
    if(music_on == 1)
    {
        pauseAudio(&audio[2]);
        pauseAudio(&audio[1]);
        restartAudio(&audio[0]);
    }
    else
        pauseAudio(&audio[0]);
    while(mainkeep)
    {
        clearScreen();
        for(i = 0; i < SCREEN_X; i++)
        {
            for(j = 0; j < SCREEN_Y; j++)
                putString(i, j, " ", 0,15);
        }

        mainkeep = (mainkeep+1)%2;
        putStringLarge(large_font, CONSTANT_X, 15, "FLAPPY CAT", 0);
        putString(65,20,"                                                                                                        ",15, 0);
        putStringLarge(large_font, CONSTANT_X, 25, "Start", 0);
        putStringLarge(large_font, CONSTANT_X, 35, "Options", 0);
        putStringLarge(large_font, CONSTANT_X, 45, "Developers", 0);
        putStringLarge(large_font, CONSTANT_X, 55, "Exit", 0);
        putString(CONSTANT_X-5,CONSTANT_Y,">>>>",0,15);
        drawCmdWindow();

        initializeKeyInput();
        i=CONSTANT_Y;
        char ch;

        while(flag)
        {
            if(waitForKeyDown(0.2))
            {
                ch = getKeyEventVirtual();
                putString(CONSTANT_X-5,i,"    ",0,15);
                switch(ch)
                {
                    case VK_DOWN:
                        if(i+VERTICAL_SPACE<67)
                        {
                            putString(CONSTANT_X-5, i+VERTICAL_SPACE, ">>>>", 0, 15);
                            drawCmdWindow();
                            i+=VERTICAL_SPACE;
                        }
                        else
                        {
                            putString(CONSTANT_X-5, i, ">>>>", 0, 15);
                            drawCmdWindow();
                        }
                        break;

                    case VK_UP:
                        if(i-VERTICAL_SPACE>19)
                        {Font *large_font = read_font("font.txt");
                            putString(CONSTANT_X-5,i-VERTICAL_SPACE,">>>>",0,15);
                            drawCmdWindow();
                            i-=VERTICAL_SPACE;

                        }
                        else
                        {
                            putString(CONSTANT_X-5, i, ">>>>", 0, 15);
                            drawCmdWindow();
                        }
                        break;
                    case VK_RETURN:
                        flag = 0;
                        break;


                }
            }
        }
        mainkeep = 0;

    }
    return i;
}
