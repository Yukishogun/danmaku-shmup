#pragma once
#include <unordered_map>
#include "Texture.h"

typedef std::shared_ptr<Texture> TexturePtr;

class TextureManager {
public:
    TextureManager();
    TextureManager(SDL_Renderer* renderer);
    ~TextureManager();

    TexturePtr loadImage(std::string path);
    TexturePtr loadFont(std::string path, int fontSize);
    SDL_Renderer* getRenderer();

private:
    TexturePtr findTexture(std::string path);
    std::unordered_map<std::string, TexturePtr> loadedTextures;
    SDL_Renderer* renderer;
};