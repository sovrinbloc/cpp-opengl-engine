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

std::string FileSystem::TutorialModel(std::string in) {
    return HOME_PATH + "/Resources/Models/Tutorial/Lesson-23/" + in + ".obj";
}

std::string FileSystem::TutorialTexture(std::string in) {
    return HOME_PATH + "/Resources/Models/Tutorial/Lesson-23/" + in + ".png";
}