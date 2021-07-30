//
// Created by Joseph Alai on 7/30/21.
//

#ifndef ENGINE_INTERACTIVEMODEL_H
#define ENGINE_INTERACTIVEMODEL_H


#include "../Interfaces/Interactive.h"
#include <map>

class InteractiveModel {
    static std::map<int, Interactive *> interactiveBox;
public:
    static Interactive* getInteractiveBox(int index);

    static void setInteractiveBox(int index, Interactive *interactive);

    static void setInteractiveBox(Interactive *interactive);

    static int getIndexByInteractive(Interactive *interactive);
};


#endif //ENGINE_INTERACTIVEMODEL_H
