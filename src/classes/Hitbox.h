#pragma once
#include <SDL.h>

class Hitbox
{
public:
    Hitbox();
    Hitbox(int width, int height);
    ~Hitbox();

    void free();
    bool collidesWith(Hitbox otherBox);
    void moveTo(float x, float y);
    void moveBy(float x, float y);
    void setSize(int width, int height);
    float getX();
    float getY();
    float getWidth();
    float getHeight();

    SDL_Rect rect;
};
