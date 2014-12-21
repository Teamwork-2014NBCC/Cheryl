#include "global.h"
#include "thebuilder.h"

dir_generator RDGenerator;

void **Matrix2D( int ncols, int  nrows, int element_size, int first_row = 0, int first_col = 0 )
{
	//nrows and ncols are the total number of rows and columns,first_row and first_col are the starting rows and columns(default is 0,it can be negative too !!)
	void **p;
	int alignment;
	long i;

	if ( ncols < 1 || nrows < 1 ) { return( NULL ); }

	i = ncols*sizeof( void * );
	//  align the addr of the data to be a multiple of sizeof(long double),this helps easy fetching and fast processing in some processors
	alignment = i % sizeof( long double );
	if ( alignment != 0 )
	{
		alignment = sizeof(long double) -alignment;
	}

	i += ncols*nrows*element_size+alignment;
	p = (void **) malloc( (size_t) i );

	if ( p!= NULL )
	{
		//compute the address of matrix[first_row][0]
		p[0] = (char *) ( p+ncols )+alignment-first_row*element_size;
		for ( i = 1; i < ncols; i++ )
			// compute the address of matrix[first_row+i][0]
			p[i] = (char *) ( p[i-1] )+nrows*element_size;
		//compute the address of matrix[0][0]
		p -= first_col;
	}
	else
		//cout<<"Memory allocation failure"<<endl;
		exit( -20 );

	return( p );
}

char **thebuilder::generate( maze_specs& gen_size )
{
REGENERATEMAZE:
	RDGenerator.seed_me();
	Cartographer.Reset();
	int& x = gen_size.first;
	int& y = gen_size.second;
	x = x % 2 ? x : x + 1;
	y = y % 2 ? y : y + 1;
	size.first = x;
	size.second = y;

	LOGFILE1( logDEBUG1 ) << "Maze size is now: " << coords_ToString( size );
	if ( maze != nullptr )
	{
		delete maze;
		LOGFILE1( logINFO ) << "Previous maze has been deleted";
	}
	maze = (char**) Matrix2D( x, y, sizeof( char ) );
	LOGFILE1( logINFO ) << "Maze Array generated";

	//Initialization - First Stage (Values)
	coords loop_pos;
	short& ix = loop_pos.first;
	short& iy = loop_pos.second;
	LOGFILE1( logINFO ) << "About to begin the Initialization Loop";
	for ( ix = 0; ix < x; ++ix )
	{
		for ( iy = 0; iy < y; ++iy )
		{
			//Cells of the maze need initial values
			LOGFILE1( logDEBUG4 ) << "Initialization Loop: " << coords_ToString( loop_pos );
			maze[ix][iy] = 1;
			Cartographer.Register_Cell( loop_pos );
		}
	}

	char state = 0;
	//Initialization - Second Stage (Visited Cells)
	LOGFILE1( logINFO ) << "Commencing Border Initialization - Entering first stage";
	for ( ix = 1, iy = 0; iy != -1; )
	{
		Cartographer << loop_pos;
		switch ( state )
		{
			case 0:
				++ix;
				if ( ( ix + 1 ) == x )
				{
					++state;
					LOGFILE1( logINFO ) << "Border Init: Entering second stage @" << coords_ToString( loop_pos );
				}
				break;

			case 1:
				++iy;
				if ( ( iy + 1 ) == y )
				{
					++state;
					LOGFILE1( logINFO ) << "Border Init: Entering Third stage @" << coords_ToString( loop_pos );
				}
				break;

			case 2:
				--ix;
				if ( ix == 0 )
				{
					++state;
					LOGFILE1( logINFO ) << "Border Init: Entering Fourth and FINAL stage @" << coords_ToString( loop_pos );
				}
				break;

			case 3:
				--iy;
				break;
		}
	}

	//Initialization - Third Stage (Entrance)
	seed_value2 = time( NULL );
	//srand( 1417031426 );
	//seed_value2 = 1417629337;
	srand( seed_value2 );
	int tx, ty;
	LOGFILE1( logINFO ) << "About to randomly select one of the 4 BORDERS to form an entrance on";
	
	char start_val = 1;
	switch ( rand() % 4 ) //The maze needs a start and finish
	{
		case 0: // Top
			tx = rand() % ( x - 1 );
			LOGFILE1( logDEBUG1 ) << "X randomly chose: " << tx;
			tx = tx % 2 ? tx : ( tx <= ( x / 2 ) ? tx + 1 : tx - 1 );
			LOGFILE1( logDEBUG1 ) << "X is now: " << tx;

			maze[tx][y - 1] = start_val;
			position.first = tx;
			position.second = y - 1;
			LOGFILE1( logINFO ) << "Position chosen @" << coords_ToString( position );

			Cartographer.Register_Cell( position, true );
			current_path.emplace( position );
			break;

		case 1: // Right
			ty = rand() % ( y - 1 );
			LOGFILE1( logDEBUG1 ) << "Y randomly chose: " << ty;
			ty = ty % 2 ? ty : ( ty <= ( y/ 2 ) ? ty + 1 : ty - 1 );
			LOGFILE1( logDEBUG1 ) << "Y is now: " << ty;

			maze[x - 1][ty] = start_val;
			position.first = x - 1;
			position.second = ty;
			LOGFILE1( logINFO ) << "Position chosen @" << coords_ToString( position );
			Cartographer.Register_Cell( position, true );
			current_path.emplace( position );
			break;

		case 2: // Bottom
			tx = rand() % ( x - 1 );
			LOGFILE1( logDEBUG1 ) << "X randomly chose: " << tx;
			tx = tx % 2 ? tx : ( tx <= ( x / 2 ) ? tx + 1 : tx - 1 );
			LOGFILE1( logDEBUG1 ) << "X is now: " << tx;

			maze[tx][0] = start_val;
			position.first = tx;
			position.second = 0;
			LOGFILE1( logINFO ) << "Position chosen @" << coords_ToString( position );
			Cartographer.Register_Cell( position, true );
			current_path.emplace( position );
			break;

		case 3: // Left
			ty = rand() % ( y - 1 );
			LOGFILE1( logDEBUG1 ) << "Y randomly chose: " << ty;
			ty = ty % 2 ? ty : ( ty <= ( y/ 2 ) ? ty + 1 : ty - 1 );
			LOGFILE1( logDEBUG1 ) << "Y is now: " << ty;

			maze[0][ty] = start_val;
			position.first = 0;
			position.second = ty;
			LOGFILE1( logINFO ) << "Position chosen @" << coords_ToString( position );
			Cartographer.Register_Cell( position, true );
			current_path.emplace( position );
			break;

		default:
			//Something bad happened
			LOGFILE1( logFATAL ) << "rand() % 4 gave something not 0~3";
			break;
	}

	// Post-Initialization
	// Start putting up walls, building paths
	int Area = ( x*y );// -(2 * x) - (2 * y) + 2;

	LOGFILE1( logINFO ) << "About to start building!! Hard Hats on :3";
	while ( Cartographer.Count() != Area )
	{
		if ( current_path.size() == 0 && Cartographer.Count() > 4 )
		{
			goto REGENERATEMAZE;
		}
		//LOGFILE1(logINFO) << "Draw state of maze (aka draw maze to screen)";
		//draw(maze, size, position);
		LOGFILE1( logINFO ) << "About to start building a path";
		build_path();
		paths.push_back( current_path );

		LOGFILE1( logINFO ) << "Calling backtrack()";
		if ( backtrack() )
		{
			LOGFILE1( logDEBUG1 ) << "backtrack() succeeded";
			position = current_path.top();
			LOGFILE1( logDEBUG1 ) << "backtrack() found:" << coords_ToString( position );
		}
		else
		{
			LOGFILE1( logDEBUG1 ) << "backtrack() failed";
		}
		//draw( maze, size, std::make_pair( 0, 0 ) );
		seed_value;
	}
	return maze;
}

