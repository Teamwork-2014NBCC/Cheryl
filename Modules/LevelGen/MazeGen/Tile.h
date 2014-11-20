#ifndef _TILE_H_
#define _TILE_H_
#include "../Mesh_Loader/Mesh_Loader/S3DMesh.h"

enum tiletype
{
	FloorTile = 0,
	WallTile = 1,
	StartTile = 2,
	EndTile = 3
};

struct tile
{
	int posX;
	int posY;
	tiletype type;
	S3DMesh *Mesh;
	bool isWall();


};




#endif 