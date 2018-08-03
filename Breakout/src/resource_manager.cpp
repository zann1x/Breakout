#include "resource_manager.h"

std::map<std::string, sf::Texture> ResourceManager::m_textures;

void ResourceManager::loadTexture(const std::string& name, const std::string& filename)
{
	if (m_textures.find(name) == m_textures.end())
	{
		sf::Texture texture;
		texture.loadFromFile(filename);
		m_textures[name] = texture;
	}
}

const sf::Texture& ResourceManager::getTexture(const std::string& name)
{
	return m_textures[name];
}

void ResourceManager::unloadTextures()
{
	m_textures.clear();
}