inline direction thebuilder::get_directions()
{
	short &x = position.first;
	short &y = position.second;

	direction R = 0;
	LOGFILE1( logINFO ) << "\tGetting Directions....";
	for ( int i = 0; i < 4; ++i )
	{
		short ix, iy;
		int j = 1 << ( 2 * i );
		switch ( j )
		{
			case UP:
				iy = y + 1;
				if ( ( ( x % 2 ) == 1 ) && ( ( iy ) < size.second ) )
				{
					LOGFILE1( logDEBUG1 ) << "Get Direction:\t North on (x, iy) " << coords_ToString( std::make_pair( x, iy ) ) << " is acceptable";
					if ( !Cartographer.Check_Cell( std::make_pair( x, iy ) ) )
					{
						R |= UP;
					}
				}
				break;

			case RIGHT:
				ix = x + 1;
				if ( ( ( y % 2 ) == 1 ) && ( ( ix ) < size.first ) )
				{
					LOGFILE1( logDEBUG1 ) << "Get Direction:\t East on (ix, y) " << coords_ToString( std::make_pair( ix, y ) ) << " is acceptable";
					if ( !Cartographer.Check_Cell( std::make_pair( ix, y ) ) )
					{
						R |= RIGHT;
					}
				}
				break;

			case DOWN:
				iy = y - 1;
				if ( ( ( x % 2 ) == 1 ) && ( ( iy ) >= 0 ) )
				{
					LOGFILE1( logDEBUG1 ) << "Get Direction:\t South on (x, iy) " << coords_ToString( std::make_pair( x, iy ) ) << " is acceptable";
					if ( !Cartographer.Check_Cell( std::make_pair( x, iy ) ) )
					{
						R |= DOWN;
					}
				}
				break;

			case LEFT:
				ix = x - 1;
				if ( ( ( y % 2 ) == 1 ) && ( ( ix ) >= 0 ) )
				{
					LOGFILE1( logDEBUG1 ) << "Get Direction:\t West on (ix, y) " << coords_ToString( std::make_pair( ix, y ) ) << " is acceptable";
					if ( !Cartographer.Check_Cell( std::make_pair( ix, y ) ) )
					{
						R |= LEFT;
					}
				}
				break;

			default:
				break;
		}
	}
	LOGFILE1( logDEBUG1 ) << "Get Direction:\t Direction Return = " << (int) R;
	return R;
}

