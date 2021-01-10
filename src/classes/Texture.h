#pragma once
#include <string>
#include <map>
#include <iostream>
#include <SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

class Texture
{
public:
	Texture();
	~Texture();

	bool loadFromFile(SDL_Renderer* renderer, std::string path);
	bool loadFont(std::string path, int fontSize);
	void free();
	void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL);
	void renderText(SDL_Renderer* renderer, int x, int y, std::string value, SDL_Color textColor);
	int getWidth();
	int getHeight();
	SDL_Texture* getTexture();

private:
    SDL_Texture* fetchTexture(SDL_Renderer* renderer, SDL_Surface* loadedSurface);
    SDL_Texture* loadFromRenderedText(SDL_Renderer* renderer, std::string textureText, SDL_Color textColor);
    void renderHelper(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, SDL_Rect & renderQuad, SDL_Rect* clip = NULL);
	SDL_Texture* gTexture;
	TTF_Font *font;
	int width;
	int height;
};
