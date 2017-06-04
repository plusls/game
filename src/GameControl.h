//
// Created by plusls on 17-5-16.
//

#ifndef GAME_GAMECONTROL_H
#define GAME_GAMECONTROL_H
#include <SFML/Graphics.hpp>
#include <string>

#include "Textures.h"
#include "FlyingObject.h"
#include "Draw.h"


//全局变量
extern const std::string RESOURCE_DIR;
extern int gameWindowHeight, gameWindowWidth;
extern int windowWidth, windowHeight;//窗口宽 高


//窗口
extern sf::RenderWindow *window;

//玩家
extern Player *player;

//判定点
extern JudgePoint *judgePoint;

//当前阶段
extern int stage;
//是否为新阶段
extern bool newGameStage;

extern sf::RenderTexture *background[7];//0 菜单 以及1到6关
extern sf::Texture *backgroundTexture;//背景纹理


///////////////////////////////////计分板
extern sf::RenderTexture *scoreboard;//计分板
extern sf::Texture *scoreboardTexture;
///////////////////////////////////

//游戏时钟
extern sf::Clock gameClock;


//字体
//sf::Font font;
//if (!font.loadFromFile(RESOURCE_DIR + "wqy-microhei.ttc"))
//return EXIT_FAILURE;


void initialization(); //初始化
void gameContinue(); //继续游戏
void watchKey();
void loadLogoBackground();//打开游戏时显示背景
void shot(FlyingObject *flyingObject, int type[3], sf::Vector2f direction);//射击
void timeTableControl();
#endif //GAME_GAMECONTROL_H
