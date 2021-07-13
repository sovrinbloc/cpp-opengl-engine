//
// Created by Joseph Alai on 7/12/21.
//

#ifndef ENGINE_HEIGHTMAP_H
#define ENGINE_HEIGHTMAP_H

#include "../Libraries/images/stb_image.h"
#include <iostream>
#include <vector>

class Heightmap {
public:

    explicit Heightmap(const std::string &fileName);

    void calculateMapFromImage();

    int getWidth() const;

    int getHeight() const;

    const std::vector<std::vector<float>> getHeightData();

private:

    std::string fileName;

    std::vector<std::vector<float>> heightData;

private:

    int width;

    int height;

};

#endif //ENGINE_HEIGHTMAP_H
