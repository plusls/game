//
// Created by plusls on 17-5-16.
//

#include "GameControl.h"
#include <unistd.h>
#include "GameEvent.h"
#include <SFML/Audio.hpp>
#include "Sounds.h"

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

//bgm
sf::Music music;


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
    //loadLogoBackground();//加载背景

    for (int i = 1; i < 7; ++i)
    {
        background[i] = new sf::RenderTexture;
        background[i]->create(382, 446);
    }

    //初始化玩家
    player = new Reimu_1;//载入玩家
    player->setPosition(PlayerTextureWidth / 2, PlayerTextureHeight/2);
    judgePoint = new JudgePoint(player);//载入判定点

    //速度
    defaultPlayerSpeed = 5;
    slowPlayerSpeed = 2;

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
            printf("%d", music.openFromFile("../resources/sound/Deep Mountain.wav"));
            music.play();
            newGameStage = false;
        }

        //玩家碰撞检测 必须放在时间表前
        player->checkCollision();

        timeTableControl();
        watchKey();


        //更新窗口
        updateWindow();

        //清理声音
        soundList.remove_if(Sound::isRemoveSound);

        //清空状态
        player->setDirection(sf::Vector2f(0, 0));
        judgePoint->setJudgePointStatus(false);

    }
}



void watchKey()
{
    sf::Vector2f direction;
    player->setSpeed(defaultPlayerSpeed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        player->setSpeed(slowPlayerSpeed);
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
            player->shot(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift));
        }
    }
}

void timeTableControl()
{
    sf::Time nowTime = gameClock.getElapsedTime();
    for (int i = 0; i < 10; ++i)
    {
        if (nowTime > timeTable[i] && gameEventList[i] != NULL)
        {
            gameEventList[i]->process();
            //stage1_1.process();
        }
    }
}

bool isPosInGameWindow(const sf::Vector2f &pos)
{
    if (pos.x >0 && pos.x < gameWindowWidth && pos.y > 0 && pos.y < gameWindowHeight)
        return true;
    else
        return false;
}