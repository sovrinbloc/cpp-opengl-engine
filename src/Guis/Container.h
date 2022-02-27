//
// Created by Joseph Alai on 2/26/22.
//

#ifndef ENGINE_CONTAINER_H
#define ENGINE_CONTAINER_H

#include <vector>
#include "UiConstraints.h"

class Container {
public:
    enum GuiType {
        TEXT,
        IMAGE,
        COLORED_BOX,
        CONTAINER
    };
protected:
    std::vector<Container *> children;
    std::vector<Container *> childrenToAdd;
    std::vector<Container *> childrenToRemove;
    UiConstraints constraints;
    GuiType type;
protected:
    Container *parent = nullptr;
    bool sterile = false;
public:

    /**
     * @brief Initializes a basic container, which is similar to a linked list. Specifies what type of container it is,
     *        and if it is capable of having children.
     * @param type
     * @param sterile
     */
    explicit Container(GuiType type, bool sterile) : type(type), sterile(sterile) {
        childrenToRemove = std::vector<Container *>();
        children = std::vector<Container *>();
        childrenToAdd = std::vector<Container *>();
    }

    virtual ~Container(){}

    /**
     * @brief Gets the component type: TEXT, IMAGE, COLORED_SQUARE, CONTAINER
     * @return
     */
    GuiType getType() const {
        return type;
    }

    /**
     * @brief Gets the parent of this component.
     * @return
     */
    Container *getParent() { return parent; }

    /**
     * @brief Sets the parent to this component.
     * @param parent
     */
    void setParent(Container *parent) { this->parent = parent; }

    /**
     * @brief Adds a child component to this container.
     *
     * @param child
     * @param constraints
     */
    void addChild(Container *child, UiConstraints constraints) {
        child->constraints = constraints;
        childrenToAdd.push_back(child);
    }

    /**
     * @brief Gets the constraints (size & position) of the component to be applied to itself and its' children.
     *
     * // todo: Should a constrained size smaller than the component itself either truncate or shrink the component?
     *
     * @return
     */
    const UiConstraints &getConstraints() const {
        return constraints;
    }

    /**
     * @brief Queues up this child to be removed from this container.
     *
     * @param child
     */
    void removeChild(Container *child) { childrenToRemove.push_back(child); }

    /**
     * @brief Removes from the parent.
     */
    void remove() { this->parent->removeChild(this); }

    void initialize() {
        // add children
        // remove children
    };

    /**
     * @brief Gets the children that are in queue to be added to the component.
     *
     * @return
     */
    std::vector<Container *> getChildrenToAdd() { return childrenToAdd; }

    bool isSterile() {
        return sterile;
    }

    /**
     * @brief Sets if this component is capable of having children, or sub-components.
     * @param sterile
     */
    void setSterile(bool sterile = true) {
        this->sterile = sterile;
    }

    /**
     * @brief Delete everything within this component.
     */
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

    /**
     * @brief removes my sub-components, and then removes me from my parent.
     */
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
