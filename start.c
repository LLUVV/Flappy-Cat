#include<windows.h>
#include<stdlib.h>
#include<mmsystem.h>
#include"audio.h"
#include"console_draw3.h"
#include"font.h"
#include"kb_input2.h"
#include"image.h"
extern Audio audio[3];
extern music_on;
int start(void)
{
    //int i;
    char ch;
    Font *large_font = read_font("font.txt");
    int flag = 0;
    Image *cat_bp = read_image("caaat.pixel", "caaat.color");
    Image *cat_bp2 = read_image("caaat2.pixel", "caaat2.color");
    if(music_on == 1)
    {
        pauseAudio(&audio[2]);
        pauseAudio(&audio[1]);
        restartAudio(&audio[0]);
    }

    while(1)
    {
        clearScreen();
        //music(1);
        flag = (flag+1)%2;

        if(flag==0)
            show_image(cat_bp, 30, 20);
        else
        {
            show_image(cat_bp2, 30, 20);
            putString(50, 50, "Please press ENTER to Continue", 15, 0);
        }

        putStringLarge(large_font, 25, 40, "Flappy cat", 15);
        drawCmdWindow();
        Sleep(250);

        initializeKeyInput();
        if(waitForKeyDown(0.2))
        {
            ch = getKeyEventVirtual();
            if(ch==VK_RETURN)
            {
                Sleep(150);
                break;
            }
        }
    //destory_image(cat_bp);
    //destroy_image(cat_bp2);
    }
    return 1;
}
