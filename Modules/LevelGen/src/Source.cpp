#include "thebuilder.h"
#include <debug_toolset.h>
#include "debug_funcs.h"

using namespace dbg;

void main()
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
	draw(maze, size, std::make_pair(0,0));
	system("pause");
	dbg::FileLog_Mgr::Stop();
}

inline void draw(unsigned char **maze, maze_specs size, coords cursor)
{
	system("cls");
	std::stringstream buffer;
	for ( int y = size.second - 1; y >= 0; --y )
	{
		for ( int x = 0; x < size.first; ++x )
		{
			if ( (x == cursor.first) && (y == cursor.second) )
			{
				buffer << "^";
			}
			else
			{
				switch ( maze[x][y] )
				{
					case 0:
						buffer << " ";
						break;
					case 1:
						buffer << "#";
						break;
					default:
						buffer << "X";
						break;
				}
			}
		}
		buffer << std::endl;
	}
	std::cout << buffer.str();
	//char c;
	//std::cin >> c;
}