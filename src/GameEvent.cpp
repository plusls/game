//
// Created by plusls on 17-6-1.
//

#include "GameEvent.h"
#include "FlyingObject.h"
#include "Draw.h"

//时间表
sf::Time timeTable[10] = {sf::seconds(5)};

//游戏事件
Stage1_1 stage1_1;

void Stage1_1::create()
{
    Moster_1 *moster;
    moster = new Moster_1;
    moster->setPosition(32, -10);
    moster->speed = 2;
    moster->setDirection(sf::Vector2f(0, 1));
    eventObjectList.push_back(moster);
    addFlyingObject(moster);
}

void Stage1_1::process()
{
    if(isCreated == false)
    {
        create();
        isCreated = true;
    }
    else
    {
        //create();
    }

}