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

struct Texture
{
	float u;
	float v;
};
/*
//colour from 2D
struct Colour
{
	float r;
	float g;
	float b;
};
*/

struct PointData
{
	Coordinates corr;
	Vector		norm;
};

//PointDataWithTexture
struct PointDataWithTexture
{
	Coordinates corr;
	Vector		norm;
	Texture		text;
};



