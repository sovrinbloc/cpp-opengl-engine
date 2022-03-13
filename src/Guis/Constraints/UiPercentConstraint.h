//
// Created by Joseph Alai on 3/12/22.
//

#ifndef ENGINE_UIPERCENTCONSTRAINT_H
#define ENGINE_UIPERCENTCONSTRAINT_H
#include "UiConstraint.h"
#include "Tools.h"

class UiPercentConstraint : public UiConstraint {
private:
    const ConstraintType constraintType = Relative;
    const PositionType positionType = Percent;
public:
    UiPercentConstraint(Axis axis, float value, ConstraintType constraintType = Relative)
    : constraintType(constraintType) {
            this->axis = axis;
            this->value = value;
    }

    /**
     * @brief Gets the constraint type: either Relative or Absolute
     *
     * @return
     */
    ConstraintType getConstraintType() const override {
        return constraintType;
    }

    /**
     * @brief Gets the position type: either Pixel or Percentage
     *
     * @return
     */
    PositionType getPositionType() const override {
        return positionType;
    }

    /**
     * @brief Returns the percentage value (not decimal).
     *
     * @return
     */
    float getPercentValue() override {
        return value * 100;
    }

    /**
     * @brief Returns the demical percentage value out of 1.
     *
     * @return
     */
    float getDecimalValue() override {
        return value;
    }

    /**
     * @brief Gets the Pixel value (not decimal).
     *
     * @return
     */
    int getPixelValue() override {
        return Tools::getPixelValueFromDecimalPercentage(axis, value);
    }


    float getValue() {
        return value;
    }
};
#endif //ENGINE_UIPERCENTCONSTRAINT_H
