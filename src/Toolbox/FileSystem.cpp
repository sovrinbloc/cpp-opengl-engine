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
    return HOME_PATH + "/src/Resources/Models/Tutorial/Lesson-23/resources/" + in + ".obj";
}

std::string FileSystem::TutorialTexture(std::string in) {
    printf("%s%s%s%s\n", HOME_PATH.c_str() , "/src/Resources/Models/Tutorial/Lesson-23/resources/" , in.c_str() , ".png");
    return HOME_PATH + "/src/Resources/Models/Tutorial/Lesson-23/resources/" + in + ".png";
}