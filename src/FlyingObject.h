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
    bool isDeath();
    int getType();
    sf::Vector2f getDirection();
    void setSpeed(float speed);
    float getSpeed();

    void setLifeTime(const sf::Time &lifetime);
    void setDirection(const sf::Vector2f& direction);
    virtual void draw(int count);
    static bool isRemoveObject(FlyingObject *flyingobject);

protected:
    int type;//怪物为0 怪物子弹为1 玩家为2 玩家子弹3 无敌物体4 //怪物与玩家子弹 怪物子弹与玩家
    sf::Time lifetime;
    float speed;
    sf::Clock clock;


private:
    sf::Vector2f direction;
    sf::Time extra = sf::seconds(0);
};

/////////////////////////////////////////////////////
class Player : public FlyingObject //玩家的基类
{
public:
    Player();
    virtual void draw(int count);
    GameRoleTexture *playerTexture;
    void checkCollision();
    virtual void shot(bool shift) = 0;
private:
    void fixPosition();//防止出界
};

class Reimu_1 : public Player
{
public:
    Reimu_1();
    virtual void shot(bool shift);
};
//////////////////////////////////////////////////////////

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

class DeathObject : public FlyingObject
{
public:
    DeathObject();
    virtual void draw(int count);
private:
    float scale = 0;
};

class Bullet : public FlyingObject
{
public:
    virtual void checkCollision() = 0;

};

class PlayerBullet : public Bullet
{
public:
    PlayerBullet(sf::Texture &playerBulletTexture, float playerBulletSpeed, const sf::Time &lifetime);
    virtual void checkCollision();
};

class Moster : public FlyingObject
{
public:
    Moster();
    void subHP(int HP);
protected:
    int HP;
};


class Moster_1 : public Moster
{
public:
    Moster_1();
    virtual void draw(int count);
};

#endif //GAME_FLYINGOBJECT_H