inline void thebuilder::build_path()
{
	while ( RDGenerator << get_directions() )
	{
		//draw( maze, size, position );
		LOGFILE1( logINFO ) << "Build Path: Choosing direction";
		switch ( RDGenerator.rnd() )
		{
			case UP:
				build_up();
				break;

			case RIGHT:
				build_right();
				break;

			case DOWN:
				build_down();
				break;

			case LEFT:
				build_left();
				break;

			default:
				break;
		}
		//LOGFILE1(logINFO) << "It is important to see where you are going (draw maze())";
		//draw(maze, size, position);
		LOGFILE1( logINFO ) << "Build Path: Adding position to PATH HISTORY" << coords_ToString( position );
		current_path.emplace( position );
	}
}

inline void thebuilder::build_up()
{
	LOGFILE1( logINFO ) << "Building Up(North)";
	short &x = position.first;
	short &y = position.second;
	//LOGFILE1(logDEBUG2) << "Marking as visited at: " << coords_ToString(position);
	//Cartographer << position;
	maze[x][++y] = 0;
	LOGFILE1( logDEBUG2 ) << "Moving to: " << coords_ToString( position );
	tour();
}

inline void thebuilder::build_down()
{
	LOGFILE1( logINFO ) << "Building Down(South)";
	short &x = position.first;
	short &y = position.second;
	//LOGFILE1(logDEBUG2) << "Marking as visited at: " << coords_ToString(position);
	//Cartographer << position;
	maze[x][--y] = 0;
	LOGFILE1( logDEBUG2 ) << "Moving to: " << coords_ToString( position );
	tour();
}

inline void thebuilder::build_left()
{
	LOGFILE1( logINFO ) << "Building Left(West)";
	short &x = position.first;
	short &y = position.second;
	//LOGFILE1(logDEBUG2) << "Marking as visited at: " << coords_ToString(position);
	//Cartographer << position;
	maze[--x][y] = 0;
	LOGFILE1( logDEBUG2 ) << "Moving to: " << coords_ToString( position );
	tour();
}

inline void thebuilder::build_right()
{
	LOGFILE1( logINFO ) << "Building Right(East)";
	short &x = position.first;
	short &y = position.second;
	//LOGFILE1(logDEBUG2) << "Marking as visited at: " << coords_ToString(position);
	//Cartographer << position;
	maze[++x][y] = 0;
	LOGFILE1( logDEBUG2 ) << "Moving to: " << coords_ToString( position );
	tour();
}

