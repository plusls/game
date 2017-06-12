//
// Created by plusls on 17-5-16.
//

#ifndef GAME_TEXTURES_H
#define GAME_TEXTURES_H

#include <SFML/Graphics.hpp>

class GameRoleTexture
{
public:
    int Width;
    int Height;
    int PosSize;
    int **Pos;
    int TextureNum;
    std::string TextureFileName;
    sf::Texture *Texture;
    void init();
    void loadTextures();
    ~GameRoleTexture();
};

class ReimuTexture : public GameRoleTexture//灵梦纹理
{
public:
    ReimuTexture();
};

class JudgePointTexture : public sf::Texture
{ //判定点纹理
public:
    JudgePointTexture();
};

class DeathTexture : public sf::Texture
{ //死亡纹理
public:
    DeathTexture();
};


class PlayerBulletTexture//玩家子弹纹理 基类
{
public:
    sf::Texture centerBullet;
    sf::Texture sideBullet;
    sf::Texture slowBullet;
};

//灵梦子弹纹理
///////////////////////////////////////////////////////////////
class ReimuBulletTexture_1 : public PlayerBulletTexture{
public:
    ReimuBulletTexture_1();
};

class ReimuBulletTexture_2 : public PlayerBulletTexture{
public:
    ReimuBulletTexture_2();
};
//////////////////////////////////////////////////////////////


class MosterTexture_1 : public GameRoleTexture{
public:
    MosterTexture_1();
};


//玩家纹理信息
extern int PlayerTextureHeight, PlayerTextureWidth;


//判定点纹理
extern JudgePointTexture judgePointTexture;

//死亡纹理
extern DeathTexture deathTexture;


//玩家纹理
extern ReimuTexture reimuTexture;

//玩家子弹纹理
////////////////////////////////////////////////////////////
//灵梦
extern ReimuBulletTexture_1 reimuBulletTexture_1;
extern ReimuBulletTexture_2 reimuBulletTexture_2;
////////////////////////////////////////////////////////////

//怪物纹理
extern MosterTexture_1 mosterTexture_1;

#endif //GAME_TEXTURES_H
