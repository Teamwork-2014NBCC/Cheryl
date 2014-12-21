#include "level_gen.h"
#include "global.h"

Wall::Wall( SceneNode* level_root, int x, int y )
{
	tile_root = new SceneNode( level_root );
	TransformerNode* displacer = new TransformerNode( tile_root );
	TransformerNode* rotator = new TransformerNode( displacer );
}

Wall::~Wall()
{
	delete tile_root;
}

Floor::Floor( SceneNode* level_root, int x, int y )
{
	tile_root = new SceneNode( level_root );
	TransformerNode* displacer = new TransformerNode( tile_root );
	TransformerNode* rotator = new TransformerNode( displacer );
}

Floor::~Floor()
{
	delete tile_root;
}

bool Dungeon::canMove( int x, int y )
{
	if ( x < 0 || x >= size.first )
	{
		return false;
	}
	else if ( y < 0 || y >= size.second )
	{
		return false;
	}
	return !map[x][y].isWall();

}

void Dungeon::Generate( int width, int height )
{
	thebuilder bob;
	size.first = width;
	size.second = height;

	char** raw_map = bob.generate( size );
	if ( map )
	{
		delete map;
	}
	map = (Tile**)Matrix2D( width, height, sizeof( Tile ), 0, 0 );

	for ( int x = 0; x < width; ++x )
	{
		for ( int y = height - 1; y >= 0; --y )
		{
			switch ( raw_map[x][y] )
			{
				case 0:
					map[x][y] = Floor( this->level_root, x, y );
					break;
				case 1:
					map[x][y] = Wall( this->level_root, x, y );
					break;
				default:
					map[x][y] = Wall( this->level_root, x, y );
					break;
			}
		}
	}
	delete raw_map;
	raw_map = nullptr;
}



