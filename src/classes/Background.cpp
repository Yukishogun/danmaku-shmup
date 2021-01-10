#include "Background.h"

Background::Background(TextureManager textureManager, SDL_Rect screenBounds)
: Entity("assets/japan1.jpg"), speed(1000), screenBounds(screenBounds)
{
    initTexture(textureManager);
}

Background::~Background()
{}

void Background::update(float timeStep)
{
    hitbox.moveBy(0, speed*timeStep);

    if (hitbox.getY() > screenBounds.h)
    {
        hitbox.moveTo(0, -250);
    }
}
