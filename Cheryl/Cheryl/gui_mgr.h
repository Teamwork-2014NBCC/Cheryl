#ifndef GUI_MGR_H
#define GUI_MGR_H

#include <vector>
#include "gui.h"


class window;


class GUI_Manager
{
private:
	std::vector<window*> windows;

public:
	void Draw();
};


class window
{
private:
	std::vector<element*> my_stuff;

public:
	void Draw();
};



#endif
