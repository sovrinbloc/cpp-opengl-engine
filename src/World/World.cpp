//
// Created by Joseph Alai on 7/30/21.
//

#include "World.h"
#include "WorldCommon.h"
#include "glm/glm.hpp"
#include "Chunk.h"

World::World() {
    chunks = std::vector<Chunk *>(MAX_CHUNKS);
}

void World::setBlock(int x, int y, int z, int texture) {
    int p = static_cast<int>(floorf((float) x / CHUNK_SIZE));
    int q = static_cast<int>(floorf((float) z / CHUNK_SIZE));
    Chunk *chunk = findChunk(p, q);
    chunk->map.set(x, y, z, texture);
    chunk->update();
}

void World::ensureChunks(int xCharMap, int zCharMap) {
    for (auto chunk : chunks) {
        if (chunk->distanceFrom(xCharMap, zCharMap) >= DELETE_CHUNK_RADIUS) {
//            glDeleteBuffers(1, &chunk->position_buffer);
//            glDeleteBuffers(1, &chunk->normal_buffer_data);
//            glDeleteBuffers(1, &chunk->uv_coords_buffer_data);

            *chunk = *(chunks[chunks.size() - 1]);
            chunks.resize(chunks.size() - 1);
        }
    }
    for (int width = -CREATE_CHUNK_RADIUS; width <= CREATE_CHUNK_RADIUS; width++) {
        for (int depth = -CREATE_CHUNK_RADIUS; depth <= CREATE_CHUNK_RADIUS; depth++) {
            // x_chunk_pos = (floorf(roundf(char_x) / 32) + width, 0 / 32 + 0: 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1
            int xChunkPos = xCharMap + width;
            // z_chunk_pos = (floorf(roundf(char_z) / 32) + depth, 0 / 32 + 0: 0, 1, 2, 3, 4 ,5, 0, 1, 2, 3, 4 ,5
            int zChunkPos = zCharMap + depth;
            if (!findChunk(xChunkPos, zChunkPos)) {
                chunks.push_back(new Chunk( xChunkPos, zChunkPos ));
            }
        }
    }
}

Chunk *World::findChunk(int xPos, int zPos) {
    for (Chunk *chunk : chunks) {
        if (chunk->p == xPos && chunk->q == zPos) {
            return chunk;
        }
    }
    return nullptr;
}

int World::collide(int height, float *charX, float *charY, float *charZ) {
    int result = 0;
    int p = static_cast<int>(floorf(roundf(*charX) / CHUNK_SIZE));
    int q = static_cast<int>(floorf(roundf(*charZ) / CHUNK_SIZE));
    Chunk *chunk = findChunk(p, q);
    if (!chunk) {
        return result;
    }
    Map *map = &chunk->map;
    int nearX = static_cast<int>(roundf(*charX));
    int nearY = static_cast<int>(roundf(*charY));
    int nearZ = static_cast<int>(roundf(*charZ));
    float marginX = *charX - static_cast<float>(nearX);
    float marginY = *charY - static_cast<float>(nearY);
    float marginZ = *charZ - static_cast<float>(nearZ);
    float padding = 0.25;

    // keeps a .25 margin away from any non-passible object.
    for (int dy = 0; dy < height; dy++) {
        if (marginX < -padding && isObstacle(map->get(nearX - 1, nearY - dy, nearZ))) {
            *charX = static_cast<float>(nearX) - padding;
        }
        if (marginX > padding && isObstacle(map->get(nearX + 1, nearY - dy, nearZ))) {
            *charX = static_cast<float>(nearX) + padding;
        }
        if (marginY < -padding && isObstacle(map->get(nearX, nearY - dy - 1, nearZ))) {
            *charY = static_cast<float>(nearY) - padding;
            result = 1;
        }
        if (marginY > padding && isObstacle(map->get(nearX, nearY - dy + 1, nearZ))) {
            *charY = static_cast<float>(nearY) + padding;
            result = 1;
        }
        if (marginZ < -padding && isObstacle(map->get(nearX, nearY - dy, nearZ - 1))) {
            *charZ = static_cast<float>(nearZ) - padding;
        }
        if (marginZ > padding && isObstacle(map->get(nearX, nearY - dy, nearZ + 1))) {
            *charZ = static_cast<float>(nearZ) + padding;
        }
    }
    return result;
}

int World::hitTest(int previous, float charX, float charY, float charZ, float rx, float ry, int *bestX, int *bestY,
                   int *bestZ) {
    int result = 0;
    float best = 0;
    int p = static_cast<int>(floorf(roundf(charX) / CHUNK_SIZE));
    int q = static_cast<int>(floorf(roundf(charZ) / CHUNK_SIZE));
    float camFrontX, camFrontY, camFrontZ;

    // todo: figure out how this works
    getSightVector(rx, ry, &camFrontX, &camFrontY, &camFrontZ);
    for (auto chunk : chunks) {
        if (chunk->distanceFrom(p, q) > 1) {
            continue;
        }
        int hitX, hitY, hitZ;
        int blockType = chunk->map.hitTest(8, previous,
                                           charX, charY, charZ, camFrontX, camFrontY, camFrontZ, &hitX, &hitY,
                                           &hitZ);
        if (blockType > 0) {
            float distance = sqrtf(
                    powf(static_cast<float>(hitX) - charX, 2) + powf(static_cast<float>(hitY) - charY, 2) +
                    powf(static_cast<float>(hitZ) - charZ, 2));
            if (best == 0 || distance < best) {
                best = distance;
                *bestX = hitX;
                *bestY = hitY;
                *bestZ = hitZ;
                result = blockType;
            }
        }
    }
    return result;
}

void World::getSightVector(float rx, float ry, float *dx, float *dy, float *dz) {
    /**
     * y ranges from -90 to 90, or -pi/2 to pi/2, so m ranges from 0 to 1 and
     * is 1 when looking ahead parallel to the ground and 0 when looking
     * straight up or down.
     */
    float m = cosf(ry); //ry = 2; m = -0.41
    /**
     * dy ranges from -1 to 1 and is -1 when looking straight down and 1 when
     * looking straight up.
     */
    *dx = cosf(rx - glm::radians(90.0f)) * m; // rx = 2; result = cos(2)sin(2) = -0.38
    *dy = sinf(ry);
    *dz = sinf(rx - glm::radians(90.0f)) * m;
}

int World::isObstacle(int w) {
    return w != 0;
}

int World::playerIntersects(int height, float x, float y, float z, int hx, int hy, int hz) {
    int nx = static_cast<int>(roundf(x));
    int ny = static_cast<int>(roundf(y));
    int nz = static_cast<int>(roundf(z));
    for (int i = 0; i < height; i++) {
        if (nx == hx && ny - i == hy && nz == hz) {
            return 1;
        }
    }
    return 0;
}
