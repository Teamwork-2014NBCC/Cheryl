#ifndef LEVEL_GEN_H
#define LEVEL_GEN_H

#include <vector>

#include "thebuilder.h"
#include "scene_nodes.h"

enum tiletype {
	FloorTile = 0,
	WallTile = 1,
	StartTile = 2,
	EndTile = 3
};

struct Tile
{
	SceneNode* tile_root = nullptr;
	tiletype type;
	bool occupied = false;
	bool isWall() const
	{
		if ( type == WallTile )
		{
			return true;
		}
		return false;
	}
};
struct Wall : Tile
{
	Wall( SceneNode* level_root, int x, int y );
	~Wall();
};
struct Floor : Tile
{
	Floor( SceneNode* level_root, int x, int y );
	~Floor();
};

class Dungeon
{
private:
	SceneNode* level_root = nullptr;
	TransformerNode* level_transformer = nullptr;
	RotatorNode* level_rotator = nullptr;

	maze_specs size;
	Tile*** map = nullptr;

protected:
	void Generate()
	{
		Generate( size.first, size.second );
	}
	void Generate( int width, int height );

public:
	Dungeon( Root_SceneNode* root );
	void Descend();
	bool canMove( int x, int y );
};

#endif