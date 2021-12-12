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

struct PointData
{
	Coordinates corr;
	Vector		norm;
};

struct Tangent
{
	float x;
	float y;
	float z;
};


struct PointDataWithTexture
{
	Coordinates corr;
	Vector		norm;
	Texture		text;
};

struct Vertex
{
	Coordinates corr;
	Vector		norm;
	Texture		text;
	Tangent		tang;
};



