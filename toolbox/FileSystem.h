//
// Created by Joseph Alai on 7/1/21.
//

#ifndef ENGINE_FILESYSTEM_H
#define ENGINE_FILESYSTEM_H
#define PATH(IN)(HOME_PATH+IN)

#include <cstdlib>
std::string HOME_PATH = realpath(".", NULL);
class FileSystem {
public:
    static std::string Path(std::string in) {
        return HOME_PATH + in;
    }
    static std::string Path(char *in) {
        return HOME_PATH + in;
    }
};
#endif //ENGINE_FILESYSTEM_H
