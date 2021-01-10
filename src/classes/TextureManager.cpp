#include "TextureManager.h"

TextureManager::TextureManager(SDL_Renderer* renderer)
: loadedTextures(), renderer(renderer)
{
}

TextureManager::~TextureManager()
{
}

/**
 * https://codereview.stackexchange.com/questions/87367/texture-managing
 * @param path
 * @return
 */
TexturePtr TextureManager::loadImage(std::string path)
{
    TexturePtr newTexture = findTexture(path);

    newTexture->loadFromFile(renderer, path);

    loadedTextures.insert(std::make_pair(path, newTexture));

    return newTexture;
}

TexturePtr TextureManager::loadFont(std::string path, int fontSize) {
    TexturePtr newTexture = findTexture(path);

    newTexture->loadFont(path, fontSize);

    loadedTextures.insert(std::make_pair(path, newTexture));

    return newTexture;
}

TexturePtr TextureManager::findTexture(std::string path) {
    auto texIterator = loadedTextures.find(path);

    if (texIterator != loadedTextures.end())
    {
        return texIterator->second;
    }

    TexturePtr newTexture = std::make_shared<Texture>();

    return newTexture;
}

SDL_Renderer *TextureManager::getRenderer() {
    return renderer;
}
