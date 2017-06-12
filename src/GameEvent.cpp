//
// Created by plusls on 17-6-1.
//

#include "GameEvent.h"
#include "Draw.h"
#include "GameControl.h"


//游戏事件
Stage1_1 stage1_1;

//时间表
sf::Time timeTable[10] = {sf::seconds(13)};
GameEvent* gameEventList[10] = {&stage1_1};

void Stage1_1::create()
{
    creatMoster(330, -10, 0);
    creatMoster(64, -510, 1);
    creatMoster(330, -1010, 0);
    creatMoster(64, -1510, 1);
    creatMoster(330, -2110, 0);
    creatMoster(64, -2610, 1);
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
        changeStatus();
    }

}

void Stage1_1::creatMoster(int x, int y, int direct)
{
    Moster_1 *moster[12];
    int offsetX = 40, offsetY = 80;
    for (int i = 0; i < 12; ++i)
    {
        moster[i] = new Moster_1;
        addFlyingObject(moster[i]);
        eventObjectList.push_back(moster[i]);
        moster[i]->setSpeed(2);
        moster[i]->setDirection(sf::Vector2f(0, 1));
    }
    if (direct == 1)
    {
        offsetX = -offsetX;
    }

    for (int i = 0; i < 6; ++i)
    {
        moster[2 * i]->setPosition(x, y - offsetY * i);
        moster[2 * i + 1]->setPosition(x + offsetX, y - offsetY * i + 10);
    }
}

void Stage1_1::changeStatus()
{
    bool isFinished = true;
    for (size_t i = 0; i < eventObjectList.size(); ++i)
    {
        if (eventObjectList[i] != NULL && eventObjectList[i]->getType() != 0)//否则已死亡物体会被回收
            eventObjectList[i] = NULL;

        if (eventObjectList[i] != NULL)
        {
            isFinished = false;
            sf::Vector2f pos = eventObjectList[i]->getPosition();

            if (pos.y > 40 && pos.y < 100)
                eventObjectList[i]->setSpeed(eventObjectList[i]->getSpeed()*0.97);
            if (pos.y >= 100)
            {
                eventObjectList[i]->setSpeed(1);
                if (pos.x < gameWindowWidth / 2)
                    eventObjectList[i]->setDirection(sf::Vector2f(3, 1));
                else
                    eventObjectList[i]->setDirection(sf::Vector2f(-3, 1));
                eventObjectList[i] = NULL;
            }
        }
    }
    if (isFinished == true)
        isCreated = true;
}
