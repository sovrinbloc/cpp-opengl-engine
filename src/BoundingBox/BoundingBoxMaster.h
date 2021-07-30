//
// Created by Joseph Alai on 7/26/21.
//

#ifndef ENGINE_BOUNDINGBOXMASTER_H
#define ENGINE_BOUNDINGBOXMASTER_H
#include "glm/glm.hpp"
#include "../Input/InputMaster.h"
#include "../RenderEngine/DisplayManager.h"
#include <map>
class BoundingBoxMaster {
private:
    static glm::ivec3 colors;
    static int totalColors;
public:
    static glm::vec3 getColor();

    static int getIndexByColor(int r, int g, int b);

    int getIndexByColor(glm::vec3 color);

    glm::vec4 getColorByIndex(int index);

    int getPickedColorIndexUnderMouse() {
//        mp = getMouseX;
//
//        // Convert cursor position
//        ScreenToClient(appMain.hWnd, &mp);
//        RECT rect; GetClientRect(appMain.hWnd, &rect);
//        mp.y = rect.bottom-mp.y;
//
//        // Read only RGB value
//        BYTE bArray[4];
//        glReadPixels(mp.x, mp.y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, bArray);
//        int iResult = getIndexByColor(bArray[0], bArray[1], bArray[2]);
//        if(iResult == RGB_WHITE)return -1; // Nothing was selected
//        return iResult;
    }
};

#endif //ENGINE_BOUNDINGBOXMASTER_H
