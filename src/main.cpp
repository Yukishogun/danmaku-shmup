#include <iostream>
#include <string>
#include <map>
#include <SDL.h>
#include <SDL2_image/SDL_image.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include "classes/Texture.h"
#include "classes/Player.h"
#include "classes/TextureManager.h"
#include "lists/texturePaths.h"
#include "lists/KeyAction.h"
#include "classes/Scoreboard.h"
#include "classes/CollisionManager.h"
#include "classes/Ball.h"
#include "classes/Background.h"
#include "classes/Animation.h"
#include "classes/Enemy.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

bool init();
void loadMedia(TextureManager& textureManager);
void loop(TextureManager& textureManager, CollisionManager& collisionManager);
void close();

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Texture* gTexture = nullptr;

bool keysDown[256] = { 0 };

std::vector<EntityPtr> entities;


bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		success = false;
	}

	else
	{
		gWindow = SDL_CreateWindow("Danmaku", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == nullptr)
		{
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == nullptr)
			{
				std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
				success = false;
			}

			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);

				int imgFlags = IMG_INIT_PNG;

				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
					success = false;
				}

				if (TTF_Init() == -1)
                {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }
			}
		}
	}

	return success;
}

void loadMedia(TextureManager &textureManager) {
    for (auto & path : texturePaths) {
        textureManager.loadImage(path);
    }
}

void close() {
	SDL_DestroyTexture(gTexture);
	gTexture = nullptr;

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	gRenderer = nullptr;

	IMG_Quit();
	SDL_Quit();
}

void loop(TextureManager &textureManager, CollisionManager &collisionManager) {

    int score = 0;

    std::shared_ptr<CollisionManager> collPtr = std::make_shared<CollisionManager>(collisionManager);

    SDL_Rect screenBounds;
    screenBounds.w = SCREEN_WIDTH;
    screenBounds.h = SCREEN_HEIGHT;

    Entity background("assets/japan1.jpg");
    background.initTexture(textureManager);
    background.moveTo(-250, 0);

    Player player1(textureManager, collPtr, &entities, arrowLR);

    player1.moveTo(600, 800);

	EntityPtr backgroundPtr = std::make_shared<Entity>(background);
	entities.push_back(backgroundPtr);


	std::function<float(float)> trajY = [](float x) { return 0; };
	std::function<float(float)> trajX = [](float x) { return 100*sin(2*x); };

	for (float i = 110; i < SCREEN_WIDTH-110; i += 110) {
		for(float j = 60; j < SCREEN_HEIGHT/3; j += 110) {
			Enemy enemy(textureManager, collPtr, &entities, trajX, trajY, i, j, 100);
			EntityPtr enemyPtr = std::make_shared<Enemy>(enemy);
			collPtr->addEntity(enemyPtr);
			entities.push_back(enemyPtr);
		}
	}

	Scoreboard scoreboard(textureManager, "assets/atarifont.ttf", 50);

	scoreboard.moveTo(25, 25);

    EntityPtr playerPtr = std::make_shared<Player>(player1);
    std::shared_ptr<Scoreboard> scoreboardPtr = std::make_shared<Scoreboard>(scoreboard);

    collPtr->addEntity(playerPtr);

    entities.push_back(playerPtr);
    entities.push_back(scoreboardPtr);

    Uint32 lastTime = SDL_GetTicks();
    Uint32 currentTime;
    float timeStep;

    bool quit = false;
    SDL_Event e;

	while (!quit)
	{
	    currentTime = SDL_GetTicks();
        timeStep = (currentTime - lastTime)/1000.f;
        lastTime = currentTime;

		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type) {

			    case SDL_QUIT:
                    quit = true;
                    break;

               case SDL_KEYDOWN:
                    keysDown[e.key.keysym.scancode] = true;
                    break;

                case SDL_KEYUP:
                    keysDown[e.key.keysym.scancode] = false;
                    break;

                default:
                    continue;
            }
		}


        EntityPtr entity;
        for (int i = 0; i < entities.size(); i++)
        {
            entity = entities.at(i);
            if (!entity->alive)
            {
                entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
                scoreboardPtr->increaseValue(entity->getScore());
				i--;
                continue;
            }
            entity->update(timeStep);
        }

        collPtr->update();

        for (auto & entity : entities)
        {
            entity->render(gRenderer);
        }

		SDL_RenderPresent(gRenderer);

	}

	close();
}

int main(int argc, char* args[]) {

	if (!init()) {
		printf("Failed to initialize!\n");
	}
	else {
        TextureManager textureManager(gRenderer);
        CollisionManager collisionManager;

		loadMedia(textureManager);

		loop(textureManager, collisionManager);
	}

	return 0;
}