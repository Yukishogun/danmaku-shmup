#include "Scoreboard.h"

Scoreboard::Scoreboard(TextureManager &textureManager, std::string fontPath, int fontSize)
: Entity(fontPath), fontSize(fontSize)
{
    value = 0;
    initFont(textureManager);
    color = { 0, 0, 0 };
}

Scoreboard::~Scoreboard()
{}

void Scoreboard::initFont(TextureManager &textureManager)
{
    texture = textureManager.loadFont(path, fontSize);
}

void Scoreboard::setValue(int newValue)
{
    value = newValue;
}

void Scoreboard::render(SDL_Renderer *renderer)
{
    texture->renderText(renderer, hitbox.getX(), hitbox.getY(), std::to_string(value), color);
}

void Scoreboard::increaseValue(int diff) {
    setValue(value + diff);
}
