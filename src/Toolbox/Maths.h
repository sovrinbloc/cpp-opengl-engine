//
// Created by Joseph Alai on 7/1/21.
//

#ifndef ENGINE_MATHS_H
#define ENGINE_MATHS_H
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
class Maths {
public:
    static glm::mat4 createTransformationMatrix(glm::vec3 translation = glm::vec3(1.0f), glm::vec3 rotation = glm::vec3(0.0f), float scale = 1.0f) {
        glm::mat4 matrix (1.0f);
        matrix = glm::translate(matrix, translation);
        matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
        matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
        matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
        return glm::scale(matrix, glm::vec3(scale));
    }

   static glm::mat4 createTransformationMatrix(glm::vec2 translation, glm::vec2 scale) {
        glm::mat4 matrix(1.0f);
        matrix = glm::translate(matrix, glm::vec3(translation.x, translation.y, 0));
        matrix = glm::scale(matrix, glm::vec3(scale.x, scale.y, 1.0f));
        return matrix;
    }

    static glm::mat4 createProjectionMatrix(float fovy = 45.0f, float width = 800.0f, float height = 600.0f, float zNear = 0.1f, float zFar = 100.0f) {
        return glm::perspective(glm::radians(fovy), static_cast<float>(width) / static_cast<float>(height), zNear,zFar);
    }

    static float barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) {
        float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
        float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
        float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
        float l3 = 1.0f - l1 - l2;
        return l1 * p1.y + l2 * p2.y + l3 * p3.y;
    }
};
#endif //ENGINE_MATHS_H
