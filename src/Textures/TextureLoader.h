//
// Created by Joseph Alai on 6/24/21.
//

#ifndef CRAFT_UTIL_H
#define CRAFT_UTIL_H

#include <string>
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

typedef enum {
    JPG = 1,
    PNG = 2,
} ImageType;

class TextureLoader {
public:
    GLuint id;
    int bound;
    TextureLoader(std::string filename, ImageType type) ;

    GLuint getId() {
        return this->id;
    }

    /**
     * @brief binds the texture to true
     */
    void bindTexture();

private:
    /**
     * @brief create a 2d texture by loading the jpeg file
     *
     * @param texture
     * @param file_name
     */
    void loadJpgTexture(const char *file_name);

    /**
     * @brief load a texture as a png and apply it to openGL
     *
     * @param file_name
     */
    void loadPngTexture(const char *file_name) ;

};

#endif //CRAFT_UTIL_H