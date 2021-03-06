// DonkeyKong.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Game.h"

int main()
{

	auto getMap = [](std::string path) -> std::vector<std::string> {

		std::vector<std::string> map = {};
		std::ifstream input;
		std::string line;
		bool success = false;
		std::string errorString = "";

		input.open(path);

		if (!input.is_open()) {
			errorString = "Could not open " + path;
			goto clean;
		}

		while (std::getline(input, line))
			map.push_back(line);

		success = true;

	clean:

		if (input.is_open())
			input.close();

		if (!success)
			throw std::runtime_error(errorString);

		return map;
	};

	try {

		std::vector<std::vector<std::string>> levels;
		levels.push_back(getMap("Levels/level1"));
		levels.push_back(getMap("Levels/level2"));
		levels.push_back(getMap("Levels/level3"));

		Game game(levels);
		game.run();

	} catch (std::runtime_error e) {
		MessageBoxA(NULL, e.what(), "Error", MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}

	return 0;
}
