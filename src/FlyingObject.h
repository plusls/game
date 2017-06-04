//
// Created by plusls on 17-5-16.
//

#ifndef GAME_FLYINGOBJECT_H
#define GAME_FLYINGOBJECT_H

#include <SFML/Graphics.hpp>
#include "Textures.h"

class FlyingObject : public sf::Sprite
{
public:
    bool remove = false;
    int speed;
    sf::Clock clock;
    sf::Time extra = sf::seconds(0);
    sf::Time lifetime;
    int type;//其他为0 玩家为1 玩家子弹2
    void setDirection(const sf::Vector2f& direction);
    sf::Vector2f getDirection();
    virtual void draw(int count);
private:
    sf::Vector2f direction;

};

class Player : public FlyingObject
{
public:
    Player(int playerNum);
    void setPlayerNum(int playerNum);
    virtual void draw(int count);
    GameRoleTexture *playerTexture;
private:
    void fixPosition();
};

class JudgePoint : public FlyingObject
{
public:
    virtual void draw(int count);
    void setJudgePointStatus(bool status);
    JudgePoint(Player *player);

private:
    bool displayJudgePoint = false;
    Player *player;
};

class Bullet : public FlyingObject
{
public:
    virtual void setBulletType(int type[3]) = 0;
};

class PlayerBullet : public Bullet
{
public:
    PlayerBullet();
    virtual void setBulletType(int type[3]);//人物 人物类型 子弹类型
};

class Moster_1 : public FlyingObject
{
public:
    Moster_1();
    virtual void draw(int count);
};

#endif //GAME_FLYINGOBJECT_H
