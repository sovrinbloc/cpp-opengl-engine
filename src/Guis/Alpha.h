//
// Created by Joseph Alai on 2/25/22.
//

#ifndef ENGINE_ALPHA_H
#define ENGINE_ALPHA_H

class Alpha {
private:
    double alpha;
public:
    Alpha(double alpha);

    double getAlpha() const;

    void setAlpha(double alpha);

    void apply();
};


#endif //ENGINE_ALPHA_H
