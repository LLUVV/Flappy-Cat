#include<windows.h>
#include<stdlib.h>
#include<mmsystem.h>
#include<time.h>
#include"audio.h"
#include"console_draw3.h"
#include"font.h"
#include"kb_input2.h"
#include"image.h"
#define SCREEN_X 270   //整個螢幕
#define SCREEN_Y 75
#define GAME_MAIN_X 198
#define GAME_MAIN_Y 69
#define GAME_EDGE_X 200
#define GAME_EDGE_Y 70
#define EDGE_START_X 5
#define EDGE_START_Y 5
#define MAIN_START_X 7
#define MAIN_START_Y 6
#define BIRD_LOCATION_X 10  //左又
#define BIRD_LOCATION_Y 35  //上下
extern music_on;
extern Audio audio[3];
int pause(void)
{
    if(music_on==0)
    {
        pauseAudio(&audio[2]);
        pauseAudio(&audio[0]);
        pauseAudio(&audio[1]);
    }

    int return_or_exit=0;
    double k,i,j,y=43;
    Font *large_font = read_font("font.txt");
    for(k=0;k<20;k++)
    {
        for(i=MAIN_START_X+45;i<GAME_MAIN_X-45;i++)  ///邊框
        {
            for(j=MAIN_START_Y+10;j<GAME_MAIN_Y-10;j++)
            {
                putString(i, j, " ", 7,7);
            }
        }
        for(i=MAIN_START_X+50;i<GAME_MAIN_X-50;i++)  ///內部
        {
            for(j=MAIN_START_Y+12;j<GAME_MAIN_Y-12;j++)
            {
                putString(i, j, " ", 15,15);
            }
        }
        for(i=78;i<113;i++)
        {
            for(j=y+8;j<y+16;j++)
                putString(i,j," ",0,0);
        }
        putStringLarge(large_font,80,y,"PAUSE",0);
        putStringLarge(large_font,80,y+10,"Exit",15);
        putStringLarge(large_font,80,y+20,"Return",0);
        y-=1;
        drawCmdWindow();
        k == 0 ? Sleep(100) : Sleep(20);
    }
    while(1)
    {
        initializeKeyInput();
        char ch;
        ch = getKeyEventVirtual();
        switch(ch)
        {
            case VK_DOWN :
                if(return_or_exit==0)
                {
                    for(i=78;i<113;i++)
                    {
                        for(j=y+8;j<y+18;j++)
                            putString(i,j," ",15,15);
                    }
                    putStringLarge(large_font,80,y+10,"Exit",0);
                    for(i=78;i<128;i++)
                    {
                        for(j=y+18;j<y+26;j++)
                            putString(i,j," ",0,0);
                    }
                    putStringLarge(large_font,80,y+20,"Return",15);
                    drawCmdWindow();
                    return_or_exit=1;
                }
                break;
            case VK_UP :
                if(return_or_exit==1)
                {
                    for(i=78;i<113;i++)
                    {
                        for(j=y+8;j<y+16;j++)
                            putString(i,j," ",0,0);
                    }
                    for(i=78;i<128;i++)
                    {
                        for(j=y+18;j<y+26;j++)
                            putString(i,j," ",15,15);
                    }
                    putStringLarge(large_font,80,y+10,"Exit",15);
                    putStringLarge(large_font,80,y+20,"Return",0);
                    drawCmdWindow();
                    return_or_exit=0;
                }
                break;
            case VK_RETURN :
                return return_or_exit;
        }
    }

}
