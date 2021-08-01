//
// Created by Joseph Alai on 7/31/21.
//

#include "Chunk.h"
#include "../Util/CommonHeader.h"
Chunk::Chunk(int p, int q) {
    this->p = p;
    this->q = q;
    faces = 0;
    map = Map("newworld.mapfile");
    update();
}

int Chunk::distanceFrom(int p, int q) {
    int dp = ABS(this->p - p);
    int dq = ABS(this->q - q);
    return static_cast<int>(fmax(dp, dq));
}

void Chunk::update() {
    // delete everything that was in this chunk
    // load any entities needed, load any objects.
    // add them to the renderer.
}
