#ifndef _COORDINATES_H_
#define _COORDINATES_H_

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
};

class Indices
{
public:
	Coordinates* vertices;
	Coordinates* normals;
	Coordinates* UVs;

	Indices(Coordinates* v, Coordinates* n, Coordinates* uv)
	{
		vertices = v;
		normals = n;
		UVs = uv;
	}
};
#endif