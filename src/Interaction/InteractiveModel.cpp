//
// Created by Joseph Alai on 7/30/21.
//

#include "../BoundingBox/BoundingBoxIndex.h"
#include <iostream>
#include "InteractiveModel.h"

std::map<int, Interactive *> InteractiveModel::interactiveBox;

Interactive *InteractiveModel::getInteractiveBox(int index) {
    auto it = interactiveBox.find(index);
    if (it == interactiveBox.end()) {
        return nullptr;
    }
    return it->second;
}

void InteractiveModel::setInteractiveBox(int index, Interactive *interactive) {
    auto it = interactiveBox.find(index);
    if (it == interactiveBox.end()) {
        std::cout << "Error: Please add Alpha attribute to color picing. Already found Interactive object at index: "
                  << std::to_string(index) << std::endl;
    }
    InteractiveModel::interactiveBox[index] = interactive;
}

void InteractiveModel::setInteractiveBox(Interactive *interactive) {
    setInteractiveBox(BoundingBoxIndex::getIndexByColor(interactive->getBoundingBox()->getBoxColor()), interactive);
}

int InteractiveModel::getIndexByInteractive(Interactive *interactive) {
    return BoundingBoxIndex::getIndexByColor(interactive->getBoundingBox()->getBoxColor());
}