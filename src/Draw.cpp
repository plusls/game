//
// Created by plusls on 17-5-16.
//

#include "Draw.h"
#include "GameControl.h"

//std::list<sf::Drawable*> drawList;

std::list<FlyingObject*> flyingObjectList;


/*void addBackGround(sf::Drawable* drawable)
{
    drawList.push_back(drawable);
}*/

void addFlyingObject(FlyingObject* flyingObject)
{
    flyingObjectList.push_back(flyingObject);
}

void drawBackGround(sf::RenderTarget* background)
{
    sf::Sprite tmp;
    tmp.setTextureRect(sf::IntRect(0, 0, 256, gameWindowHeight));
    backgroundTexture->setRepeated(true);
    tmp.setTexture(*backgroundTexture);
    tmp.setScale(gameWindowWidth/256.0, 1);
    background->draw(tmp);
}

void drawFlyingObject(sf::RenderTarget* background)
{
    static int count = 0;
    flyingObjectList.remove_if(FlyingObject::isRemoveObject);

    for(auto object : flyingObjectList)
    {
        object->draw(count);
        int objectType = object->getType();
        if (objectType == 1|| objectType == 3) //如果是子弹则进行碰撞检测
            ((Bullet*)object)->checkCollision();
        background->draw(*object);
    }
    ++count;
    count %= 200;
}



void updateScoreboard()
{
    sf::Sprite scoreboardSprite;
    scoreboard->clear();
    scoreboardTexture->setRepeated(true);
    scoreboardSprite.setTextureRect(sf::IntRect(0, 0, windowWidth, windowHeight));
    scoreboardSprite.setTexture(*scoreboardTexture);
    scoreboard->draw(scoreboardSprite);
    scoreboard->display();
}

void updateWindow()
{
    sf::Sprite backgroundSprite;
    window->setActive();
    window->clear();
    if (stage != 0)//阶段为0则为绘画菜单 不为0绘画背景
    {
        updateScoreboard();
        window->draw(sf::Sprite(scoreboard->getTexture()));
    }

    background[stage]->clear();//清空画板
    drawBackGround(background[stage]);//画背景

    drawFlyingObject(background[stage]);//画飞行物体

    background[stage]->display();//显示 否则图像是倒着的
    backgroundSprite.setPosition(36, 20);
    backgroundSprite.setTexture(background[stage]->getTexture());
    window->draw(backgroundSprite);

    window->display();
}