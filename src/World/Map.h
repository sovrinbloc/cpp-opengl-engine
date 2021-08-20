//
// Created by Joseph Alai on 7/31/21.
//

#ifndef ENGINE_MAP_H
#define ENGINE_MAP_H

#include <iostream>
#include "Block.h"
#include <map>

enum EntityType {
    Tree1 = 0x00,
    Tree2 = 0x01,
    Fern1 = 0x02,
    Fern2 = 0x03,
    Fern3 = 0x04,
    Fern4 = 0x05,
    Grass = 0x06,
    Stall = 0x07,
    Lamp = 0x08,
    Grass = 0x09,
    Backpack = 0x10,
    Nothing = -1
};
class Map {
public:
    unsigned int mask; // the size of the array
    std::map<long, Block *> entries;

    Block *data; // instead of map for entries
    unsigned int size; // the amount of blocks
public:

    Map();

    explicit Map(std::string mapName);

    /**
     * Loads the actual positioning, and logic of the world.
     *
     * @param xChunkPos
     */
    void makeWorld(std::string worldFile);

    /**
     *
     *  @brief map_get
     *
     *  hashes the coordinates, and hits the hash map (map->data)
     *  to see if we can get the block. if we can find it, then return it's texture
     *  if we can't find it, then keep going until we find it.
     *
     *  @var MapStruct *map : the chunk's map, containing blocks
     *  @var int p : p position of block
     *  @var int y : y position of block
     *  @var int q : q position of block
     *  @return texture (block type) [w]
     *
     */
    int get(int x, int y, int z);

    void set(int x, int y, int z, int texture);

    /**
     *  @brief hitTest
     *
     *  Line of sight search from current position. If a block is
     *         intersected it is returned, along with the block previously in the line
     *         of sight. If no block is found, return None, None.
     *  checks to see if the cursor is close enough to a block, and hitting it.
     *
     *  @var charX (character / camera p coordinates)
     *  @var charY (character / camera y coordinates)
     *  @var charZ (character / camera q coordinates)
     *  @var rx (horizontal rotation axis -> ray toward X)
     *  @var ry (vertical rotation axis -> ray toward Y)
     *  @var bx
     *  @var by
     *  @var bz
     */
    int hitTest(float maxDistance, int previous, float charX, float charY, float charZ, float camFrontX,
                float camFrontY, float camFrontZ, int *hitX, int *hitY, int *hitZ);

    void grow();

    void mapAlloc();

    void mapFree();

    void makeWorld(int x_chunk_pos, int z_chunk_pos);
};

#endif //ENGINE_MAP_H
