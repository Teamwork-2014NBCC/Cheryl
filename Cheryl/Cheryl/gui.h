#ifndef GUI_H
#define GUI_H

struct region
{

};

class element
{
public:
	virtual void Draw() = 0;
};

class text : public element
{

};

class button : public element
{

};

class static_text : public text
{

};

class dynamic_text : public text
{

};

#endif
