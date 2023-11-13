//
// Created by Joseph Alai on 8/3/21.
//

#ifndef ENGINE_AABB_H
#define ENGINE_AABB_H

#include <glm/glm.hpp>

enum class BoundTypes {
    AABB = 0x00, // Axis Aligned Bounding Box
    SPHERE = 0x01,
};

class AABB {

public:
    BoundTypes type;
    // sphere values
    glm::vec3 center;

    float radius;
    // bounding box values
    glm::vec3 min;

    glm::vec3 max;
    /*
     * Constructors
     */

    // initialize with type
    explicit AABB(BoundTypes type);

    // initialize as sphere
    AABB(glm::vec3 center, float radius);

    // initialize as AABB
    AABB(glm::vec3 min, glm::vec3 max);

    AABB();

    /*
     * Calculating values for the region
     */

    // center
    glm::vec3 calculateCenter();

    // calculate dimensions
    glm::vec3 calculateDimensions();

    /*
     * Testing Methods
     */

    // determines if point is inside
    bool containsPoint(glm::vec3 pt);

    // determines if region is inside of region
    bool containsRegion(AABB br);

    // determines if region intersects (partial containment)
    bool intersectsWith(AABB br);

};


#endif //ENGINE_AABB_H
