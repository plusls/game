//
// Created by plusls on 17-6-1.
//

#ifndef GAME_GAMEEVENT_H
#define GAME_GAMEEVENT_H
#include <vector>
#include "FlyingObject.h"

class GameEvent {
public:
    virtual void create() = 0;
    bool isCreated = false;
    std::vector<FlyingObject*> eventObjectList;
    virtual void process() = 0;
};


class Stage1_1 : public GameEvent
{
public:
    virtual void process();

private:
    virtual void create();
    void creatMoster(int x, int y, int direct);//0 向左  1 向右
    void changeStatus();
};

//时间表
extern sf::Time timeTable[10];
//游戏事件列表
extern GameEvent* gameEventList[10];

//游戏事件
extern Stage1_1 stage1_1;


#endif //GAME_GAMEEVENT_H
