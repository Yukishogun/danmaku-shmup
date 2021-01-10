#pragma once
#include "Entity.h"

class Ball : public Entity {
public:
    Ball(TextureManager textureManager, SDL_Rect screenBounds);
    ~Ball();

    void update(float timeStep);
    void onCollision(Entity* otherEntity);

    int leftOutOfBounds;
    int rightOutOfBounds;

private:
    float speedX;
    float speedY;
    float initalSpeed;
    float maxBounce;
    SDL_Rect screenBounds;
};