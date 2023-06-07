#pragma once
#include "SpriteObject.h"

enum class CollisionType
{
    AABB,
    CIRCLE
};

class PhysicsObject :
    public SpriteObject
{
public:

    PhysicsObject();

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;
    virtual void HandleCollision(PhysicsObject& other);

    void SetColliding(bool newColliding);
    bool CheckCollision(PhysicsObject other);
    sf::Vector2f GetCollisionDepth(PhysicsObject other);

protected:

    virtual void UpdateAcceleration();

    sf::Vector2f twoFramesOldPosition;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    sf::Vector2f collisionOffset;
    sf::Vector2f collisionScale;
    CollisionType collisionType;
    bool hasDrag;

    float GetCircleColliderRadius();
    sf::Vector2f GetCollisionCentre();

public:

    sf::FloatRect GetAABB();
private:

    bool colliding;
};

