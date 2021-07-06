//
// Created by Joseph Alai on 7/6/21.
//

#include "FileSystem.h"

std::string HOME_PATH = realpath(".", NULL);

std::string FileSystem::Path(std::string in) {
    return HOME_PATH + in;
}
std::string FileSystem::Path(char *in) {
    return HOME_PATH + in;
}