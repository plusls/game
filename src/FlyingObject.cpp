//
// Created by plusls on 17-5-16.
//

#include "FlyingObject.h"
#include "GameControl.h"
#include <cmath>

sf::Vector2f FlyingObject::getDirection()
{
    return direction;
}

void FlyingObject::setDirection(const sf::Vector2f& direction)
{
    float mod = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
    this->direction = direction;
    if (mod)
    {
        this->direction.x *= speed / mod;
        this->direction.y *= speed / mod;
    }
}

void FlyingObject::draw(int count)
{
    sf::Vector2f direction = getDirection();
    move(direction);
}


Player::Player(int playerNum)
{
    type = 1;
    setPlayerNum(playerNum);
    setOrigin(sf::Vector2f(playerTexture->Width/2, playerTexture->Height/2));
}

void Player::setPlayerNum(int playerNum)
{
    switch(playerNum)
    {
        case 0:
            playerTexture = &reimuTexture;
            break;
    }
}

void Player::draw(int count)
{
    sf::Vector2f direction = getDirection();
    move(direction);
    if (direction.x < 0)
    {
        setScale(1, 1);
        setTexture(playerTexture->Texture[5 + (count / 10)% 6]);
    }
    else if (direction.x > 0)
    {
        setScale(-1, 1);
        setTexture(playerTexture->Texture[5 + (count / 10)% 6]);
    }
    else
    {
        setTexture(playerTexture->Texture[0 + (count / 10)% 4]);
    }
    fixPosition();
}

void Player::fixPosition()
{
    const sf::Vector2f& position = sf::Sprite::getPosition();
    if (position.x - playerTexture->Width/2 < 0)
    {
        sf::Sprite::setPosition(playerTexture->Width/2, position.y);
    }
    if (position.x + playerTexture->Width/2 > gameWindowWidth)
    {
        sf::Sprite::setPosition(gameWindowWidth - playerTexture->Width/2, position.y);
    }
    if (position.y - playerTexture->Height/2 < 0)
    {
        sf::Sprite::setPosition(position.x, playerTexture->Height/2);
    }
    if (position.y + playerTexture->Height/2 > gameWindowHeight)
    {
        sf::Sprite::setPosition(position.x, gameWindowHeight - playerTexture->Height/2);
    }
}

JudgePoint::JudgePoint(Player *player)
{
    type = 1;
    this->player = player;
    setTexture(judgePointTexture);
    setOrigin(sf::Vector2f(32, 32));
}

void JudgePoint::draw(int count)
{
    if (displayJudgePoint == true)
    {
        setTexture(judgePointTexture, true);
        this->rotate(1);
        setPosition(player->getPosition());
    }
    else
    {
        setTexture(sf::Texture(), true);
    }
}

void JudgePoint::setJudgePointStatus(bool status)
{
    this->displayJudgePoint = status;
}

PlayerBullet::PlayerBullet()
{
    type = 2;
}

void PlayerBullet::setBulletType(int type[3])
{
    lifetime = sf::seconds(1.5);
    PlayerBulletTexture *playerBulletTexture;
    sf::Vector2u size;
    switch (type[0])
    {
        case 0:
            playerBulletTexture = &reimuBulletTexture[type[1]];
            break;
    }
    switch(type[2])
    {
        case 0:
            setTexture(playerBulletTexture->centerBullet);
            size = playerBulletTexture->centerBullet.getSize();
            setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
            speed = 16;
            break;
        case 1:
            setTexture(playerBulletTexture->sideBullet);
            size = playerBulletTexture->sideBullet.getSize();
            setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
            speed = 16;
            break;
        case 2:
            setTexture(playerBulletTexture->slowBullet);
            size = playerBulletTexture->slowBullet.getSize();
            setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
            speed = 8;
            break;
    }
}



Moster_1::Moster_1()
{
    setOrigin(sf::Vector2f(mosterTexture_1.Width/2, mosterTexture_1.Height/2));
    lifetime = sf::seconds(10);
}

void Moster_1::draw(int count)
{
    printf("aaa\n");
    sf::Vector2f direction = getDirection();
    move(direction);
    if (direction.x < 0)
    {
        setScale(1, 1);
        setTexture(mosterTexture_1.Texture[5 + (count / 10)% 4]);
    }
    else if (direction.x > 0)
    {
        setScale(-1, 1);
        setTexture(mosterTexture_1.Texture[5 + (count / 10)% 4]);
    }
    else
    {
        setTexture(mosterTexture_1.Texture[0 + (count / 10)% 4]);
    }
}