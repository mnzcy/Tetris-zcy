#include "Tetris.h"
#include <iostream>
#include <windows.h>
using namespace std;
int main(){
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    Tetris game(21,10,263,10,36);
    game.play();
    return 0;
}