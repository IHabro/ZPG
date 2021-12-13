#pragma once

#include "AbstractObserver.h"
#include "ShaderProgram.h"

class ShaderProgram; //dopredna deklarace (z duvodu krizoveho odkazu)

class Camera : public Subject
{
private:
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;

public:
    Camera();
    Camera(glm::vec3, glm::vec3, glm::vec3);
    ~Camera();

    //Methods
    void SetCamera(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
    void ToFront(); //Towards vision
    void ToBack();
    void ToLeft();
    void ToRight();
    void MouseMove(double new_x, double new_y, int width, int height);

    //Get Methods
    glm::mat4 GetCamera();
    glm::vec3 GetCameraPosition();
    glm::vec3 GetTarget();
};
