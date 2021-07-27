//
// Created by Joseph Alai on 7/26/21.
//

#ifndef ENGINE_BOUNDINGBOXMASTER_H
#define ENGINE_BOUNDINGBOXMASTER_H
#include "glm/glm.hpp"
#include "../Input/InputMaster.h"
#include "../RenderEngine/DisplayManager.h"

class BoundingBoxMaster {
private:
    glm::vec3 colors;

public:
    glm::vec3 getColor() {
        if (colors.r < 255) {
            colors.r++;
        } else if (colors.g < 255) {
            colors.g++;
        } else if (colors.b < 255) {
            colors.b++;
        }
        return colors;
    }

    int GetIndexByColor(int r, int g, int b)
    {
        return (r)|(g<<8)|(b<<16);
    }

    glm::vec4 GetColorByIndex(int index)
    {
        int r = index&0xFF;
        int g = (index>>8)&0xFF;
        int b = (index>>16)&0xFF;

        return glm::vec4(float(r)/255.0f, float(g)/255.0f, float(b)/255.0f, 1.0f);
    }

    glm::vec3 getClicked() {
        if (InputMaster::hasPendingClick()) {
            if (InputMaster::mouseClicked(LeftClick)) {
                unsigned char pixel[3];
                glReadPixels(static_cast<GLint>(InputMaster::mouseX), static_cast<GLint>(DisplayManager::Height() - InputMaster::mouseY) - 1, 1, 1, GL_RED, GL_UNSIGNED_BYTE, &pixel);
                return glm::vec3(pixel[0], pixel[1], pixel[2]);
            }
        }
        return glm::vec3();
    }

    int GetPickedColorIndexUnderMouse() {
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
//        int iResult = GetIndexByColor(bArray[0], bArray[1], bArray[2]);
//        if(iResult == RGB_WHITE)return -1; // Nothing was selected
//        return iResult;
    }
};


#endif //ENGINE_BOUNDINGBOXMASTER_H
