//
// Created by plusls on 17-5-16.
//

#include "GameControl.h"
#include <unistd.h>
#include "GameEvent.h"
//全局变量
const std::string RESOURCE_DIR = "../resources/";
int gameWindowWidth = 382, gameWindowHeight = 446;//游戏范围宽 高

int windowWidth = 640, windowHeight = 480;//窗口宽 高

int backGroundHeight = 480, backGroundWidth = 640;
//窗口
sf::RenderWindow *window;

//玩家
Player *player;

//判定点
JudgePoint *judgePoint;

//玩家速度
int defaultPlayerSpeed;
int slowPlayerSpeed;

//背景
sf::RenderTexture *background[7];//0 菜单 以及1到6关
sf::Texture *backgroundTexture;//背景纹理

//sprite

///////////////////////////////////计分板
sf::RenderTexture *scoreboard;//计分板
sf::Texture *scoreboardTexture;
///////////////////////////////////

//阶段
int stage = 1;
//新阶段
bool newGameStage = true;

//游戏时钟
sf::Clock gameClock;


void initialization()
{
    window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "东方妖妖梦"); //窗口设置
    window->setFramerateLimit(120); //设置fps

    //纹理
    backgroundTexture = new sf::Texture;
    backgroundTexture->loadFromFile("../resources/image/stg1bg.png", sf::IntRect(0, 0, 256, 256));

    //初始化计分板
    scoreboard = new sf::RenderTexture;
    scoreboard->create(windowWidth, windowHeight);
    scoreboardTexture = new sf::Texture;
    scoreboardTexture->loadFromFile("../resources/image/front.png", sf::IntRect(0, 224, 128, 32));


    //测试时不加载
    loadLogoBackground();//加载背景

    for (int i = 1; i < 7; ++i)
    {
        background[i] = new sf::RenderTexture;
        background[i]->create(382, 446);
    }

    //初始化玩家
    player = new Player(0);//载入玩家
    player->setPosition(player->playerTexture->Width/2, player->playerTexture->Height/2);
    judgePoint = new JudgePoint(player);//载入判定点

    //速度
    defaultPlayerSpeed = 7;
    slowPlayerSpeed = 3;

    addFlyingObject(player);
    addFlyingObject(judgePoint);
}

void loadLogoBackground()//加载背景
{
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("../resources/image/th07logo.jpg");
    window->clear();
    window->draw(sf::Sprite(backgroundTexture));
    window->display();
    sleep(2);
}

void gameContinue()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
        else if(event.type == sf::Event::KeyPressed)
        {
            //printf("keypress %d\n", event.key.code);

        }
        else if(event.type == sf::Event::KeyReleased)
        {
            //printf("keyreleased %d\n", event.key.code);
        }
    }
    if (stage == 0)
    {

    }
    else
    {
        if (newGameStage == true)
        {
            gameClock.restart();
            newGameStage = false;
        }
        timeTableControl();
        watchKey();
        updateWindow();

        //清空状态
        player->setDirection(sf::Vector2f(0, 0));
        judgePoint->setJudgePointStatus(false);
    }
}



void watchKey()
{
    sf::Vector2f direction;
    player->speed = defaultPlayerSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        player->speed = slowPlayerSpeed;
        judgePoint->setJudgePointStatus(true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        //std::thread t2(static_cast<void (sf::Text::*)(const sf::Vector2<float> &)>(&sf::Text::move));
        //void (sf::Text::*move)(const sf::Vector2<float> &) = &sf::Text::move;
        //std::thread t = std::thread(std::mem_fn(static_cast<void (sf::Text::*)(const sf::Vector2<float> &)>(&sf::Text::move)), text, sf::Vector2<float>(0, -length));
        direction = player->getDirection();
        if (direction.x != 0)
        {
            direction.x /= abs(direction.x);
        }
        direction.y = -1;
        player->setDirection(direction);

        /*std::thread th([](sf::Text *text){
            printf("hahaha\n");
            //text->move(sf::Vector2<float>(0, -8));

        }, &player);
        th.join();*/
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        direction = player->getDirection();
        if (direction.x != 0)
        {
            direction.x /= abs(direction.x);
        }
        direction.y = 1;
        player->setDirection(direction);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        direction = player->getDirection();
        if (direction.y != 0)
        {
            direction.y /= abs(direction.y);
        }
        direction.x = -1;
        player->setDirection(direction);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        direction = player->getDirection();
        if (direction.y != 0)
        {
            direction.y /= abs(direction.y);
        }
        direction.x = 1;
        player->setDirection(direction);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        if (gameClock.getElapsedTime().asMicroseconds() % 200 < 100)
        {
            int type[3] = {0, 0, 0};
            shot(player, type, sf::Vector2f(0, -1));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            {
                type[2] = 2;
            }
            else
            {
                type[2] = 1;
            }
            shot(player, type, sf::Vector2f(0, -1));
        }
    }
}

void shot(FlyingObject *flyingObject, int type[3], sf::Vector2f direction)
{
    Bullet *bullet;
    sf::Vector2f pos = flyingObject->getPosition();
    if (flyingObject->type == 1)
    {
        bullet = new PlayerBullet;
        bullet->setBulletType(type);
        bullet->setDirection(direction);
        if (type[2] == 1)
        {
            bullet->setPosition(pos.x - ((Player*)flyingObject)->playerTexture->Width / 2,
                                pos.y - ((Player*)flyingObject)->playerTexture->Height / 2);
            flyingObjectList.push_back(bullet);

            bullet = new PlayerBullet;
            bullet->setBulletType(type);
            bullet->setDirection(direction);
            bullet->setPosition(pos.x + ((Player*)flyingObject)->playerTexture->Width / 2,
                                pos.y - ((Player*)flyingObject)->playerTexture->Height / 2);
            flyingObjectList.push_back(bullet);
        }
        else
        {
            bullet->setPosition(pos.x, pos.y - ((Player*)flyingObject)->playerTexture->Height / 2);
            flyingObjectList.push_back(bullet);
        }
    }
}

void timeTableControl()
{
    bool gameEvent[10];
    sf::Time nowTime = gameClock.getElapsedTime();
    for (int i = 0; i < 10; ++i)
    {
        gameEvent[i] = false;
    }
    for (int i = 0; i < 10; ++i)
    {
        if (gameEvent[i] == false && nowTime > timeTable[i])
        {
            gameEvent[i] = true;
            stage1_1.process();
        }
    }
}

//void first