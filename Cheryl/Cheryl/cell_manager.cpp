#include "cell_manager.h"
#include "log.h"

using namespace dbg;

void cell_mgr::operator<<(coords position)
{
	LOGFILE1(logDEBUG3) << "Cell sent to Cartographer: " << coords_ToString(position);
	std::map<coords, bool>::iterator itr = Cells.find(position);

	if ( !itr->second )
	{
		LOGFILE1(logDEBUG3) << "Cartographer:\t Marking Visited";
		itr->second = true;
		Cells_Visited++;
	}
}

void cell_mgr::Register_Cell(coords position, bool visited)
{
	auto TempVar = Cells.emplace(position, visited);
	if ( !TempVar.second )
	{
		LOGFILE1(logDEBUG3) << "Cartographer:\t Cell already REGISTERED @ " << coords_ToString(position);
		// No addition was made to the Map
		if ( !TempVar.first->second && visited )
		{
			LOGFILE1(logDEBUG3) << "Cartographer:\t Marking Visited ";
			Cells_Visited++;
		}
		TempVar.first->second = visited;
	}
	else
	{
		LOGFILE1(logDEBUG3) << "Cartographer:\t Cell being REGISTERED @ " << coords_ToString(position);
		// Added position to Map
		if ( visited )
		{
			LOGFILE1(logDEBUG3) << "Cartographer:\t Marking Visited ";
			Cells_Visited++;
		}
	}
}

bool cell_mgr::Check_Cell(coords reference_point)
{
	if ( Cells[reference_point] )
	{
		LOGFILE1(logDEBUG3) << "Cartographer:\t Check Cell: True @ " << coords_ToString(reference_point);
		return true;
	}
	LOGFILE1(logDEBUG3) << "Cartographer:\t Check Cell: False @ " << coords_ToString(reference_point);
	return false;
}

int cell_mgr::Count()
{
	LOGFILE1(logDEBUG1) << "Cartographer:\t Total Cells Visited: " << Cells_Visited;
	return Cells_Visited;
}

void cell_mgr::Reset()
{
	Cells_Visited = 0;
	Cells.clear();
	while ( !Q_Branch.empty() )
	{
		Q_Branch.pop();
	}
}
