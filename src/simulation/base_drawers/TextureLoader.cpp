//
// Created by sp on 20.05.2025.
//

#include "TextureLoader.hpp"

std::map<std::string, sf::Texture*> TextureLoader::loadedTextures;

sf::Texture * TextureLoader::getTexture(const std::string &texturePath) {
    if (!TextureLoader::loadedTextures.contains(texturePath)) {
        TextureLoader::loadedTextures[texturePath] = new sf::Texture(texturePath);
    }
    return TextureLoader::loadedTextures[texturePath];
}

void TextureLoader::clear() {
    for (const auto &val: TextureLoader::loadedTextures | std::views::values) {
        delete val;
    }
    TextureLoader::loadedTextures.clear();
}
