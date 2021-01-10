#include "Hitbox.h"
#include <iostream>

Hitbox::Hitbox()
{
}

Hitbox::Hitbox(int width, int height)
{
    rect.w = width;
    rect.h = height;
}

void Hitbox::setSize(int width, int height)
{
    rect.w = width;
    rect.h = height;
}

Hitbox::~Hitbox()
{
    free();
}

void Hitbox::moveTo(float x, float y)
{
    rect.x = x;
    rect.y = y;
}

void Hitbox::moveBy(float dx, float dy)
{
    rect.x += dx;
    rect.y += dy;
}

bool Hitbox::collidesWith(Hitbox otherBox) {
    return SDL_HasIntersection(&rect, &otherBox.rect);
}

void Hitbox::free() {

}

float Hitbox::getX() {
    return rect.x;
}

float Hitbox::getY() {
    return rect.y;
}

float Hitbox::getWidth() {
    return rect.w;
}

float Hitbox::getHeight() {
    return rect.h;
}


