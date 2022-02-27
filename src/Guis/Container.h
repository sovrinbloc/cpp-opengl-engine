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
    Container *parent = nullptr;
    GuiType type;
    std::string name;
    uint groupId;
    uint childId;
protected:

    std::vector<Container *> children;
    std::vector<Container *> childrenToAdd;
    std::vector<Container *> childrenToRemove;
    UiConstraints *constraints = nullptr;
    bool sterile = false;
public:
    /**
     * @brief Initializes a basic container, which is similar to a linked list. Specifies what type of container it is,
     *        and if it is capable of having children.
     * @param type
     * @param sterile
     */
    explicit Container(GuiType type, bool sterile, std::string name = "component") : type(type), sterile(sterile), name(name) {
        childrenToRemove = std::vector<Container *>();
        children = std::vector<Container *>();
        childrenToAdd = std::vector<Container *>();
    }

    virtual ~Container(){}

    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name) {
        Container::name = name;
    }

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
    void addChild(Container *child, UiConstraints *constraints) {
        child->setParent(this);
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
    UiConstraints *getConstraints() {
        return constraints;
    }

    /**
     * @brief Gets the constraints (size & position) of the component to be applied to itself and its' children.
     *
     * // todo: Should a constrained size smaller than the component itself either truncate or shrink the component?
     *
     * @return
     */
    void setConstraints(UiConstraints *constraints) {
        this->constraints = constraints;
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
