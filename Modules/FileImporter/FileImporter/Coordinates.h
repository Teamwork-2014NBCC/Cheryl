#ifndef _COORDINATES_H_
#define _COORDINATES_H_

#include <stdlib.h>

class Coordinates
{
public:
	float x, y, z;

	Coordinates(float newx, float newy, float newz)
	{
		x = newx;
		y = newy;
		z = newz;
	}
	~Coordinates()
	{
	}
};

class Indices
{
public:
	Coordinates* vertices;
	Coordinates* normals;
	Coordinates* UVs;
	int index;

	Indices(Coordinates* v, Coordinates* n, Coordinates* uv, int i)
	{
		vertices = v;
		normals = n;
		UVs = uv;
		index = i;
	}
	~Indices()
	{
	}
};
#endif