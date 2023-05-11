#pragma once
#include "PhysicsObject.h"

class Player:
    public PhysicsObject
{
public:

    Player();

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;
    void HandleCollision(SpriteObject& other) override;

private:

    void UpdateAcceleration() override;

    sf::Vector2f GetPipPosition(float pipTime, sf::Vector2f gravity, sf::Vector2f startVelocity, sf::Vector2f startPosition);

    sf::Vector2f twoFramesOldPosition;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    std::vector<sf::Sprite> pips;
};

