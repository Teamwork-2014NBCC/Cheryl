#include "Player.h"


//this code sets up memory leak detection
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif


#include "global.h"

string school = "C:/Users/1039652/Documents/Programming Classes/";
string home = "D:/All Classes/Programming Classes/";
string file1 = "";
string file2 = "";


void main()
{

	//the line below turns on memory leak detection in debug mode
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	srand(time(NULL));


	get_blit3d()->SetInit(Init);
	get_blit3d()->SetDeInit(DeInit);
	get_blit3d()->SetUpdate(Update);
	get_blit3d()->SetDraw(Draw);
	get_blit3d()->SetDoInput(DoInput);
	get_blit3d()->SetDoCursor(DoCursor);

	//Run() blocks until the window is closed
	get_blit3d()->Run(Blit3DThreadModel::SIMPLEMULTITHREADED);

	system("pause");


}