//
// Created by sp on 20.05.2025.
//

#pragma once
#include <map>
#include <ranges>
#include <string>
#include <SFML/Graphics.hpp>


class TextureLoader {
public:
    static sf::Texture* getTexture(const std::string &texturePath) {
        if (!TextureLoader::loadedTextures.contains(texturePath)) {
            TextureLoader::loadedTextures[texturePath] = new sf::Texture(texturePath);
        }
        return TextureLoader::loadedTextures[texturePath];
    }

    static void clear() {
        for (const auto &val: TextureLoader::loadedTextures | std::views::values) {
            delete val;
        }
        TextureLoader::loadedTextures.clear();
    }

private:
    static std::map<std::string, sf::Texture*> loadedTextures;
};
