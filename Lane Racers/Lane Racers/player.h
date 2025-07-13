#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "bonusesEffectsContext.h"
using namespace std;
using namespace sf;
class player
{
private:
    RectangleShape shape;
    Texture texture;
    sf::Vector2f velocity;
    float speed;
    int WorkPlaceSize;
    bool CanMove = true;
    int score = 0;	
    bonusesEffectsContext& effects;

public:
    player(sf::Vector2f startPos, sf::Vector2f size, int WorkPlaceSize, bonusesEffectsContext& effects, float speed = 0.5f);

    void handleInput(float time);
    void update(float time, float winWidth);
    void draw(RenderWindow& win) const;

    sf::Vector2f GetPos() const;
    sf::Vector2f GetSize() const;
    sf::FloatRect GetBounds() const;
    int GetScore() const;
    bool IsCanMove() const;
    void AddScore(int value);
    void ChangeMovePosible(bool state);
    void Reset(Vector2f StartPos);
};

