//
// Created by Joseph Alai on 7/31/21.
//

#include <cmath>
#include "Map.h"
#include "HashMap.h"
#include "WorldCommon.h"
#include "../Toolbox/Noise.h"


// using dynamic memory allocation
Map::Map() {
    mapAlloc();
}

Map::Map(std::string mapName) {
    mapAlloc();
    makeWorld(std::move(mapName));
}

void Map::makeWorld(std::string worldFile) {
    // set(x, y, z, object);
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

// duplicate: but with hashmap with calloc, instead of actual std::map
void Map::set(int x, int y, int z, int texture) {
    unsigned int index = HashMap::hash(x, y, z) & mask; // hint: what the fuck is this?
    Block *entry = data + index; // map->data = (Block *)calloc(map->mask + 1, sizeof(Block));
    int overwrite = 0;

    // whatis: see if the hash exists in the map. if it does,
    //  continue on until we find an entry that is empty
    while (!EMPTY_BLOCK(entry)) {
        if (entry->x == x && entry->y == y && entry->z == z) {
            overwrite = 1;
            break;
        }
        index = (index + 1) & mask;
        entry = data + index;
    }
    if (overwrite) {
        entry->w = texture;
    }
        // whatis: add the block to the map, and increment the map size by 1
    else if (texture) {
        entry->x = x;
        entry->y = y;
        entry->z = z;
        entry->w = texture;
        size++;
        if (size * 2 > mask) {
            grow();
        }
    }
}

// map_get (using calloc, etc)
//
// hashes the coordinates, and hits the hash map (map->data)
// to see if we can get the block. if we can find it, then return it's texture
// if we can't find it, then keep going until we find it.
//
// @var Map *map : the chunk's map, containing blocks
// @var int x : x position of block
// @var int y : y position of block
// @var int z : z position of block
// @return texture (block type) [w]
int Map::get(int x, int y, int z) {
    unsigned int index = HashMap::hash(x, y, z) & mask;
    Block *entry = data + index;
    while (!EMPTY_BLOCK(entry)) {
        if (entry->x == x && entry->y == y && entry->z == z) {
            return entry->w;
        }
        index = (index + 1) & mask;
        entry = data + index;
    }
    return 0;
}

void Map::grow() {
    Map new_map;
    new_map.mask = (mask << 1) | 1; // double the map size and add 1
    new_map.size = 0;
    new_map.data = (Block *)calloc(new_map.mask + 1, sizeof(Block));
    for (unsigned int index = 0; index <= mask; index++) {
        Block *block = data + index;
        if (!EMPTY_BLOCK(block)) {
            new_map.set(block->x, block->y, block->z, block->w);
        }
    }
    free(data);
    mask = new_map.mask; // new size of the array
    size = new_map.size; // new amount of blocks
    data = new_map.data; // the hash_map for the blocks
}

void Map::mapAlloc() {
    mask = 0xfff;
    size = 0;
    data = (Block *)calloc(mask + 1, sizeof(Block)); // hashmap initialized
}

void Map::mapFree() {
    free(data);
}



// make_world
// todo: figure out if these are generating cubes, or the faces to the cube
//   as it relates to: update_chunk
//
// @var Map *map : an empty map
// @var int x_chunk_pos : the x position of the chunk
// @var int y_chunk_pos : the y position of the chunk
//
// makes a volume of blocks based on the perlin formula.
// we traverse the position of the chunk, starting at -1, going to CHUNK_SIZE (32)
// and create an area of 34 x 34. but during the rendering of the area (x * z),
// we also generate a perlin value to see which height of blocks we are going to allow.
// the perlin formula is generated twice.
//
int debugs = 0;
void Map::makeWorld(int x_chunk_pos, int z_chunk_pos) {
    enum EntityType block_texture;

    int pad = 1; // todo: figure out what this is. Although I think it means the distance between blocks
    for (int dx = -pad; dx < CHUNK_SIZE + pad; dx++) { // from -1 to +33?
        for (int dz = -pad; dz < CHUNK_SIZE + pad; dz++) {
            // we multiply by the Chunk_Size to separate the chunk into 32 x 32 x Y blocks
            int x = x_chunk_pos * CHUNK_SIZE + dx; // actual x position of the block
            int z = z_chunk_pos * CHUNK_SIZE + dz; // actual z position of the block

            // whatis: perlin noise (generating realistic structures, and textures)
            //  in this sense it is used to generate the maps.
            //  https://medium.com/@yvanscher/playing-with-perlin-noise-generating-realistic-archipelagos-b59f004d8401 https://www.engadget.com/2015-03-04-how-minecraft-worlds-are-made.html
            float f = Noise::simplex2(x * 0.01, z * 0.01, 4, 0.5, 2); // increases depth (sheer)
            float g = Noise::simplex2(-x * 0.01, -z * 0.01, 2, 0.9, 2); // smoother
            int max_map_height = g * 32 + 16; // max height
            int block_y = f * max_map_height; // the location of the block being built

            block_texture = Grass; // block_texture (cube type)
            int ground_level_height = 12; // ground_level_height = the ground level (12 blocks exist below)
            if (block_y <= ground_level_height) {
                block_y = ground_level_height;
                block_texture = Ground; // ground level and below (dirt)
            }
            // only allow from 0 - 32 to be generated by a block
            // whatis: why would we have the padding, then?
            if (dx < 0 || dz < 0 || dx >= CHUNK_SIZE || dz >= CHUNK_SIZE) {
                block_texture = (EntityType)-1; // empty sky that is untouchable and you can't go through it
                // basically an indestructible block that sits below the standard ground so you can't go through them.
            }
            for (int y = 0; y < block_y; y++) {
                // whatis: set all blocks *below* ground level with whatever texture
                // fills in the map with the textured blocks, leaving them to be accessible and usable
                set(x, y, z, block_texture);
            }
            if (block_texture == Grass) {
                if (Noise::simplex2(-x * 0.1, z * 0.1, 4, 0.8, 2) > 0.6) {
                    set(x, block_y, z, Fern);
                }
                if (Noise::simplex2(x * 0.05, -z * 0.05, 4, 0.8, 2) > 0.7) {
                    int w = PlantYellow + Noise::simplex2(x * 0.1, z * 0.1, 4, 0.8, 2) * 7;
                    set(x, block_y, z, w);
                }
            }
            // render clouds between 64 and 72 height
            for (int y = 62; y < 72; y++) {
                if (Noise::simplex3(x * 0.01, y * 0.1, z * 0.01, 8, 0.5, 2) > 0.75) {
                    set(x, y, z, Clouds); // clouds
                }
            }
        }
    }
}

Map::~Map() {
    mapFree();
}



/*Map::Map() {
    mask = 0xfff;
    entries = std::map<long, Block *>();
}*/

/*Map::Map(std::string mapName) {
    mask = 0xfff;
    entries = std::map<long, Block *>();
    makeWorld(std::move(mapName));
}*/


/*
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
*/

/*
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
*/