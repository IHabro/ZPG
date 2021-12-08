#pragma once

#include "Scene.h"

struct ShaderInfo
{
	const char* vertex;
	const char* fragment;
};

struct FactoryParams
{
	ShaderInfo shader;
	Scene* scene;
};