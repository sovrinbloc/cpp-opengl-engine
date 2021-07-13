//
// Created by Joseph Alai on 7/12/21.
//

#include "HeightMap.h"

Heightmap::Heightmap(const std::string &fileName) {
    this->fileName = fileName;
    calculateMapFromImage();
    if (heightData.size() == 0) {
        return;
    }
}

void Heightmap::calculateMapFromImage() {
    stbi_set_flip_vertically_on_load(1);
    int bytesPerPixel;
    const auto imageData = stbi_load(fileName.c_str(), &width, &height, &bytesPerPixel, 0);
    if (imageData == nullptr) {

        // Return empty vector in case of failure
        std::cout << "Failed to load heightmap image " << fileName << "!" << std::endl;
        return;
    }

    std::vector<std::vector<float>> result(height, std::vector<float>(width));
    auto pixelPtr = &imageData[0];
    for (auto i = 0; i < height; i++) {
        for (auto j = 0; j < width; j++) {
            result[i][j] = float(*pixelPtr) / 255.0f;
            pixelPtr += bytesPerPixel;
        }
    }

    heightData = result;
    stbi_image_free(imageData);
}

int Heightmap::getWidth() const {
    return width;
}

int Heightmap::getHeight() const {
    return height;
}

const std::vector<std::vector<float>> Heightmap::getHeightData() {
    return heightData;
}


