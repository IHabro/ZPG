#pragma once

struct Coordinates
{
	float x;
	float y;
	float z;
};

struct Vector
{
	float x;
	float y;
	float z;
};

//Colour from 2D
struct Colour
{
	float r;
	float g;
	float b;
};

struct PointData
{
	Coordinates corr;
	Vector normal;
	//Colour colour;
};



