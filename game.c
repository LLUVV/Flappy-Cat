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
#define BIRD_LOCATION_Y 35
#define TUBE_X 2  //上下
#define TUBE_SPACE 61 //管子間距
#define NUM_KEYS 9
time_t time_count;
char str[40] = {'\0'},buffer[400];
int cur_tick, last_tick;
double G=0.0;
double i,j,people_y=18,bird_x=BIRD_LOCATION_X,bird_y=BIRD_LOCATION_Y,count;
char ch;
double tube1x=40.0, tube2x=150.0,tube3x=260.0,tube4x=370.0;
double tube_speed_constant= 0.01;
int rand_number1=-20;
int rand_number2=-5;
int rand_number3=3;
int rand_number4=0;
char buffer1[300];
char score[10000];
int best = 0;
extern music_on;
extern Audio audio[3];
extern die_times;
void tube_move(void)
{
    Image *people = read_image("cat.pixel", "cat.color");
    Image *tube = read_image("tube16.pixel", "tube16.color");
    Image *apple = read_image("apple3.pixel", "apple3.color");
    Image *tube_down = read_image("tube17.pixel", "tube17.color");
    int tube_x_move=1;
        for(i=EDGE_START_X;i<GAME_EDGE_X;i++)   ///主畫面邊框
        {
            for(j=EDGE_START_Y;j<GAME_EDGE_Y;j++)
            {
                putString(i, j, " ", 7,7);
            }
        }
        for(i=MAIN_START_X;i<GAME_MAIN_X;i++)  ///主畫面遊戲
        {
            for(j=MAIN_START_Y;j<GAME_MAIN_Y;j++)
            {
                putString(i, j, " ", 15,0);
            }
        }
        if(tube1x>-10 && tube1x<=195)   ///4種水管
        {
            show_image(tube, tube1x, rand_number1);
            show_image(tube_down, tube1x,rand_number1+TUBE_SPACE);
            show_image(apple, 170, 30);
            show_image(people,bird_x,bird_y);
        }
        else if (tube1x<=-10)
        {
            rand_number1=-(rand()%40)+(rand()%5);
            tube1x = tube1x+230;
            //show_image(tube, tube1x, rand_number1);
            //show_image(tube_down, tube1x,rand_number1+TUBE_SPACE);
            show_image(apple, 170, 30);
            show_image(people,bird_x,bird_y);
        }
        if(tube2x>-10 && tube2x<=195)
        {
            show_image(tube, tube2x, rand_number2);
            show_image(tube_down, tube2x,rand_number2+TUBE_SPACE);
            show_image(apple, 170, 30);
            show_image(people,bird_x,bird_y);
        }
        else if(tube2x<=-10)
        {
            rand_number2=-(rand()%10)+(rand()%5);
            tube2x = tube2x+230;
            //show_image(tube, tube2x, rand_number2);
            //show_image(tube_down, tube2x,rand_number2+TUBE_SPACE);
            show_image(apple, 170, 30);
            show_image(people,bird_x,bird_y);
        }

        if(tube3x>-10 && tube3x<=195)
        {
            show_image(tube, tube3x,rand_number3);
            show_image(tube_down, tube3x, rand_number3+TUBE_SPACE);
            show_image(apple, 170, 30);
            show_image(people,bird_x,bird_y);
        }
        else if(tube3x<=-10)
        {
            rand_number3 = -(rand()%30)+(rand()%5);
            tube3x = tube3x+230;
            //show_image(tube, tube3x,rand_number3);
            //show_image(tube_down, tube3x, rand_number3+TUBE_SPACE);
            show_image(apple, 170, 30);
            show_image(people,bird_x,bird_y);
        }
        if(tube4x>-10 && tube4x<=195)
        {
            show_image(tube, tube4x, rand_number4);
            show_image(tube_down, tube4x, rand_number4+TUBE_SPACE);
            show_image(apple, 170, 30);
            show_image(people,bird_x,bird_y);
        }
        else if(tube4x<=-10)
        {
            rand_number4 = -(rand()%20)+(rand()%5);
            tube4x = tube4x+230;
            //show_image(tube, tube4x, rand_number4);
            //show_image(tube_down, tube4x, rand_number4+TUBE_SPACE);
            show_image(apple, 170, 30);
            show_image(people,bird_x,bird_y);
        }  ///水管結束
        cover_game_screen();
        show_image(people,bird_x,bird_y);

        tube_speed_constant += 0.003;
        tube1x -=(0.5+tube_speed_constant),tube2x -=(0.5+tube_speed_constant);
        tube3x -=(0.5+tube_speed_constant),tube4x -=(0.5+tube_speed_constant); ///速度
        return;
}

