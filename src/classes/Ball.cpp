#include "Ball.h"

Ball::Ball(TextureManager textureManager, SDL_Rect screenBounds)
: Entity("assets/cirno_ball.png"),
screenBounds(screenBounds), initalSpeed(1200), maxBounce(3.14159265 / 3),
leftOutOfBounds(0), rightOutOfBounds(0)
{
    speedX = initalSpeed;
    speedY = 0;
    initTexture(textureManager);
    moveTo(screenBounds.w / 2, screenBounds.h / 2);
}

void Ball::update(float timeStep) {
    if (hitbox.getX() >= screenBounds.w)
    {
        moveTo(screenBounds.w / 2, screenBounds.h / 2);
        speedX = -initalSpeed;
        speedY = 0;
        rightOutOfBounds++;
    }
    else if (hitbox.getX()+hitbox.getWidth() <= 0)
    {
        moveTo(screenBounds.w / 2, screenBounds.h / 2);
        speedX = initalSpeed;
        speedY = 0;
        leftOutOfBounds++;
    }
    else if (hitbox.getY() <= 0 || hitbox.getY() >= screenBounds.h - hitbox.getHeight())
    {
        speedY *= -1;
    }

    moveBy(speedX*timeStep, speedY*timeStep);
}

void Ball::onCollision(Entity *otherEntity) {
    float relativeIntersectY = (otherEntity->hitbox.getY() + (otherEntity->hitbox.getHeight() / 2)) - (hitbox.getY() + hitbox.getHeight()/2);
    double normalizedRelativeIntersectionY = (relativeIntersectY / (otherEntity->hitbox.getHeight() / 2));
    double bounceAngle = normalizedRelativeIntersectionY * maxBounce;

    if (hitbox.getX() > screenBounds.w/2)
    {
        speedX = -initalSpeed * cos(bounceAngle);
    }
    else
    {
        speedX = initalSpeed * cos(bounceAngle);
    }
    speedY = initalSpeed * sin(bounceAngle);
}

Ball::~Ball() {

}
