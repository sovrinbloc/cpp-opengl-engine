//
// Created by Joseph Alai on 7/3/21.
//

#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H

#include "glm/glm.hpp"

struct Lighting {
    glm::vec3 ambient;
    glm::vec3 diffuse;

    float constant;
    float linear;
    float quadratic;
};

class Light {
private:
    glm::vec3 position;

    glm::vec3 color;

    Lighting lighting;

public:

    constexpr static float kDirectional = -1.0f;

public:
    /**
     * @brief Light stores the details of each light. Position, color, and if it's a spot or
     *        directional light.
     * @param position
     * @param color
     * @param lighting
     */
    explicit Light(glm::vec3 position = glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f),
                   Lighting lighting = {
                           .ambient =  glm::vec3(0.2f, 0.2f, 0.2f),
                           .diffuse =  glm::vec3(0.5f),
                           .constant = 1.0f,
                           .linear = 0.09f,
                           .quadratic = 0.032f
                   });

    Lighting getLighting();

    void setLighting(const Lighting &lighting);

    glm::vec3 &getPosition();

    void setPosition(glm::vec3 position);

    void addToPosition(glm::vec3 position);

    glm::vec3 &getColor();

    void setColor(glm::vec3 color);

};

#endif //ENGINE_LIGHT_H