void cover_game_screen(void)
{
        for(i=5;i<GAME_EDGE_X;i++) ///蓋上面
        {
            for(j=0;j<=EDGE_START_X;j++)
            {
                putString(i, j, " ", 7,7);
            }
        }
        Font *large_font = read_font("font.txt");
        putStringLarge(large_font, 10, 0,"died", 0);
        sprintf(buffer1,"%d",die_times);
        putStringLarge(large_font, 47, 0,buffer1, 12);
        putStringLarge(large_font, 63, 0,"times", 0);
        putStringLarge(large_font, 120, 0,"score ", 0);
        putStringLarge(large_font, 165, 0, score, 0);
        for(i=5;i<GAME_EDGE_X;i++) ///蓋下面
        {
            for(j=69;j<=150;j++)
            {
                putString(i, j, " ", 7,7);
            }
        }
        for(i=0;i<EDGE_START_X+3;i++) ///蓋左邊
        {
            for(j=0;j<=150;j++)
            {
               putString(i, j, " ", 7,7);
            }
        }
        for(i=198;i<205+10;i++) ///蓋右邊
        {
            for(j=0;j<=150;j++)
            {
               putString(i, j, " ", 7,7);
            }
        }
        drawCmdWindow();
        return;
}
int timer(void)
{
    return (clock()/(0.001*CLOCKS_PER_SEC));
}
void JUMPER(void)
{
    Image *people = read_image("human3.pixel", "human3.color");
        G =0 ;
        for(count=30;count>0;count--)  // 往上
        {
            if(bird_y>7)
            {

                for(i=MAIN_START_X;i<GAME_MAIN_X;i++)  ///主畫面遊戲
                {
                    for(j=MAIN_START_Y;j<GAME_MAIN_Y;j++)
                    {
                        putString(i, j, " ", 15,0);
                    }pauseAudio(&audio[0]);
                }
                //if(x<100) x=x+0.2; ///往右
                tube_move();
                G = G+0.033;
                bird_y -=  (1-G);
                show_image(people, bird_x, bird_y);
                drawCmdWindow(); //左右,上下(變大往下
                Sleep(4);
            }
            else
                break;
        }
        /*G = 0.0;
        for(count=100;count>0;count--) //往下
        {
            if(y<=60)
            {
                for(i=MAIN_START_X;i<GAME_MAIN_X;i++)  ///主畫面遊戲
                {
                    for(j=MAIN_START_Y;j<GAME_MAIN_Y;j++)
                    {
                        putString(i, j, " ", 15,0);
                    }
                }
                G = G+0.025;
                y +=  G;
                show_image(people, x, y);
                drawCmdWindow(); //左右,上下(變大往下
                Sleep(5);
            }
            else
                break;
        }*/
}


