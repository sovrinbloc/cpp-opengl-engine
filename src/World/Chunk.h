//
// Created by Joseph Alai on 7/31/21.
//

#ifndef ENGINE_CHUNK_H
#define ENGINE_CHUNK_H


#include <cmath>
#include "Map.h"
#include <iostream>

class Chunk {
public:
    Map map;
    int p;
    int q;

    int faces;
    unsigned int position_buffer; // whatis: i am not sure what the position buffer is
    unsigned int normal_buffer_data; // whatis: i don't know what this is
    unsigned int uv_coords_buffer_data; // storing texture coordinates

    /**
     *  @var uv_coords_buffer_data
     *  When texturing a mesh, you need a way to tell to OpenGL which part of the image has to be used for each triangle. This is done with UV coordinates.
     *  Each vertex can have, on top of its position, a couple of floats, U and V. These coordinates are used to access the texture, in the following way :
     *  http://www.opengl-tutorial.org/assets/images/tuto-5-textured-cube/UVintro.png
     *
     *  @var int p : the position p of the person divided by max chunks :
     *   floorf(roundf(char_x) / CHUNK_SIZE)
     *  @var int q : the position p of the person divided by max chunks :
     *   floorf(roundf(char_z) / CHUNK_SIZE)
     *  @var position_buffer
     *  @var normal_buffer_data
     *  whatis: A chunk is a 256-block tall, 16×16 segment of a world (256x16x16).
     *   Chunks are the method used by the world generator to divide maps into manageable pieces.
     */
    Chunk(int p, int q);

    /**
     *  chunk_distance
     *  gets the max distance between the player's location relative to max chunks,
     *  and the input chunk
     *
     *  @var ChunkStruct *chunk
     *  @var int p Player P
     *  @var int q Player Q
     */
    int distanceFrom(int p, int q);

    /**
     * @brief Update makes sure the actual VAO's, etc, are loaded.
     */
    void update();


};


#endif //ENGINE_CHUNK_H
