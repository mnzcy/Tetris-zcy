#include <graphics.h>
#include <vector>
using namespace std;
struct Point{
    int row;
    int col;
};


class Block{
public:
    Block();
    Block(Block *temp);//拷贝构造
    void copy(Block *temp);
    void drop();//下降
    void moveLeftRight(int offest);//左右移动
    void rotate();//旋转
    void draw(int leftMargin,int topMargin);//绘制方块
    bool unfit(const vector<vector<int>> &map);//判断是否合法
    void stopBlock(vector<vector<int>> &map);//方块停止运动
    static IMAGE** getImage();//取私有成员imgs
    int getBlockType();
private:
    int BlockType;//方块形状
    Point smallBlocks[4];//四个小方块点位
    IMAGE *img;//方块颜色指针
    static const int Blocks[7][4];//七种方块类型及点位
    static int size;//每个小方块大小
    static IMAGE* imgs[7];//方块颜色库
};