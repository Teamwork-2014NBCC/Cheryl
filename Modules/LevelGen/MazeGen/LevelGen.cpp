#include "LevelGen.h"
#include "Tile.h"

void LevelGeneration::GenerateLevel()
{
	dbg::FileLog_Mgr::RegisterNewLog(L"mazebuilder.log");
	dbg::FileLog_Mgr::RegisterNewLog(L"additional.log");
	dbg::FileLog_Mgr::Start();

	thebuilder bob;
	maze_specs size;
	size.first = 50;
	size.second = 20;
	LOGFILE1(logINFO) << "Maze sizes set" << coords_ToString(size);
	unsigned char **maze = bob.generate(size);
	draw(maze, size, std::make_pair(0, 0));
	system("pause");
	dbg::FileLog_Mgr::Stop();
}


inline void LevelGeneration::loadmap(unsigned char **maze, maze_specs size, coords cursor)
{



	system("cls");
	std::stringstream buffer;
	tile *New_Map_of_Tiles = new tile[size.first * size.second];
	int index;
	for (int y = size.second; y >= 0; --y)
	{
		for (int x = 0; x < size.first; ++x)
		{
			index++;
			tileList[index]->posX = x;
			tileList[index]->posY = y;
			tileList[index]->Mesh = nullptr;
			switch (maze[x][y])
			{
			case 0:
				tileList[index]->isWall = false;
				tileList[index]->type = FloorTile;
				break;
			case 1:
				tileList[index]->isWall = true;
				tileList[index]->type = WallTile;
				break;
			default:
				tileList[index]->isWall = false;
				tileList[index]->type = StartTile;
				break;
			}
		}
	}
}



