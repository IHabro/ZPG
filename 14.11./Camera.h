#pragma once

#include "ShaderProgram.h"

class ShaderProgram; //dopredna deklarace (z duvodu krizoveho odkazu)

class Camera
{
private:
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;

public:
    Camera(/*ShaderProgram* sh*/);
    ~Camera();
    glm::mat4 GetCamera();
    void ToFront(); //Towards vision
    void ToBack();
    void ToLeft();
    void ToRight();
    void MouseMove(double new_x, double new_y, int width, int height);
    glm::vec3 GetCameraPosition();
};
