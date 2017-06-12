//
// Created by plusls on 17-5-16.
//

#include "FlyingObject.h"
#include "GameControl.h"
#include <cmath>
#include "Sounds.h"
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

bool FlyingObject::isDeath()
{
    if(clock.getElapsedTime() >= lifetime && type != 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void FlyingObject::setSpeed(float speed)//设置速度
{
    this->speed = speed;
    setDirection(direction);
}

float FlyingObject::getSpeed()//设置速度
{
    return speed;
}

void FlyingObject::setLifeTime(const sf::Time &lifetime)
{
    this->lifetime = lifetime;
}

int FlyingObject::getType()
{
    return type;
}

bool FlyingObject::isRemoveObject(FlyingObject *flyingobject)
{
    bool ret = flyingobject->isDeath();

    if (ret == true)
    {
        if (flyingobject->getType() == 0 || flyingobject->getType() == 1)
        {
            sf::Vector2f pos = flyingobject->getPosition();
            DeathObject *deathObject = new DeathObject;
            deathObject->setPosition(pos);
            addFlyingObject(deathObject);
        }
        delete flyingobject;
    }
    return ret;
}

Player::Player()
{
    type = 2;
    setOrigin(sf::Vector2f(PlayerTextureWidth / 2, PlayerTextureHeight / 2));
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

void Player::checkCollision()
{
    sf::Vector2f pos = getPosition();
    sf::FloatRect boundingBox(pos.x, pos.y, 12, 12);
    for (auto flyObject : flyingObjectList)
    {
        int objectType = flyObject->getType();
        if ((objectType == 0 || objectType == 1)&& flyObject->isDeath() == false && flyObject->getGlobalBounds().intersects(boundingBox))
        {
            MosterDeathSound *sound = new MosterDeathSound;
            sound->play();
            soundList.push_back(sound);
            for (auto flyingObject : flyingObjectList)
            {
                if ((flyingObject->getType() == 0 || flyingObject->getType() == 1) && isPosInGameWindow(flyingObject->getPosition()))
                    flyingObject->setLifeTime(sf::seconds(0));
            }
        }
    }
}

Reimu_1::Reimu_1()
{
    playerTexture = &reimuTexture;
}

void Reimu_1::shot(bool shift)
{
    PlayerBullet *centerBullet, *sideBullet_1, *sideBullet_2, *slowBullet;
    sf::Vector2f pos = getPosition();

    centerBullet = new PlayerBullet(reimuBulletTexture_1.centerBullet, 16, sf::seconds(1.5));
    centerBullet->setDirection(sf::Vector2f(0, -1));
    centerBullet->setPosition(pos.x,
                              pos.y - PlayerTextureHeight / 2);
    flyingObjectList.push_back(centerBullet);

    if (shift == false)
    {
        sideBullet_1 = new PlayerBullet(reimuBulletTexture_1.sideBullet, 16, sf::seconds(1.5));
        sideBullet_2 = new PlayerBullet(reimuBulletTexture_1.sideBullet, 16, sf::seconds(1.5));
        sideBullet_1->setDirection(sf::Vector2f(0, -1));
        sideBullet_2->setDirection(sf::Vector2f(0, -1));
        sideBullet_1->setPosition(pos.x - PlayerTextureWidth / 2,
                                  pos.y - PlayerTextureHeight / 2);
        sideBullet_2->setPosition(pos.x + PlayerTextureWidth / 2,
                                  pos.y - PlayerTextureHeight / 2);
        flyingObjectList.push_back(sideBullet_1);
        flyingObjectList.push_back(sideBullet_2);
    }
    else
    {
        slowBullet = new PlayerBullet(reimuBulletTexture_1.slowBullet, 8, sf::seconds(1.5));
        slowBullet->setDirection(sf::Vector2f(0, -1));
        slowBullet->setPosition(pos.x,
                                  pos.y - PlayerTextureHeight / 2);
        flyingObjectList.push_back(slowBullet);
    }
}

JudgePoint::JudgePoint(Player *player)
{

    type = 2;
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

DeathObject::DeathObject()
{
    lifetime = sf::seconds(0.2);
    type = 4;
    setTexture(deathTexture);
    setOrigin(deathTexture.getSize().x / 2, deathTexture.getSize().y / 2);
}

void DeathObject::draw(int count)
{
    scale += 1/25.0;
    setScale(scale, scale);
    setRotation(getRotation() + 1);

}

PlayerBullet::PlayerBullet(sf::Texture &playerBulletTexture, float playerBulletSpeed, const sf::Time &lifetime)
{
    type = 3;
    setTexture(playerBulletTexture);
    speed = playerBulletSpeed;
    this->lifetime = lifetime;

    sf::Vector2u size = playerBulletTexture.getSize();
    setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
}

void PlayerBullet::checkCollision()
{
    sf::FloatRect boundingBox = this->getGlobalBounds();
    for (auto flyingObject : flyingObjectList)
    {
        if (isPosInGameWindow(flyingObject->getPosition()) &&
                flyingObject->getType() == 0 && flyingObject->isDeath() == false && flyingObject->getPosition().y >=0  &&
                flyingObject->getGlobalBounds().intersects(boundingBox))
        {
            lifetime = sf::seconds(0);
            ((Moster*)flyingObject)->subHP(1);
        }
    }
}

Moster::Moster()
{
    type = 0;
}

void Moster::subHP(int HP)
{
    this->HP -= HP;
    if (this->HP <= 0)
    {
        MosterDeathSound *sound = new MosterDeathSound;
        sound->play();
        soundList.push_back(sound);
        lifetime = sf::seconds(0);
    }
}

Moster_1::Moster_1()
{
    HP = 1;
    setOrigin(sf::Vector2f(mosterTexture_1.Width/2, mosterTexture_1.Height/2));
    lifetime = sf::seconds(20);
}

void Moster_1::draw(int count)
{
    sf::Vector2f direction = getDirection();
    move(direction);
    if (direction.x < 0)
    {
        setScale(1, 1);
        setTexture(mosterTexture_1.Texture[4]);
    }
    else if (direction.x > 0)
    {
        setScale(-1, 1);
        setTexture(mosterTexture_1.Texture[4]);
    }
    else
    {
        setTexture(mosterTexture_1.Texture[0 + (count / 10)% 4]);
    }
}