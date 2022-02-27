//
// Created by Joseph Alai on 2/25/22.
//

#include "Alpha.h"

Alpha::Alpha(double alpha) : alpha(alpha) {}

double Alpha::getAlpha() const {
    return alpha;
}

void Alpha::setAlpha(double alpha) {
    Alpha::alpha = alpha;
}

void Alpha::apply() {}
