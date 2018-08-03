#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class ResourceManager
{
private:
	static std::map<std::string, sf::Texture> m_textures;

public:
	static void loadTexture(const std::string& name, const std::string& filename);
	static const sf::Texture& getTexture(const std::string& name);

	static void unloadTextures();
};