int game(void)
{
    tube_speed_constant = 0.01;
    people_y=18;
    bird_x=BIRD_LOCATION_X;
    bird_y=BIRD_LOCATION_Y;
    tube1x=40.0, tube2x=100.0,tube3x=160.0,tube4x=220.0;
    rand_number1=-20;
    rand_number2=-5;
    rand_number3=3;
    rand_number4=0;
    Image *tube = read_image("tube3.pixel", "tube3.color");
    Image *tube_down = read_image("tube4.pixel", "tube4.color");
    Image *people = read_image("human3.pixel", "human3.color");
    Font *large_font = read_font("font.txt");
    Image *bluesky = read_image("sky10.pixel", "sky10.color");
    Image *apple = read_image("apple3.pixel", "apple3.color");
    int t=0,t2=0;
    clearScreen();
    srand(time(NULL));
    show_image(bluesky, 0, 0);
    openAudioFile("Vacation_Uke.wav", &audio[2]);
    if(music_on == 1)
    {
        pauseAudio(&audio[0]);
        pauseAudio(&audio[1]);
        playAudio(&audio[2]);
        restartAudio(&audio[2]);
    }

    for(i=EDGE_START_X;i<GAME_EDGE_X;i++)   ///主畫面邊框
    {
        for(j=EDGE_START_Y;j<GAME_EDGE_Y;j++)
        {
            putString(i, j, " ", 7,7);
        }
    }
    for(i=MAIN_START_X;i<GAME_MAIN_X;i++)  ///主畫面遊戲
    {
        for(j=MAIN_START_Y;j<GAME_MAIN_Y;j++)
        {
            putString(i, j, " ", 15,0);
        }
    }
    show_image(tube, 15, 6);
    show_image(tube_down, 15, 45);
    show_image(tube, 90, 0);
    show_image(tube_down, 90, 39);
    show_image(tube, 150, 1);
    show_image(tube_down, 150, 40);
    show_image(tube, 130, 6);
    show_image(tube_down, 130, 45);
    show_image(apple, 170, 30);
    show_image(people, bird_x, bird_y);  //左右 ,上下
    drawCmdWindow();
    initializeKeyInput();
    char ch;
    int k,migi=1;
    int game_play_continue=1;
    int key_down[NUM_KEYS] = {0};
    int key_val[NUM_KEYS] = {VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_O, VK_K, VK_RETURN, VK_SPACE, VK_BACK};
    initializeKeyInput();


    int cur_time, last_time;
    int go_up = 0, go_down = 0, go_left = 0, go_right = 0;
    t2 = clock()/100;

    saveScreen();
    cur_time = last_time = clock();
    while(game_play_continue)
    {
        cur_time = clock();
        t = clock()/100-t2;
        if(t > best)
            best = t;
        sprintf(score, "%d", t);
        if(cur_time - last_time > 30){
            last_time = cur_time;        ///else 會改變一步
            if(go_up && bird_y>=6)bird_y--;
            if(go_right&& bird_x<=180)bird_x++;
            if(go_down && bird_y<=57)bird_y++;
            if(go_left && bird_x>=8)bird_x--;


            clearScreen();
            restoreScreen();
            tube_move();

        }
        for (k=0; k<NUM_KEYS; k++) {
            if(KEY_DOWN(key_val[k]) && !key_down[k]) {
                key_down[k] = 1;
                switch (key_val[k]) {
                    case VK_O:   ///開無敵
                        migi = 0;
                        break;
                    case VK_K:   ///關無敵
                        migi = 1;
                        break;
                    case VK_UP:
                        go_up = 1;
                        break;
                    case VK_DOWN:
                        go_down = 1;
                        break;
                    case VK_LEFT:
                        go_left = 1;
                        break;
                    case VK_RIGHT:
                        go_right = 1;
                        break;
                    case VK_BACK:
//                        saveScreen();
                        if(pause()== 0)
                            return 1;
                        else
                        {
//                            restoreScreen();
//                            drawCmdWindow();
                            t2 = clock()/100-t;
                            if(music_on==1)
                                restartAudio(&audio[2]);
                        }
                        break;
                }
            }
            if(KEY_UP(key_val[k]) && key_down[k]){
                key_down[k] = 0;
                switch (key_val[k]) {
                    case VK_UP:
                        go_up = 0;
                        break;
                    case VK_DOWN:
                        go_down = 0;
                        break;
                    case VK_LEFT:
                        go_left = 0;
                        break;
                    case VK_RIGHT:
                        go_right = 0;
                        break;
                }
            }
        }
        /*if(y<=60)
        {
            if(x<100) x=x+0.2; ///往右
            G = G+0.025;
            y +=  G;
            show_image(people, x, y);
            drawCmdWindow(); //左右,上下(變大往下
            Sleep(5);
        }*/
//        if(waitForKeyDown(0.001))
//        {
//            ch = getKeyEventVirtual();
//            switch(ch)
//            {
//                case VK_O:   ///開無敵
//                    migi = 0;
//                    break;
//                case VK_K:   ///關無敵
//                    migi = 1;
//                    break;
//                case VK_SPACE:
//                    JUMPER();
//                    break;
//                case VK_UP:
//                    if(bird_y>7)bird_y = bird_y-4;
//                    break;
//                case VK_DOWN:
//                    if(bird_y<58)bird_y = bird_y+4;
//                    break;
//                case VK_RIGHT:
//                    if(bird_x<163) bird_x = bird_x+4;
//                    break;
//                case VK_LEFT:
//                    if(bird_x>10) bird_x = bird_x-6;
//                    break;
//                case VK_BACK  :
//                    saveScreen();
//                    if(pause()== 0)
//                        return 1;
//                    else
//                    {
//                        restoreScreen();
//                        drawCmdWindow();
//                        if(music_on==1)
//                            restartAudio(&audio[2]);
//                    }
//                    break;
//
//            }
//        }
//        tube_move();
        if(migi==1)
        {
            if  ((((bird_x>=tube1x-2&&bird_x<=tube1x+10)||(bird_x+10>=tube1x-2&&bird_x+2<=tube1x+20))
              &&((bird_y<rand_number1+49)||(bird_y+5>rand_number1+TUBE_SPACE)))
            ||(((bird_x>=tube2x-2&&bird_x<=tube2x+10)||(bird_x+10>=tube2x-2&&bird_x+2<=tube2x+20))
              &&((bird_y<rand_number2+49)||(bird_y+5>rand_number2+TUBE_SPACE)))
            ||(((bird_x>=tube3x-2&&bird_x<=tube3x+10)||(bird_x+10>=tube3x-2&&bird_x+2<=tube3x+20))
              &&((bird_y<rand_number3+49)||(bird_y+5>rand_number3+TUBE_SPACE)))
            ||(((bird_x>=tube4x-2&&bird_x<=tube4x+10)||(bird_x+10>=tube4x-2&&bird_x+2<=tube4x+20))
              &&((bird_y<rand_number4+49)||(bird_y+5>rand_number4+TUBE_SPACE))))
              {
                  Sleep(250);
                  return 2;
              }
        }

    }
}
