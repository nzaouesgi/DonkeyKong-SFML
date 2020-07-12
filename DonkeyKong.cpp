// DonkeyKong.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Game.h"

int main()
{

	std::vector<std::string> map1;
	map1.push_back("################################################################################");
	map1.push_back("#................oooo...oooo........................................ooooo......#");
	map1.push_back("#.........###....oooo...................ooooo........ooooo..........#####..#####");
	map1.push_back("#p......#####....######.................ooooo........ooooo......#########..#####");
	map1.push_back("####.###########################o####................####################..#####");
	map1.push_back("#..............................#o####...............####.............####..#####");
	map1.push_back("#oooooo........................#oooo..............######.............####..#####");
	map1.push_back("#oooooo.m.#...oooo.............#oooo.....m.......#######.............####..#####");
	map1.push_back("###########...####.............#########################...................#####");
	map1.push_back("#.............######..........oooooo.........................oooooo........#####");
	map1.push_back("#.............##########......######.........................oooooo........#####");
	map1.push_back("#.....#ooo......m..........############...##....##...........oooooo........#####");
	map1.push_back("##....#######################################..#################################");
	map1.push_back("##.............................................................................#");
	map1.push_back("######..........ooooo..............#.........m............#....oooooo..........#");
	map1.push_back("########........ooooo..............########################....oooooo.........e#");
	map1.push_back("###############################..#########.........#############################");
	map1.push_back("................................................................................");

	std::vector<std::string> map2;
	map2.push_back("################################################################################");
	map2.push_back("#..............................ooooooo.........................................#");
	map2.push_back("#.............ooooooooo........ooooooo.........................................#");
	map2.push_back("#.............#########........ooooooo.........................ooooooooooooo...#");
	map2.push_back("#..............................#######.........................ooooooooooooo...#");
	map2.push_back("#p.....####ooooooom.......################.........oooooooo####.......m.....####");
	map2.push_back("###############################################....#############################");
	map2.push_back("#####............................ooooooo.......................................#");
	map2.push_back("#######..........................ooooooo.......................................#");
	map2.push_back("##########......................#ooooooo......m..............#.................#");
	map2.push_back("##################..............##############################............######");
	map2.push_back("#ooo.......................................###################...........#######");
	map2.push_back("#ooo......................ooooooo..........###################..........########");
	map2.push_back("#ooo......m..........#....#oooooo......m.................#####.........#########");
	map2.push_back("######################....####################################........##########");
	map2.push_back("#.......##############...............###ooooooo......................###########");
	map2.push_back("#e.........ooooo....##....m...##.....###ooooooo.....................############");
	map2.push_back("########...ooooo....############.....###########################################");
	map2.push_back("###########ooooo.....m...............###########################################");
	map2.push_back("################################################################################");

	std::vector<std::string> map3;
	map3.push_back("################################################################################");
	map3.push_back("#.....................................oooooo...........oooooooooooooo..........#");
	map3.push_back("#p...ooooooo........oooooo............oooooo...........oooooooooooooo..........#");
	map3.push_back("#############.......######.....m......######...........##############..........#");
	map3.push_back("#.........................############.........................................#");
	map3.push_back("#............ooooooo..............ooooooo......................................#");
	map3.push_back("#...........#ooomooo#............#ooomooo#...............#....m.#..............#");
	map3.push_back("#...........#########............#########...............########.......m......#");
	map3.push_back("#........................................................#####################.#");
	map3.push_back("#............ooooooooooooooo..............oooooooooo...........................#");
	map3.push_back("############.################.............oooooooooooo.........................#");
	map3.push_back("############.##################..........####.......oooo.......................#");
	map3.push_back("#............###################.......######.........ooooo....................#");
	map3.push_back("#oooooooooooo#####################...########...........oooooooooooooooo.......#");
	map3.push_back("#ooooooooooooooooooooooooooooooooooo#########.............oooooooooooooo.......#");
	map3.push_back("#m......m..m.###############################...............oooooooooooo.......e#");
	map3.push_back("#############################################...............####################");



	std::vector<std::vector<std::string>> maps;
	maps.push_back(map1);
	maps.push_back(map2);
	maps.push_back(map3);

	Game game(maps);
	game.run(0);
}
