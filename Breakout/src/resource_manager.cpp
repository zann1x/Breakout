#include "resource_manager.h"

std::map<std::string, sf::Texture> ResourceManager::m_textures;
std::map<std::string, Text> ResourceManager::m_texts;
std::map<std::string, sf::Font> ResourceManager::m_fonts;

void ResourceManager::loadTexture(const std::string& name, const std::string& filename)
{
	if (m_textures.find(name) == m_textures.end())
	{
		sf::Texture texture;
		texture.loadFromFile(filename);
		m_textures[name] = texture;
	}
}

sf::Texture& ResourceManager::getTexture(const std::string& name)
{
	return m_textures[name];
}

void ResourceManager::loadText(const std::string& name, const std::string& str, const std::string& fontname)
{
	if (m_fonts.find(fontname) == m_fonts.end())
	{
		sf::Font font;
		font.loadFromFile(fontname);
		m_fonts[fontname] = font;
	}
	if (m_texts.find(name) == m_texts.end())
	{
		Text text;
		text.setFont(m_fonts[fontname]);
		text.setString(str);
		m_texts[name] = text;
	}
}

Text& ResourceManager::getText(const std::string& name)
{
	return m_texts[name];
}

void ResourceManager::unloadResources()
{
	m_textures.clear();
	m_texts.clear();
	m_fonts.clear();
}
