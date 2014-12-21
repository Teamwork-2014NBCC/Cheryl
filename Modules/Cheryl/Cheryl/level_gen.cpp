#include "level_gen.h"
#include "global.h"

Wall::Wall( SceneNode* level_root, int x, int y )
{
	tile_root = new SceneNode( level_root );

	TransformerNode* displacer = new TransformerNode( tile_root );
	RotatorNode* rotator = new RotatorNode( displacer, true, true, true );
	rotator->Set_Mesh( get_game_engine().mesh_mgr.Get_Mesh( "box.s3d" ) );
	
	glm::vec3 axis;
	axis.x = 1;
	displacer->Transform( x, axis );
	axis.x = 0;
	axis.y = 1;
	displacer->Transform( y, axis );
	axis.y = 0;
	axis.z = 1;
	displacer->Transform( 1, axis );/**/
}

Wall::~Wall()
{
	delete tile_root;
}

Floor::Floor( SceneNode* level_root, int x, int y )
{
	tile_root = new SceneNode( level_root );

	TransformerNode* displacer = new TransformerNode( tile_root );
	RotatorNode* rotator = new RotatorNode( displacer, true, true, true );
	//rotator->Set_Mesh( get_game_engine().mesh_mgr.Get_Mesh( "box.s3d" ) );

	glm::vec3 axis;
	axis.x = 1;
	displacer->Transform( x, axis );
	axis.x = 0;
	axis.y = 1;
	displacer->Transform( y, axis );/**/
}

Floor::~Floor()
{
	delete tile_root;
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
	map = (Tile***)Matrix2D( width, height, sizeof( Tile* ), 0, 0 );

	for ( int x = 0; x < width; ++x )
	{
		for ( int y = height - 1; y >= 0; --y )
		{
			switch ( raw_map[x][y] )
			{
				case 0:
					map[x][y] = new Floor( this->level_rotator, x, y );
					break;
				case 1:
					map[x][y] = new Wall( this->level_rotator, x, y );
					break;
				default:
					map[x][y] = new Wall( this->level_rotator, x, y );
					break;
			}
		}
	}
	delete raw_map;
	raw_map = nullptr;
	level_transformer->Trickle_Down_Data();
}

Dungeon::Dungeon( Root_SceneNode* root )
{
	size.first = 10;
	size.second = 10;
	level_root = new SceneNode( root );
	level_transformer = new TransformerNode( level_root );

	glm::vec3 axis;
	axis.z = -1;
	level_transformer->Transform( 30, axis );
	axis.z = 0;
	axis.x = 1;
	//level_transformer->Transform( 30, axis );
	axis.x = 0;
	axis.y = 1;
	//level_transformer->Transform( 30, axis );

	level_rotator = new RotatorNode( level_transformer, true, true, true );
}

void Dungeon::Descend()
{
	size.first++;
	size.second++;
	Generate();
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
	return !map[x][y]->isWall();

}
