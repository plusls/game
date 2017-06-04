#include <thread>

#include <string>
#include <unistd.h>
#include <cstdio>

#include "GameControl.h" //全局变量以及



int main()
{
    initialization();//初始化游戏
    //消息循环
    while (window->isOpen())
    {
        gameContinue();
    }
    return 0;
}