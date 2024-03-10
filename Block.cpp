#include "Block.h"
#include <stdlib.h>
#include <vector>
using namespace std;
const int Block::Blocks[7][4]={
    1,3,5,7,//1
    2,3,4,5,//田
    3,4,5,7,//T
    1,2,3,4,//Z
    0,2,3,5,//镜像Z
    1,3,4,5,//J
    0,2,4,5,//L
};
int Block::size=36;
 IMAGE* Block::imgs[7]={NULL};

Block::Block()
{
    if(imgs[0]==NULL){//首次创建时，获取所有的方块颜色，存入imgs
        IMAGE imgtep;
        loadimage(&imgtep,"resources\\tiles.png");
        SetWorkingImage(&imgtep);
        for(int i=0;i<7;i++){
            imgs[i]=new IMAGE;
            getimage(imgs[i],i*36,0,36,36);
        }
        SetWorkingImage();
    }

    BlockType=rand()%7+1;//随机生成方块的形状
    for(int i=0;i<4;++i){//初始化方块的位置
        smallBlocks[i].row=Blocks[BlockType-1][i]/2;
        smallBlocks[i].col=Blocks[BlockType-1][i]%2+5;
    }

    img=imgs[BlockType-1];//配置方块颜色
}

Block::Block(Block *temp)
{
    this->BlockType=temp->BlockType;
    for(int i=0;i<4;++i){
        this->smallBlocks[i].col=temp->smallBlocks[i].col;
        this->smallBlocks[i].row=temp->smallBlocks[i].row;
    }
}

void Block::drop()
{
    for(int i=0;i<4;++i){
        smallBlocks[i].row++;
    }
}

void Block::moveLeftRight(int offest)
{
    for(int i=0;i<4;++i){
        smallBlocks[i].col+=offest;
    }
}

void Block::rotate()
{
    Point p=smallBlocks[1];
    for(int i=0;i<4;++i){
        Point temp=smallBlocks[i];
        smallBlocks[i].col=p.col-temp.row+p.row;
        smallBlocks[i].row=p.row+temp.col-p.col;
    }
}

void Block::draw(int leftMargin, int topMargin)
{
    for(int i=0;i<4;++i){
        int x=leftMargin+smallBlocks[i].col*size;
        int y=topMargin+smallBlocks[i].row*size;
        putimage(x,y,img);
    }
}

IMAGE **Block::getImage()
{
    return imgs;
}

int Block::getBlockType()
{
    return BlockType;
}



bool Block::unfit(const vector<vector<int>>& map){
    int rows=map.size();
    int cols=map[0].size();
    for(int i=0;i<4;++i){
        if(smallBlocks[i].row>=rows) return false;
        if(smallBlocks[i].col<0) return false;
        if(smallBlocks[i].col>=cols) return false;
        if(map[smallBlocks[i].row][smallBlocks[i].col]) return false;
    }
    return true;
}

void Block::stopBlock(vector<vector<int>>& map){
    for(int i=0;i<4;++i){
        map[smallBlocks[i].row][smallBlocks[i].col]=BlockType;
    }
}

void Block::copy(Block* temp){
    this->BlockType=temp->BlockType;
    for(int i=0;i<4;++i){
        this->smallBlocks[i]=temp->smallBlocks[i];
    }
}