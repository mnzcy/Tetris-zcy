#include <vector>
using namespace std;
#include <graphics.h>
#include "Block.h"

#define KEY_DOWN(vk_c) (GetAsyncKeyState(vk_c)&0x8000?1:0)
class Tetris{
    public:
        Tetris(int rows,int cols,int left,int top,int BlockSize,int,int,int);
        void init();//初始化
        void play();//开始游戏
    private:
        void updateWindow();//渲染游戏画面
        void clearLine();//清行
        void keyEvent();//获取用户的输入
        int getDelay();//距离上次调用这个函数间隔多少时间（ms） 用于计时
        void drop();//方块掉落
        void moveLeftRight(int offx);
        void rotate();
        void drawScore();
        void gameover();
        void save_score();
        void game_pause();
        void newgame();
    private:
        int delay;//时间间隔
        bool update;//是否渲染标志
        bool overflag;
        bool backflag;
        vector<vector<int>> map;//存储每个方块数据
        int bgmusic;
        int txmusic;
        int delaylevel;
        int rows;
        int cols;
        int leftMargin;
        int topMargin;
        int BlockSize;
        int score;
        int level;
        int highestscore;
        static int max_level;
        IMAGE gamebg;//游戏背景
        
        Block* nowBlock;
        Block* nextBlock;
        IMAGE **imgs;

        static int normalSpeed;
        static int quickSpeed;
        static int addScore[4];
};