#include "Tetris.h"
#include "Button.h"
#include <iostream>
#include <windows.h>
#include <fstream>
#define SETTINGS_FILE "resources/settings.txt"
#define high_delay 100
#define mid_delay 200
#define low_delay 400

using namespace std;
void init()
{
    IMAGE uibg, gamehead;
    initgraph(938, 809); // 初始化窗口
    loadimage(&uibg, "resources/uibg.jpg", 938, 809);
    putimage(0, 0, &uibg);
    loadimage(&gamehead, "resources/game_head.jpg", 600, 300);
    putimage(169, 10, &gamehead);
}
void printrules(){
    IMAGE rule;
    initgraph(938, 809); // 初始化窗口
    loadimage(&rule, "resources/rules.png", 938, 809);
    putimage(0, 0, &rule);
    while(1){
        if(KEY_DOWN('B')) break;
    }
}
void set_settings(bool& bgmusic,bool& txmusic,int& delaylevel){
    char title1[2][32]={{"ON"},{"OFF"}};
    char title2[3][32]={{"High"},{"Mid"},{"Low"}};
    IMAGE set;
    initgraph(938, 809); // 初始化窗口
    loadimage(&set, "resources/setbg.png", 938, 809);
    putimage(0, 0, &set);
    Button on1(300,230,200,60,title1[0]);
    Button off1(600,230,200,60,title1[1]);
    Button on2(300,400,200,60,title1[0]);
    Button off2(600,400,200,60,title1[1]);
    Button High(300,570,150,60,title2[0]);
    Button Mid(500,570,150,60,title2[1]);
    Button Low(700,570,150,60,title2[2]);

    if(bgmusic) on1.change();
    else off1.change();

    if(txmusic) on2.change();
    else off2.change();

    if(delaylevel==high_delay) High.change();
    else if(delaylevel==mid_delay) Mid.change();
    else Low.change();

    ExMessage msg; // 声明一个消息指针
    while(1){
        if (peekmessage(&msg, EM_MOUSE))
        {
            switch (msg.message)
            {
            case WM_LBUTTONDOWN://检测鼠标点击按钮
                if (msg.x >= 300 && msg.x <= 500  && msg.y >=230 && msg.y <= 290) {
                    if(bgmusic) {}
                    else{
                        bgmusic=1;
                        on1.change();
                        off1.init();
                    }
                }
                if (msg.x >= 600 && msg.x <= 800  && msg.y >=230 && msg.y <= 290) {
                    if(!bgmusic){}
                    else{
                        bgmusic=0;
                        on1.init();
                        off1.change();
                    }
                }
                if (msg.x >= 300 && msg.x <= 500  && msg.y >= 400 && msg.y <= 460) {
                    if(txmusic){}
                    else{
                        txmusic=1;
                        on2.change();
                        off2.init();
                    }
                }
                if (msg.x >= 600 && msg.x <= 800  && msg.y >= 400 && msg.y <= 460) {
                    if(!txmusic){}
                    else{
                        txmusic=0;
                        on2.init();
                        off2.change();
                    }
                }
                if (msg.x >= 300 && msg.x <= 450  && msg.y >= 570 && msg.y <= 630) {
                    delaylevel=high_delay;
                    High.change();
                    Mid.init();
                    Low.init();
                }
                if (msg.x >= 500 && msg.x <= 650  && msg.y >= 570 && msg.y <= 630) {
                    delaylevel=mid_delay;
                    High.init();
                    Mid.change();
                    Low.init();
                }
                if (msg.x >= 700 && msg.x <= 850  && msg.y >= 570 && msg.y <= 630) {
                    delaylevel=low_delay;
                    High.init();
                    Mid.init();
                    Low.change();
                }
                break;
            default:break;
            }
        }
        if(KEY_DOWN('B')) break;
    }

}

void print_highestscore(){
    IMAGE uibg;
    initgraph(938, 809); // 初始化窗口
    loadimage(&uibg, "resources/uibg.jpg", 938, 809);
    putimage(0, 0, &uibg);

    Button(200,200,500,200,(char*)"highestscore");

    int highest=0;
    ifstream file("resources/highestscore.txt");
    file>>highest;

    char highest_char[32];
    string str_highest=to_string(highest);
    strcpy(highest_char,str_highest.c_str());
    Button highestscore(200,500,500,200,highest_char);

    while(1){
        if(KEY_DOWN('B')) break;
    }
}

int main()
{
    bool exitflag=false;
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    init();
    
    bool bgmusic;
    bool txmusic;
    int delaylevel;
    ifstream file(SETTINGS_FILE);
    file>>bgmusic;
    file>>txmusic;
    file>>delaylevel;

    int h = 200;
    char text[5][32] = {"paly", "rules", "highestscore", "settings", "exit"};
    Button play(239, h + 100, 460, 80, text[0]);
    Button rules(239, h + 200, 460, 80, text[1]);
    Button score_list(239, h + 300, 460, 80, text[2]);
    Button settings(239, h + 400, 460, 80, text[3]);
    Button exit_game(239, h + 500, 460, 80, text[4]);

    ExMessage msg; // 声明一个消息指针
    while (!exitflag)
    {
        if (peekmessage(&msg, EM_MOUSE))
        {
            switch (msg.message)
            {
            case WM_LBUTTONDOWN://检测鼠标点击按钮
                if (msg.x >= 239 && msg.x <= 699  && msg.y >= 300 && msg.y <= 380)
                {
                    Tetris game(21, 10, 263, 10, 36);
                    game.play();
                }
                if (msg.x >= 239 && msg.x <= 699  && msg.y >= 400 && msg.y <= 480) printrules();

                if (msg.x >= 239 && msg.x <= 699  && msg.y >= 500 && msg.y <= 580) print_highestscore();
                if (msg.x >= 239 && msg.x <= 699  && msg.y >= 600 && msg.y <= 680) set_settings(bgmusic,txmusic,delaylevel);
                if (msg.x >= 239 && msg.x <= 699  && msg.y >= 700 && msg.y <= 780) exitflag=true;
                
                init();
                break;
            case WM_MOUSEMOVE://检测鼠标移动 按键变色
                BeginBatchDraw();
                if (msg.x >= 239 && msg.x <= 699  && msg.y >= 300 && msg.y <= 380)
                    play.change();
                else play.init();
                if (msg.x >= 239 && msg.x <= 699  && msg.y >= 400 && msg.y <= 480)
                    rules.change();
                else rules.init();
                if (msg.x >= 239 && msg.x <= 699  && msg.y >= 500 && msg.y <= 580)
                    score_list.change();
                else score_list.init();
                if (msg.x >= 239 && msg.x <= 699  && msg.y >= 600 && msg.y <= 680)
                    settings.change();
                else settings.init();
                if (msg.x >= 239 && msg.x <= 699  && msg.y >= 700 && msg.y <= 780)
                    exit_game.change();
                else exit_game.init();
                EndBatchDraw();
                break;
            default:
                break;
            }
        }
    }

    
    return 0;
}