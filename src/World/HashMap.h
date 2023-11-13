//
// Created by Joseph Alai on 7/31/21.
//

#ifndef ENGINE_HASHMAP_H
#define ENGINE_HASHMAP_H

class HashMap {
public:

    /**
     * @brief for generating memory spaces (hash map)
     *
     * @param key
     * @return
     */
    static int hashInt(int key) {
        key = ~key + (key << 15);
        key = key ^ (key >> 12);
        key = key + (key << 2);
        key = key ^ (key >> 4);
        key = key * 2057;
        key = key ^ (key >> 16);
        return key;
    }

    /**
     * @brief hash inputs (x, y, z) and returns a hashed version of that system
     *
     * @param x
     * @param y
     * @param z
     * @return
     */
    static int hash(int x, int y, int z)  {
        x = hashInt(x);
        y = hashInt(y);
        z = hashInt(z);
        return x ^ y ^ z;
    }

};

#endif //ENGINE_HASHMAP_H
