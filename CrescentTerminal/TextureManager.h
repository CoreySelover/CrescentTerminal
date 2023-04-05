#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class TextureManager
{
public:
    static sf::Texture& getTexture(const std::string& filename)
    {
        auto& textures = getTextureMap();
        auto textureIterator = textures.find(filename);

        if (textureIterator == textures.end())
        {
            auto& texture = textures[filename];
            texture.loadFromFile(filename);
            return texture;
        }
        else
        {
            return textureIterator->second;
        }
    }

private:
    static std::unordered_map<std::string, sf::Texture>& getTextureMap()
    {
        static std::unordered_map<std::string, sf::Texture> textures;
        return textures;
    }
};

