#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

#include "text.h"

class ResourceManager
{
private:
	static std::map<std::string, sf::Texture> m_textures;
	static std::map<std::string, Text> m_texts;
	static std::map<std::string, sf::Font> m_fonts;

public:
	static void loadTexture(const std::string& name, const std::string& filename);
	static sf::Texture& getTexture(const std::string& name);

	static void loadText(const std::string& name, const std::string& str, const std::string& fontname);
	static Text& getText(const std::string& name);

	static void unloadResources();
};
