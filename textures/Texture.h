//
// Created by Joseph Alai on 6/24/21.
//

#ifndef CRAFT_UTIL_H
#define CRAFT_UTIL_H
#include "png.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../libraries/images/stb_image.h"
typedef enum {
    JPG,
    PNG,
} ImageType;

class Texture {
public:
    GLuint id;
    int bound;
    Texture(std::string filename, ImageType type) {
        this->id = 0;
        this->bound = false;
        switch (type) {
            case JPG:
                this->loadJpgTexture(filename.c_str());
                break;
            case PNG:
                this->loadPngTexture(filename.c_str());
                break;
            default:
                printf("there is a problem, with loading the texture");
                return;
        }
    }

    GLuint getId() {
        return this->id;
    }

    /**
     * @brief binds the texture to true
     */
    void bindTexture() {
//        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->id);
        bound = true;
    }

private:
    /**
     * @brief create a 2d texture by loading the jpeg file
     *
     * @param texture
     * @param file_name
     */
    void loadJpgTexture(const char *file_name) {
        glGenTextures(1, &this->id);
//        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->id);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load and generate the texture
        int width, height, nrChannels;
        unsigned char *data = stbi_load(file_name, &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            printf("Failed to load texture\n");
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(data);
    }

    /**
     * @brief load a texture as a png and apply it to openGL
     *
     * @param file_name
     */
    void loadPngTexture(const char *file_name) {
        int w;
        int h;
        int comp;
        unsigned char* image = stbi_load(file_name, &w, &h, &comp, STBI_rgb_alpha);

        if(image == nullptr) {
            printf("Failed to load texture");
            return;
        }

        glGenTextures(1, &this->id);
//        glActiveTexture(GL_TEXTURE0);

        glBindTexture(GL_TEXTURE_2D, this->id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        if (comp == 3) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        else if (comp == 4) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(image);
    }

};

#endif //CRAFT_UTIL_H