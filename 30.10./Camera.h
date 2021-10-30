#pragma once

#include "ShaderProgram.h"

class ShaderProgram; //dopredna deklarace (z duvodu krizoveho odkazu)

class Camera
{
private:
    ShaderProgram* shader;
public:
    Camera(ShaderProgram* sh);
    ~Camera();
    void GetCamera();
    void ToFront();
    void ToLeft();
};
