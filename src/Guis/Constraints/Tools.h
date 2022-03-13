//
// Created by Joseph Alai on 3/12/22.
//

#ifndef ENGINE_TOOLS_H
#define ENGINE_TOOLS_H

#include "../../RenderEngine/DisplayManager.h"

class Tools {
public:
    /**
     * @brief Converts the input decimal percentage [0...1] into pixels.
     *
     * @param decimalValue
     * @return
     */
    static int getPixelValueFromDecimalPercentage(Axis axis, float decimalValue) {
        // multiplies the percentage decimalValue by the width (pixel)
        if (axis == XAxis) {
            return DisplayManager::Width() * decimalValue;
        }
        return DisplayManager::Height() * decimalValue;
    }

    /**
     * @brief Gets the ratio decimal of the pixel to screen.
     *
     * @return
     */
    static float getRatioDecimalValueFromPixel(Axis axis, float pixelValue) {
        if (axis == XAxis) {
            return ((float) pixelValue * 1.0f) / ((float) DisplayManager::Width() * 1.0f);
        }
        return ((float) pixelValue * 1.0f) / ((float) DisplayManager::Height() * 1.0f);
    }
};

#endif //ENGINE_TOOLS_H
