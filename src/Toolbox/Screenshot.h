//
// Created by Joseph Alai on 7/29/21.
//

#ifndef ENGINE_SCREENSHOT_H
#define ENGINE_SCREENSHOT_H
#define GL_SILENCE_DEPRECATION
#include "GLFW/glfw3.h"
class Screenshot {
public:
    /**
     * @brief takes a screenshot of the screen within x, y, area and saves it to the hard drive
     * @example Screenshot::saveToFile("output" + std::to_string(glfwGetTime() / 10) + std::string(".tga"),
                                     DisplayManager::FboWidth(), DisplayManager::FboHeight());
     * @param filename
     * @param windowWidth
     * @param windowHeight
     */
    static void saveToFile(const std::string &filename, int windowWidth, int windowHeight) {
        const int numberOfPixels = windowWidth * windowHeight * 3;
        unsigned char pixels[numberOfPixels];

        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glReadBuffer(GL_FRONT);
        glReadPixels(0, 0, windowWidth, windowHeight, GL_RGB, GL_UNSIGNED_BYTE, pixels);

        FILE *outputFile = fopen(filename.c_str(), "w");
        short header[] = {0, 2, 0, 0, 0, 0, (short) windowWidth, (short) windowHeight, 24};

        fwrite(&header, sizeof(header), 1, outputFile);
        fwrite(pixels, numberOfPixels, 1, outputFile);
        fclose(outputFile);

        printf("Finish writing to file: %s.\n", filename.c_str());
    }

};
#endif //ENGINE_SCREENSHOT_H
