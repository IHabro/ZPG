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

//PointDataWithTexture
struct PointDataWithTexture
{
	Coordinates corr;
	Vector		norm;
	Texture		text;
};

struct Vertex
{
	float posi[3];
	float norm[3];
	float text[2];
	//float tang[3];
};

