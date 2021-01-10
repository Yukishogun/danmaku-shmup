#include "Texture.h"
#include <SDL2_ttf/SDL_ttf.h>

Texture::Texture()
{
	gTexture = NULL;
	width = 0;
	height = 0;
}

Texture::~Texture()
{
	free();
}

bool Texture::loadFromFile(SDL_Renderer* renderer, std::string path)
{
	free();

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL)
    {
        std::cout << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << std::endl;
    }

	gTexture = fetchTexture(renderer, loadedSurface);
	return gTexture != NULL;
}

SDL_Texture* Texture::loadFromRenderedText(SDL_Renderer* renderer, std::string textureText, SDL_Color textColor)
{
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);

    return fetchTexture(renderer, textSurface);
}

SDL_Texture* Texture::fetchTexture(SDL_Renderer* renderer, SDL_Surface* loadedSurface)
{
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    width = loadedSurface->w;
    height = loadedSurface->h;
    SDL_FreeSurface(loadedSurface);

    return newTexture;
}

void Texture::free()
{
	if (gTexture != NULL)
	{
		SDL_DestroyTexture(gTexture);
		gTexture = NULL;
		width = 0;
		height = 0;
	}
}

void Texture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip)
{
	SDL_Rect renderQuad = { x, y, width, height };

	if (clip)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	renderHelper(renderer, gTexture, x, y, renderQuad, clip);
}

int Texture::getWidth()
{
	return width;
}

int Texture::getHeight()
{
	return height;
}

SDL_Texture* Texture::getTexture()
{
	return gTexture;
}

bool Texture::loadFont(std::string path, int fontSize) {
    font = TTF_OpenFont(path.c_str(), fontSize);

    return false;
}

void Texture::renderText(SDL_Renderer *renderer, int x, int y, std::string value, SDL_Color textColor) {
    SDL_Texture *newTexture = loadFromRenderedText(renderer, value, textColor);

    SDL_Rect renderQuad = { x, y, width, height };

    renderHelper(renderer, newTexture, x, y, renderQuad, NULL);

}

void Texture::renderHelper(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, SDL_Rect & renderQuad, SDL_Rect* clip)
{
    SDL_RenderCopy(renderer, texture, clip, &renderQuad);
}
