//
// Created by Joseph Alai on 7/1/21.
//

#ifndef ENGINE_MATHS_H
#define ENGINE_MATHS_H
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
class Maths {
public:
    static glm::mat4 createTransformation(glm::vec3 translation = glm::vec3(1.0f), glm::vec3 rotation = glm::vec3(0.0f), float scale = 1.0f) {
        glm::mat4 matrix (1.0f);
        matrix = glm::translate(matrix, translation);
        matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
        matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
        matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
        return glm::scale(matrix, glm::vec3(scale));
    }
};
#endif //ENGINE_MATHS_H
