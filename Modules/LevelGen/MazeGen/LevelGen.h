#ifndef _LEVELGEN_H_
#define _LEVELGEN_H_

#include "../src/thebuilder.h"
#include "../src/Source.cpp"
#include "Tile.h"
#include "../Mesh_Loader/Mesh_Loader/S3DMesh.h"
#include <vector>
#include "Tile.h"
#include "../src/thebuilder.h"
#include <debug_toolset.h>
#include "../src/debug_funcs.h"



class LevelGeneration
{

public:
	


	thebuilder bob;
	maze_specs size;
	unsigned char **maze = bob.generate(size);
	int x;
	int y;
	std::vector <tile *> tileList;
	void DrawMap();
	inline void loadmap(unsigned char **maze, maze_specs size, coords cursor);
	void GenerateLevel();

};









#endif