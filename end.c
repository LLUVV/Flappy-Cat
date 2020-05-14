#include<windows.h>
#include<stdlib.h>
#include<mmsystem.h>
#include"audio.h"
#include"console_draw3.h"
#include"font.h"
#include"kb_input2.h"
#include"image.h"
extern die_times;
extern music_on;
extern Audio audio[3];
extern score[10000];
char bestscore[10000];
extern best;
int i;
int end(void)
{
    die_times++;
    int flag = 0;
    char ch;
    Font *large_font = read_font("font.txt");
//    int flag = 0;
    Image *blood = read_image("blood.pixel", "blood.color");
    Image *chicken = read_image("chicken2.pixel", "chicken2.color");
    //if(music_on == 1)
    //    restartAudio(&audio[0]);
    openAudioFile("chickennnnn.wav", &audio[1]);
    pauseAudio(&audio[2]);
    pauseAudio(&audio[0]);
    if(music_on == 1)
    {
        playAudio(&audio[1]);
        restartAudio(&audio[1]);
        //restartAudio(&audio[2]);
    }
    sprintf(bestscore, "%d", best);
    clearScreen();
    show_image(blood, 0, 0);
    putStringLarge(large_font, 140, 30, "YOU DIED", 15);
    putStringLarge(large_font, 130, 45, "score", 15);
    putStringLarge(large_font, 190, 45,score, 15);
    putStringLarge(large_font, 120, 55,"bestscore", 15);
    putStringLarge(large_font, 200, 55,bestscore, 15);
    //putString(110, 45, "Please press ENTER to Continue", 15, 0);
    drawCmdWindow();
    Sleep(3000);
    while(1)
    {
        clearScreen();


        show_image(blood, 0, 0);
        putStringLarge(large_font, 140, 30, "YOU DIED", 15);
        putString(160, 40, "Please press ENTER to Continue", 15, 0);
        putStringLarge(large_font, 130, 45, "score", 15);
        putStringLarge(large_font, 190, 45,score, 15);
        putStringLarge(large_font, 120, 55,"bestscore", 15);
        putStringLarge(large_font, 200, 55,bestscore, 15);

        flag = (flag+1)%2;
        //putString(120, 45, "Please press ENTER to Continue", 15, 0);

        if(flag==0)
        {
            show_image(chicken, 30, 10);

        }

        else
        {
            show_image(blood, 0, 0);
            putStringLarge(large_font, 130, 30, "YOU DIED", 15);
            putString(150, 40, "Please press ENTER to Continue", 15, 0);
            putStringLarge(large_font, 120, 45, "score", 15);
            putStringLarge(large_font, 180, 45,score, 15);
            putStringLarge(large_font, 110, 55,"bestscore", 15);
            putStringLarge(large_font, 190, 55,bestscore, 15);


        }
        drawCmdWindow();
        Sleep(300);
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

    }
    destroy_image(chicken);
    destroy_image(blood);
    //pauseAudio(&audio[])
    return 1;
}
