#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "game_object.h"

class LevelCreator
{
public:
	static std::vector<GameObject> create(const std::string& level)
	{
		std::vector<GameObject> gameObjects;
		std::string data;
		std::ifstream file(level);
		int x = 0, y = 0;

		while (!file.eof())
		{
			std::getline(file, data);
			x = 0;
			
			for (char ch : data)
			{
				GameObject rec;

				switch (ch)
				{
				case '0':
					rec.setType(BlockType::TYPE0);
					break;
				case '1':
					rec.setType(BlockType::TYPE1);
					break;
				case '2':
					rec.setType(BlockType::TYPE2);
					break;
				default:
					std::cout << "Block type unknown" << std::endl;
					continue;
					break;
				}

				rec.setPosition(x * rec.getSize().x, y * rec.getSize().y);
				gameObjects.push_back(rec);
				x++;
			}
			y++;
		}

		return gameObjects;
	}
};