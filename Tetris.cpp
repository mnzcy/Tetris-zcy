#include <stdio.h>
#include <stdlib.h>
#include "Tetris.h"

#include <conio.h>
#include<time.h>
#include <vector>
#include <graphics.h>
using namespace std;
#include <windows.h>
#include <mmsystem.h>
#include <string>
#include <fstream>
#pragma comment(lib,"Winmm.lib")
#define RECORD_FILE "resources/highestscore.txt"
int Tetris::normalSpeed=500;
int Tetris::quickSpeed=20;
int Tetris::addScore[4]={10,40,90,160};
int Tetris::max_level=5;
Tetris::Tetris(int rows, int cols, int left, int top, int BlockSize):map(rows,vector<int>(cols,0))//初始化map为0
{
    this->rows=rows;
    this->cols=cols;
    leftMargin=left;
    topMargin=top;
    this->BlockSize=BlockSize;
}

void Tetris::init()
{
    score=0;
    level=0;
    overflag=false;
    backflag=false;
    delay=normalSpeed;//间隔时间
    srand(time(NULL));//配置随机种子
    // backui=new Button();
    
    loadimage(&gamebg,"resources/bg2.png",938,809);//加载游戏背景
    imgs=Block::getImage();

    ifstream file(RECORD_FILE);
    file>>highestscore;
    file.close();
}

void Tetris::play()
{
    
    init();
    mciSendString("open resources/xiaochu1.mp3 alias song",NULL,0,NULL);
    mciSendString("play resources/bg.mp3 repeat",0,0,0);
    nowBlock=new Block;
    nextBlock=new Block;

    update=true;

    int timeGap=0;
    while(!backflag){
        keyEvent();

        timeGap+=getDelay();
        if(timeGap>delay){
            timeGap=0;
            drop();//方块下落
            update=true;
        }

        if(update){
            update=false;
            updateWindow();//更新游戏画面
            clearLine();//更新游戏数据
        }

        if(overflag) {
            gameover();
            while(1){
                 if(KEY_DOWN('N')) {newgame();break;}
                 if(KEY_DOWN('B')) {backflag=true;break;}
            }
        
    }
}
}
void Tetris::keyEvent(){
    unsigned char ch;
    
    bool rotateFlag=false;
    
    if(KEY_DOWN('A')){
        moveLeftRight(-1);
        Sleep(150);
    }
    if(KEY_DOWN('D')){
        moveLeftRight(1);
        Sleep(150);
    }
    if(KEY_DOWN('W')){
        rotate();
        Sleep(200);
    }
    if(KEY_DOWN('S')){
        delay=quickSpeed;
        Sleep(80+20*level);
    }
    if(KEY_DOWN('P')){
        game_pause();
        Sleep(200);
    }
    if(KEY_DOWN('B')){
        backflag=true;
    }
    
}



void Tetris::moveLeftRight(int offx)
{
    Block bakBlock(nowBlock);

    nowBlock->moveLeftRight(offx);

    if(nowBlock->unfit(map)==false){
        nowBlock->copy(&bakBlock);
    }
    update=true;

}

void Tetris::rotate()
{
    if(nowBlock->getBlockType()==2) return;
    Block bakBlock(nowBlock);
    nowBlock->rotate();
    if(nowBlock->unfit(map)==false){
        nowBlock->copy(&bakBlock);
    }
    update=true;
}

void Tetris::drawScore()
{
    char score_char[32];
    string str_score=to_string(score);
    strcpy(score_char,str_score.c_str());

    char level_char[10];
    string str_level="level "+to_string(level+1);
    strcpy(level_char,str_level.c_str());

    char highestscore_char[32];
    string str_highestscore=to_string(highestscore);
    strcpy(highestscore_char,str_highestscore.c_str());
    settextcolor(WHITE);
    settextstyle(40,20,"楷体");
    outtextxy(76,645,level_char);
    settextstyle(60,30,"楷体");
    outtextxy(676,645,score_char);
    outtextxy(676,735,highestscore_char);
}

void Tetris::gameover()
{
    save_score();
    mciSendString("stop resources/bg.mp3",0,0,0);
    IMAGE over_image;
    loadimage(&over_image,"resources/over.png");
    putimage(400,400,&over_image);
    mciSendString("play resources/over.mp3",0,0,0);
    
}

void Tetris::save_score()
{
    if(score>highestscore){
        highestscore=score;
        ofstream file(RECORD_FILE);
        file<<highestscore;
        file.close();
    }
}

void Tetris::game_pause()
{
    Sleep(200);
    while(1){
        if(KEY_DOWN('P')) break;
    }
    
}

void Tetris::newgame()
{
    for(int i=0;i<rows;++i){
        for(int j=0;j<cols;++j){
            map[i][j]=0;
        }
    }
    score=0;
    level=0;
    overflag=false;
    delay=normalSpeed;
}

int Tetris::getDelay(){
    static unsigned long long int lastime=0;
    unsigned long long int nowtime=GetTickCount();
    if(lastime==0){
        lastime=nowtime;
        return 0;
    }
    else{
        int returnTime=nowtime-lastime;
        lastime=nowtime;
        return returnTime;
    }
}

void Tetris::drop(){
    Block bakBlock(nowBlock);
    
    nowBlock->drop();
    if(nowBlock->unfit(map)==false){
        bakBlock.stopBlock(map);
        
        delay=normalSpeed-level*100;//如果有快速下降的情况，到底后立马还原速度

        delete nowBlock;
        nowBlock=nextBlock;
        nextBlock=new Block;
        if(nowBlock->unfit(map)==false) overflag=true;
    }
}



 void Tetris::updateWindow(){
        putimage(0,0,&gamebg);//刷新游戏背景

        BeginBatchDraw();
        for(int i=0;i<rows;++i){//渲染已经存在的小方块，数组中存储的数字即为方块颜色
            for(int j=0;j<cols;++j){
                if(map[i][j]==0) continue;
                int trow=topMargin+i*BlockSize;
                int tcol=leftMargin+j*BlockSize;
                putimage(tcol,trow,imgs[map[i][j]-1]);
            }
        }

        nowBlock->draw(leftMargin,topMargin);//绘制当前方块
        nextBlock->draw(500,100);//绘制预告方块
        drawScore();
        EndBatchDraw();
 }
    
void Tetris::clearLine(){//清行
    int k=rows-1;
    int lineCount=0;
    for(int i=rows-1;i>=0;--i){
        int count=0;
        for(int j=0;j<cols;++j){
            if(map[i][j]) count++;
            map[k][j]=map[i][j];
        }
        if(count<cols){
            k--;
        }
        else {
            lineCount++;
        }
    }

    if(lineCount>0){
        score+=addScore[lineCount-1];
        mciSendString("play resources/xiaochu1.mp3",0,0,0);
        level=score/100;
        if(level>=max_level) level=4;
        delay=normalSpeed-level*100;
        update=true;
    }
}


