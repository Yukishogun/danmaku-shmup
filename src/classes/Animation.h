#pragma once
#include <vector>
#include <string>
#include <SDL.h>
#include "Timer.h"
#include "TextureManager.h"

class Animation {
public:
    Animation(TexturePtr texture, std::vector<SDL_Rect> animationFrames, int timeInterval);
    ~Animation();

    void update(float timeStep);
    void render(SDL_Renderer* renderer, int x, int y);
    void changeSpeed(int timeInterval);
    SDL_Rect* getCurrentFrame();

    bool paused;

private:
    TexturePtr texture;
    int currentFrameIndex;
    Timer timer;
    std::vector<SDL_Rect> frames;
};

typedef std::shared_ptr<Animation> AnimationPtr;