//
// Created by plusls on 17-5-16.
//

#ifndef GAME_TEXTURES_H
#define GAME_TEXTURES_H

#include <SFML/Graphics.hpp>

class GameRoleTexture {
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
};

class ReimuTexture : public GameRoleTexture{
public:
    ReimuTexture();
};

class JudgePointTexture : public sf::Texture{
public:
    JudgePointTexture();
};

class PlayerBulletTexture
{
public:
    sf::Texture centerBullet;
    sf::Texture sideBullet;
    sf::Texture slowBullet;
};

class ReimuBulletTexture : public PlayerBulletTexture{
public:
    ReimuBulletTexture(int type);
};

class MosterTexture_1 : public GameRoleTexture{
public:
    MosterTexture_1();
};


//判定点纹理
extern JudgePointTexture judgePointTexture;

//玩家纹理
extern ReimuTexture reimuTexture;

//玩家子弹纹理
extern ReimuBulletTexture reimuBulletTexture[2];

//怪物纹理
extern MosterTexture_1 mosterTexture_1;

#endif //GAME_TEXTURES_H
