#pragma once
#include "SpriteObject.h"

class Player:
    public SpriteObject
{
public:

    Player();

    void Update(sf::Time frameTime) override;
    void HandleCollision(SpriteObject& other) override;

private:

    void UpdateAcceleration();

    sf::Vector2f twoFramesOldPosition;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
};

