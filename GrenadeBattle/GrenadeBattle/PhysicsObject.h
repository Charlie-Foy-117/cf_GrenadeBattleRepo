#pragma once
#include "SpriteObject.h"
class PhysicsObject :
    public SpriteObject
{
public:

    PhysicsObject();

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;
    virtual void HandleCollision(PhysicsObject& other);

private:

    virtual void UpdateAcceleration();

    sf::Vector2f twoFramesOldPosition;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
};

