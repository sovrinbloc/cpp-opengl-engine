//
// Created by Joseph Alai on 7/31/21.
//

#ifndef ENGINE_WORLDCOMMON_H
#define ENGINE_WORLDCOMMON_H

#define EMPTY_BLOCK(e) (!(e)->x && !(e)->y && !(e)->z && !(e)->w)
#define MAP_FOR_EACH(map, block) \
    for (unsigned int i = 0; i <= (map)->mask; i++) { \
        Block *(block) = (map)->data + i; \
        if (EMPTY_BLOCK(block)) { \
            continue; \
        }
#define END_MAP_FOR_EACH }
#define MAX_CHUNKS 1024
#define CHUNK_SIZE 32 // the distance allowed to load blocks (except q?)
#define CREATE_CHUNK_RADIUS 6
#define RENDER_CHUNK_RADIUS 6
#define DELETE_CHUNK_RADIUS 8

#endif //ENGINE_WORLDCOMMON_H
