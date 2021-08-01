//
// Created by Joseph Alai on 7/31/21.
//

#include <cmath>
#include "Map.h"
#include "HashMap.h"
#include "WorldCommon.h"

Map::Map() {
    mask = 0xfff;
    entries = std::map<long, Block *>();
}

Map::Map(std::string mapName) {
    mask = 0xfff;
    entries = std::map<long, Block *>();
    makeWorld(std::move(mapName));
}

void Map::makeWorld(std::string worldFile) {
    // set(x, y, z, object);
}

int Map::get(int x, int y, int z) {
    unsigned int index = HashMap::hash(x, y, z) & mask;
    auto it = entries.find(index);
    if (it != entries.end()) {
        if (it->second->x == x && it->second->y == y && it->second->z == z) {
            return it->second->w;
        }
    }

    for (it = entries.begin(); it != entries.end() && !EMPTY_BLOCK(it->second); index = (index + 1) & mask) {
        if (it->second->x == x && it->second->y == y && it->second->z == z) {
            return it->second->w;
        }
        it = entries.find(index);
    }

    return 0;
}

void Map::set(int x, int y, int z, int texture) {
    unsigned int index = HashMap::hash(x, y, z) & mask;
    Block *entry = entries[index];
    int overwrite = 0;

    //  see if the hash exists in the map. if it does,
    //  continue on until we find an entry that is empty
    std::map<long, Block *>::iterator it;
    for (it = entries.begin(); it != entries.end() && !EMPTY_BLOCK(it->second); index = (index + 1) & mask) {
        if (it->second->x == x && it->second->y == y && it->second->z == z) {
            overwrite = 1;
            break;
        }
        it = entries.find(index);
    }
    if (it == entries.end()) {
        entries[index] = entry;
    }

    if (overwrite) {
        entry->w = texture;
    } else if (texture) {
        // add the block to the map, and increment the map size by 1
        entry->x = x;
        entry->y = y;
        entry->z = z;
        entry->w = texture;
    }
}

int
Map::hitTest(float maxDistance, int previous, float charX, float charY, float charZ, float camFrontX, float camFrontY,
             float camFrontZ, int *hitX, int *hitY, int *hitZ) {
    int maxDist = 8;
    int previousX = 0;
    int previousY = 0;
    int previousZ = 0;
    for (int i = 0; i < static_cast<int>(maxDistance * static_cast<float>(maxDist)); i++) {
        int nearestX = static_cast<int>(std::roundf(charX));
        int nearestY = static_cast<int>(std::roundf(charY));
        int nearestZ = static_cast<int>(std::roundf(charZ));
        if (nearestX != previousX || nearestY != previousY || nearestZ != previousZ) {
            int block_texture = get(nearestX, nearestY, nearestZ);
            if (block_texture > 0) {
                if (previous) {
                    *hitX = previousX;
                    *hitY = previousY;
                    *hitZ = previousZ;
                } else {
                    *hitX = nearestX;
                    *hitY = nearestY;
                    *hitZ = nearestZ;
                }
                return block_texture;
            }
            previousX = nearestX;
            previousY = nearestY;
            previousZ = nearestZ;
        }
        charX += camFrontX / static_cast<float>(maxDist);
        charY += camFrontY / static_cast<float>(maxDist);
        charZ += camFrontZ / static_cast<float>(maxDist);
    }
    return 0;
}
