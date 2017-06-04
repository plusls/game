//
// Created by plusls on 17-5-16.
//

#include "Textures.h"

//判定点纹理
JudgePointTexture judgePointTexture;

//玩家纹理
ReimuTexture reimuTexture;

//怪物纹理
MosterTexture_1 mosterTexture_1;

//玩家子弹纹理预加载
ReimuBulletTexture reimuBulletTexture[2] = {ReimuBulletTexture(0), ReimuBulletTexture(1)};

//怪物子弹纹理预加载



void GameRoleTexture::init()//存在内存泄露
{
    Pos = new int *[PosSize];
    for (int i = 0; i < PosSize; ++i)
    {
        Pos[i] = new int [3];
    }
    Texture = new sf::Texture [TextureNum];
}

void GameRoleTexture::loadTextures()
{
    int now = 0;
    for (int i = 0; i < PosSize; ++i)
    {
        for (int j = 0; j < Pos[i][2]; ++j)
        {
            Texture[now].loadFromFile(TextureFileName,
                                    sf::IntRect(Pos[i][0] + j * Width, Pos[i][1], Width, Height));
            Texture[now].setSmooth(true);
            ++now;
        }
    }
}

ReimuTexture::ReimuTexture()
{
    PosSize = 2;
    TextureNum = 18;
    init();
    Width = 32;
    Height = 48;

    //正常
    Pos[0][0] = 0;
    Pos[0][1] = 0;
    Pos[0][2] = 4;

    //左
    Pos[1][0] = 0;
    Pos[1][1] = Height;
    Pos[1][2] = 7;

    TextureFileName = "../resources/image/player00.png";
    loadTextures();
}


JudgePointTexture::JudgePointTexture()
{
    loadFromFile("../resources/image/etama2.png", sf::IntRect(0, 112, 64, 64));
};

ReimuBulletTexture::ReimuBulletTexture(int type)
{
    if (type == 0)
    {
        centerBullet.loadFromFile("../resources/image/player00.png", sf::IntRect(128, 0, 16, 16));
        sideBullet.loadFromFile("../resources/image/player00.png", sf::IntRect(144, 0, 16, 16));
        slowBullet.loadFromFile("../resources/image/player00.png", sf::IntRect(208, 0, 32, 32));
    }
    else
    {
        centerBullet.loadFromFile("../resources/image/player00.png", sf::IntRect(128, 0, 16, 16));
        sideBullet.loadFromFile("../resources/image/player00.png", sf::IntRect(192, 0, 16, 48));
        slowBullet.loadFromFile("../resources/image/player00.png", sf::IntRect(0, 160, 32, 64));
    }
}

MosterTexture_1::MosterTexture_1()
{
    PosSize = 1;
    TextureNum = 8;
    init();
    Width = 32;
    Height = 32;

    Pos[0][0] = 0;
    Pos[0][1] = 0;
    Pos[0][2] = 8;

    TextureFileName = "../resources/image/stg7enm.png";
    loadTextures();
}