inline void thebuilder::tour()
{
	const coords last = current_path.top();// write code to deal with this
	coords tourist = last;
	LOGFILE1( logINFO ) << "Tour: Position: " << coords_ToString( tourist );

	const short Lx = last.first;
	const short Ly = last.second;
	const short Cx = position.first;
	const short Cy = position.second;
	short& Tx = tourist.first;
	short& Ty = tourist.second;

	short left, right, up, down;
	left = last.first - 1;
	left = left >= 0 ? left : 0;

	right = last.first + 1;
	right = right < size.first ? right : size.first - 1;

	up = last.second + 1;
	up = up < size.second ? up : size.second - 1;

	down = last.second - 1;
	down = down >= 0 ? down : 0;

	LOGFILE1( logDEBUG1 )  << "Tour: X axis <=> " << "Left: " << left << " - Right: " << right;
	LOGFILE1( logDEBUG1 ) << "Tour: Y axis <=> " << "Up: " << up << " - Down: " << down;

	LOGFILE1( logINFO ) << "Marking LAST cell as visited";
	Cartographer << tourist;

	if ( Cx == Lx )
	{
		//Evidence of vertical movements
		if ( Ly < Cy )
		{
			//North movement verified
			LOGFILE1( logINFO ) << "Tour: Visiting bottom half";
			Tx = left;
			Cartographer << tourist;
			Ty = down;
			Cartographer << tourist;
			Tx = Lx;
			Cartographer << tourist;
			Tx = right;
			Cartographer << tourist;
			Ty = Ly;
			Cartographer << tourist;
		}
		else
		{
			//South movement assumed
			LOGFILE1( logINFO ) << "Tour: Visiting top half";
			Tx = left;
			Cartographer << tourist;
			Ty = up;
			Cartographer << tourist;
			Tx = Lx;
			Cartographer << tourist;
			Tx = right;
			Cartographer << tourist;
			Ty = Ly;
			Cartographer << tourist;
		}
	}
	else if ( Cy == Ly )
	{
		//Evidence of horizontal movements
		if ( Lx < Cx )
		{
			//East movement verified
			LOGFILE1( logINFO ) << "Tour: Visiting left half";
			Ty = up;
			Cartographer << tourist;
			Tx = left;
			Cartographer << tourist;
			Ty = Ly;
			Cartographer << tourist;
			Ty = down;
			Cartographer << tourist;
			Tx = Lx;
			Cartographer << tourist;
		}
		else
		{
			//West movement assumed
			LOGFILE1( logINFO ) << "Tour: Visiting right half";
			Ty = up;
			Cartographer << tourist;
			Tx = right;
			Cartographer << tourist;
			Ty = Ly;
			Cartographer << tourist;
			Ty = down;
			Cartographer << tourist;
			Tx = Lx;
			Cartographer << tourist;
		}
	}
}

inline bool thebuilder::backtrack()
{
	if ( current_path.size() > 0 )
	{
		Cartographer << current_path.top();
	}
	while ( current_path.size() > 0 )
	{
		current_path.pop();
		LOGFILE1( logINFO ) << "Backtrack:\t Removed top Cell from Stack";
		if ( current_path.size() == 0 )
		{
			return false;
		}
		coords temp = current_path.top();
		LOGFILE1( logINFO ) << "Backtrack:\t Acquired top Cell from Stack: " << coords_ToString( temp );
		short &x = temp.first;
		short &y = temp.second;
		//draw(maze, size, temp);
		//system("pause");
		int i = rand() % 4;
		for ( int count = 0; count < 4; ++count )
		{
			int ix = 0, iy = 0;
			int j = 1 << ( 2 * i++ );
			i = i <= 4 ? i : 0;
			switch ( j )
			{
				case UP:
					iy = y + 2;
					if ( ( ( x % 2 ) == 1 ) && ( ( iy ) < size.second ) )
					{
						LOGFILE1( logDEBUG1 ) << "Backtrack:\t North on (x, iy) " << coords_ToString( std::make_pair( x, iy ) ) << " is acceptable";
						if ( !Cartographer.Check_Cell( std::make_pair( x, iy ) ) )
						{
							maze[x][--iy] = 0;
							current_path.emplace( std::make_pair( x, iy ) );
							return true;
						}
					}
					break;

				case RIGHT:
					ix = x + 2;
					if ( ( ( y % 2 ) == 1 ) && ( ( ix ) < size.first ) )
					{
						LOGFILE1( logDEBUG1 ) << "Backtrack:\t East on (ix, y) " << coords_ToString( std::make_pair( ix, y ) ) << " is acceptable";
						if ( !Cartographer.Check_Cell( std::make_pair( ix, y ) ) )
						{
							maze[--ix][y] = 0;
							current_path.emplace( std::make_pair( ix, y ) );
							return true;
						}
					}
					break;

				case DOWN:
					iy = y - 2;
					if ( ( ( x % 2 ) == 1 ) && ( ( iy ) >= 0 ) )
					{
						LOGFILE1( logDEBUG1 ) << "Backtrack:\t South on (x, iy) " << coords_ToString( std::make_pair( x, iy ) ) << " is acceptable";
						if ( !Cartographer.Check_Cell( std::make_pair( x, iy ) ) )
						{
							maze[x][++iy] = 0;
							current_path.emplace( std::make_pair( x, iy ) );
							return true;
						}
					}
					break;

				case LEFT:
					ix = x - 2;
					if ( ( ( y % 2 ) == 1 ) && ( ( ix ) >= 0 ) )
					{
						LOGFILE1( logDEBUG1 ) << "Backtrack:\t West on (ix, y) " << coords_ToString( std::make_pair( ix, y ) ) << " is acceptable";
						if ( !Cartographer.Check_Cell( std::make_pair( ix, y ) ) )
						{
							maze[++ix][y] = 0;
							current_path.emplace( std::make_pair( ix, y ) );
							return true;
						}
					}
					break;

				default:
					break;
			}
		}
	}
	return false;
}