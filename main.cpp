#include "Tetris.h"
#include "Button.h"
#include <iostream>
#include <windows.h>
#include <fstream>
#define SETTINGS_FILE "resources/settings.txt"
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
void set_settings(){

}

int main()
{

    bool exitflag=false;
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    init();
    
    bool bgmusic;
    bool txmusic;
    int delaylevel;
    int beginlevel;


    int h = 200;
    char text[5][32] = {"paly", "rules", "score list", "settings", "exit"};
    Button play(269, h + 100, 400, 80, text[0]);
    Button rules(269, h + 200, 400, 80, text[1]);
    Button score_list(269, h + 300, 400, 80, text[2]);
    Button settings(269, h + 400, 400, 80, text[3]);
    Button exit_game(269, h + 500, 400, 80, text[4]);

    ExMessage msg; // 声明一个消息指针
    while (!exitflag)
    {
        if (peekmessage(&msg, EM_MOUSE))
        {
            switch (msg.message)
            {
            case WM_LBUTTONDOWN:
                if (msg.x >= 269 && msg.x <= 669  && msg.y >= 300 && msg.y <= 380)
                {
                    Tetris game(21, 10, 263, 10, 36);
                    game.play();
                }
                if (msg.x >= 269 && msg.x <= 669  && msg.y >= 400 && msg.y <= 480) printrules();

                if (msg.x >= 269 && msg.x <= 669  && msg.y >= 500 && msg.y <= 580)
                    // outtextxy(269, 420, title[2]);
                if (msg.x >= 269 && msg.x <= 669  && msg.y >= 600 && msg.y <= 680) set_settings();
                if (msg.x >= 269 && msg.x <= 669  && msg.y >= 700 && msg.y <= 780) exitflag=true;
                
                init();
                break;
            case WM_MOUSEMOVE:
                BeginBatchDraw();
                if (msg.x >= 269 && msg.x <= 669  && msg.y >= 300 && msg.y <= 380)
                    play.change();
                else play.init();
                if (msg.x >= 269 && msg.x <= 669  && msg.y >= 400 && msg.y <= 480)
                    rules.change();
                else rules.init();
                if (msg.x >= 269 && msg.x <= 669  && msg.y >= 500 && msg.y <= 580)
                    score_list.change();
                else score_list.init();
                if (msg.x >= 269 && msg.x <= 669  && msg.y >= 600 && msg.y <= 680)
                    settings.change();
                else settings.init();
                if (msg.x >= 269 && msg.x <= 669  && msg.y >= 700 && msg.y <= 780)
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