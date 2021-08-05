//
// Created by Joseph Alai on 8/3/21.
//

#include "BoundingRegion.h"

/**
 * @brief initialize with type
 *
 * @param type
 */
BoundingRegion::BoundingRegion(BoundTypes type) : type(type) {}

/**
 * @brief initialize as sphere
 *
 * @param center
 * @param radius
 */
BoundingRegion::BoundingRegion(glm::vec3 center, float radius) :
        type(BoundTypes::SPHERE), center(center), radius(radius) {}

/**
 * @brief initialize as AABB
 *
 * @param min
 * @param max
 */
BoundingRegion::BoundingRegion(glm::vec3 min, glm::vec3 max) :
        type(BoundTypes::AABB), min(min), max(max) {}

/*
* Calculating values for the region
*/

/**
 * @brief center
 *
 * @return
 */
glm::vec3 BoundingRegion::calculateCenter() {
    return (type == BoundTypes::SPHERE) ? center : (max + min) / 2.0f;
}

/**
 * @brief calculate dimensions
 *
 * @return
 */
glm::vec3 BoundingRegion::calculateDimensions() {
    return (type == BoundTypes::AABB) ? (min + max) : glm::vec3(2.0f * radius);
}

/**
 * @brief determines if point is inside
 *
 * @param pt
 * @return
 */
bool BoundingRegion::containsPoint(glm::vec3 pt) {
    if (type == BoundTypes::AABB) {
        return (max.x > pt.x) && (min.x < pt.x) &&
               (max.y > pt.y) && (min.y < pt.y) &&
               (max.z > pt.z) && (min.z < pt.z);
    }

    // sphere - distance must be less than radius
    // x^2 + y^2 + z^2 >= r^2
    float distSquared = 0.0f;
    for (int i = 0; i < 3; ++i) {
        distSquared += (center[i] - pt[i]) * (center[i] - pt[i]);
    }

    return distSquared <= (radius * radius);

}

/**
 * @brief determines if region is completely inside of region
 *
 * @param br
 * @return
 */
bool BoundingRegion::containsRegion(BoundingRegion br) {
    if (br.type == BoundTypes::AABB) {
        // if br is a box, just has to contain min and max
        return containsPoint(br.min) && containsPoint(br.max);
    }

    if (br.type == BoundTypes::SPHERE && type == BoundTypes::SPHERE) {
        // if both spheres, combination of distance from centers and br.radius is < radius
        return glm::length(center - br.center) + br.radius < radius;
    }

    // if this is a box and br is a sphere,
    if (br.type == BoundTypes::SPHERE && type == BoundTypes::AABB) {
        if (!containsPoint(br.center)) {
            return false;
        }

        // center inside the box
        /*
         * for each axis (x, y, z)
         * - if the distance from the center of the sphere to either side  of the box,
         *  in (x, y, or z) independently, is smaller than the radius, then that means there
         *  is some section of the sphere  that is outside of the box
         *  - return false
         */
        for (int i = 0; i < 3; ++i) {
            if (abs(max[i] - br.center[i]) < br.radius ||
                abs(br.center[i] - min[i]) < br.radius) {
                return false;
            }
        }
    }

    return true;
}

/**
 * @brief determines if region intersects (partial containment)
 *
 * @param br
 * @return
 */
bool BoundingRegion::intersectsWith(BoundingRegion br) {
    // overlap on all axes

    if (type == BoundTypes::AABB && br.type == BoundTypes::AABB) {
        // both boxes - they must overlap on all three axis
        glm::vec3 rad = calculateDimensions() / 2.0f;   // "radius" of "this" box
        glm::vec3 radBr = br.center / 2.0f;             // "radius" of "br" box

        glm::vec3 center = calculateCenter();           // center of "this" box
        glm::vec3 centerBr = br.calculateCenter();      // center of "br" box

        glm::vec3 dist = abs(center - centerBr);

        for (int i = 0; i < 3; ++i) {
            if (dist[i] > rad[i] + radBr[i]) {
                // no overlap on this axis
                return false;
            }
        }
    }

    if (type == BoundTypes::SPHERE && br.type == BoundTypes::SPHERE) {
        // distance between centers must be less than combined radius
        return glm::length(center - br.center) < (radius + br.radius);
    }

    // box and sphere
    if (type == BoundTypes::SPHERE) {
        // determine if sphere is above top, below bottom, etc.
        // find distance (squared) to the closest plane

        float distSquared = 0.0f;
        for (int i = 0; i < 3; ++i) {
            if (center[i] < br.min[i]) {
                // beyond min
                distSquared += (br.min[i] - center[i]) * (br.min[i] * center[i]);
            } else if (center[i] > br.max[i]) {
                // beyond max
                distSquared += (center[i] - br.max[i]) * (center[i] - br.max[i]);
            }
            // else inside
        }
        return distSquared <= (radius * radius);
    }

    // (type == BoundTypes::AABB && br.type == SPHERE)
    // this is a box, br is a sphere
    // call algorithm for br (defined in preceding else if block)
    return br.intersectsWith(*this);
}

BoundingRegion::BoundingRegion() {}
