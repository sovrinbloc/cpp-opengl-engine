//
// Created by Joseph Alai on 7/4/21.
//

#ifndef ENGINE_UTILS_H
#define ENGINE_UTILS_H
float randomFloat() {
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}
#endif //ENGINE_UTILS_H
