//
// Created by plusls on 17-5-16.
//

#ifndef GAME_DRAW_H
#define GAME_DRAW_H
#include <SFML/Graphics.hpp>
#include "FlyingObject.h"
#include <list>

//extern std::list<sf::Drawable*> drawList;

extern std::list<FlyingObject*> flyingObjectList;

void drawBackGround(sf::RenderTarget* window);

void drawFlyingObject(sf::RenderTarget* window);

void addFlyingObject(FlyingObject* flyingObject);

void addBackGround(sf::Drawable* drawable);

void updateScoreboard();

void updateWindow();

bool isRemoveObject(FlyingObject*);
#endif //GAME_DRAW_H
