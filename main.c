#include"audio.h"
Audio audio[3];
extern music_on;
int die_times=0;
int main(void)
{
    int k,mainstop=1;
    openAudioFile("On_Hold.wav", &audio[0]);
    //openAudioFile("chickennnnn.wav", &audio[1]);

    playAudio(&audio[0]);
    k = 0;
    while(mainstop)
    {

        switch(k)
        {
            case 0:
                k = start();
                break;
            case 1:
                k = menu();
                break;
            case 2:
                k = end();
                break;
            case 27:
                k = game();
                break;
            case 37:
                k = Options();
                break;
            case 47:
                k = Developers();
                break;
            case 57:
                ExitGame();
                mainstop = 0;
                break;
        }
    }
    return;
}


