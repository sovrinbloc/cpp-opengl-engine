//
// Created by Joseph Alai on 7/12/21.
//

#ifndef ENGINE_HEIGHTMAP_H
#define ENGINE_HEIGHTMAP_H

#include "../Libraries/images/stb_image.h"
#include <iostream>
#include <vector>

struct ImageInfo {
    int height;
    int width;
    std::string filename;
};

class Heightmap {
public:

    explicit Heightmap(const std::string &fileName);

    void calculateMapFromImage();

    std::vector<std::vector<float>> getHeightData();

    float getHeight(int x, int z);

    ImageInfo getImageInfo();

private:


    static const float MAX_HEIGHT;
    static const float MIN_HEIGHT;
    static const float MAX_COLOR_VALUE;

    std::string fileName;

    std::vector<std::vector<float>> heightData;

    ImageInfo imageInfo;

};

#endif //ENGINE_HEIGHTMAP_H
