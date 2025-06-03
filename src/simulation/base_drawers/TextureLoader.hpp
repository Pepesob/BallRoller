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
    static sf::Texture* getTexture(const std::string &texturePath);
    static void clear();

private:
    static std::map<std::string, sf::Texture*> loadedTextures;
};
