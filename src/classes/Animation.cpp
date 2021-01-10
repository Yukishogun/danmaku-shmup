#include "Animation.h"

Animation::Animation(TexturePtr texture, std::vector<SDL_Rect> animationFrames, int timeInterval)
: timer(), paused(false), currentFrameIndex(0), texture(texture) {
    frames = animationFrames;
    timer.timeInterval = timeInterval;
}

Animation::~Animation()
{
}

void Animation::changeSpeed(int timeInterval) {
    timer.timeInterval = timeInterval;
}

void Animation::update(float timeStep) {
    if (!paused)
    {
        timer.update(timeStep);
        if (timer.hasPassedDeadline())
        {
            currentFrameIndex++;
            timer.repeat();
            if (currentFrameIndex >= frames.size())
            {
                currentFrameIndex = 0;
            }
        }
    }
}

SDL_Rect* Animation::getCurrentFrame() {
    return &frames.at(currentFrameIndex);
}

void Animation::render(SDL_Renderer *renderer, int x, int y) {
    texture->render(renderer, x, y, getCurrentFrame());
}

