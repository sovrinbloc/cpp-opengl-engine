//
// Created by Joseph Alai on 3/12/22.
//

#ifndef ENGINE_UICONSTRAINT_H
#define ENGINE_UICONSTRAINT_H

enum Axis {
    XAxis,
    YAxis
};

enum ConstraintType {
    Absolute,
    Relative
};

enum PositionType {
    Percent,
    Pixel
};


class UiConstraint {
protected:
    float value;
    Axis axis;
public:
    virtual ConstraintType getConstraintType() const = 0;

    virtual PositionType getPositionType() const = 0;

    virtual float getPercentValue() = 0;

    virtual float getDecimalValue() = 0;

    virtual int getPixelValue() = 0;

    Axis getAxis() const;
};


#endif //ENGINE_UICONSTRAINT_H
