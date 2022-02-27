//
// Created by Joseph Alai on 2/26/22.
//

#ifndef ENGINE_CONTAINER_H
#define ENGINE_CONTAINER_H

#include <vector>
#include "UiConstraints.h"

class Container {
protected:
    std::vector<Container *> children;
    std::vector<Container *> childrenToAdd;
    std::vector<Container *> childrenToRemove;
    UiConstraints constraints;

protected:
    Container *parent = nullptr;
    bool sterile = false;
public:
    explicit Container(bool sterile) : sterile(sterile) {}

    Container *getParent() { return parent; }

    void setParent(Container *parent) { this->parent = parent; }

    void addChild(Container *child, UiConstraints constraints) {
        child->constraints = constraints;
        childrenToAdd.push_back(child);
    }

    const UiConstraints &getConstraints() const {
        return constraints;
    }

    void removeChild(Container *child) { childrenToRemove.push_back(child); }

    void remove() { this->parent->removeChild(this); }

    void initialize() {
        // add children
        // remove children
    };

    std::vector<Container *> getChildren() { return children; }

    bool isSterile() {
        return sterile;
    }

    void setSterile(bool sterile = true) {
        this->sterile = sterile;
    }

    void deleteMe() {
        for (Container *component : children) {
            component->removeOldComponents();
        }
        for (Container *component : childrenToAdd) {
            component->removeOldComponents();
        }
        for (Container *component : childrenToRemove) {
            component->removeOldComponents();
        }
    }

    void removeOldComponents() {
        int index = 0;
        while (index < childrenToRemove.size()) {
            Container *component = childrenToRemove.at(index++);
            children.erase(children.begin() + index);
            component->deleteMe();
        }
        childrenToRemove.clear();
    }
};

#endif //ENGINE_CONTAINER_H
