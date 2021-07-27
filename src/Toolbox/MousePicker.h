//
// Created by Joseph Alai on 7/21/21.
//

#ifndef ENGINE_MOUSEPICKER_H
#define ENGINE_MOUSEPICKER_H

#include "glm/glm.hpp"
#include "../Entities/CameraInput.h"
#include "Picker.h"

/**
 * Based on the OpenGL ThinMatrix Tutorial and ...
 * https://antongerdelan.net/opengl/raycasting.html
 */
class MousePicker : public Picker{
protected:
    glm::vec3 currentRay;

    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    Camera *camera;

public:

    MousePicker(Camera *cam, glm::mat4 projection);
    glm::vec3 getCurrentRay();
    virtual void update();
    static glm::vec3 getPointOnRay(glm::vec3 ray, float distance, Camera *camera);
};


#endif //ENGINE_MOUSEPICKER_H
