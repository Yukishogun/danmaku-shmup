#pragma once
#include "Entity.h"

class Background :
public Entity
{
public:
    explicit Background(TextureManager textureManager, SDL_Rect screenBounds);
    ~Background();

    void update(float timeStep);

private:
    float speed;
    SDL_Rect screenBounds;
};
