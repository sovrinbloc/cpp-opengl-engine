//
// Created by Joseph Alai on 8/3/21.
//

#ifndef ENGINE_BOUNDINGREGION_H
#define ENGINE_BOUNDINGREGION_H

#include <glm/glm.hpp>

enum class BoundTypes {
    AABB = 0x00, // Axis Aligned Bounding Box
    SPHERE = 0x01,
};

class BoundingRegion {

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
    explicit BoundingRegion(BoundTypes type);

    // initialize as sphere
    BoundingRegion(glm::vec3 center, float radius);

    // initialize as AABB
    BoundingRegion(glm::vec3 min, glm::vec3 max);

    BoundingRegion();

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
    bool containsRegion(BoundingRegion br);

    // determines if region intersects (partial containment)
    bool intersectsWith(BoundingRegion br);

};


#endif //ENGINE_BOUNDINGREGION_H
