//
// Created by Joseph Alai on 7/4/21.
//

#ifndef ENGINE_UTILS_H
#define ENGINE_UTILS_H
float randomFloat() {
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}
int roll(int min, int max)
{
    // x is in [0,1[
    double x = rand()/static_cast<double>(RAND_MAX + 1);

    // [0,1[ * (max - min) + min is in [min,max[
    int that = min + static_cast<int>( x * (max - min) );

    return that;
}
#endif //ENGINE_UTILS_H
