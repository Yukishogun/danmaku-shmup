#pragma once

#include "Entity.h"

class Scoreboard : public Entity
{
public:
    Scoreboard(TextureManager &textureManager, std::string fontPath, int fontSize);
    ~Scoreboard();

    void setValue(int newValue);
    void increaseValue(int diff);
    void render(SDL_Renderer* renderer);
    SDL_Color color;

private:
    int value;
    int fontSize;
    void initFont(TextureManager &textureManager);
};
