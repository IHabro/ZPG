#pragma once

struct Coordinates
{
	float x;
	float y;
	float z;
	float d4;
};

struct Colour
{
	float r;
	float g;
	float b;
	float a;
};

struct PointData
{
	Coordinates corr;
	Colour colour;
};
