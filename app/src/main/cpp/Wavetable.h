//
// Created by JohnK on 10/12/2021.
//

#ifndef PATCH_MATCHER_WAVETABLE_H
#define PATCH_MATCHER_WAVETABLE_H
#include <functional>


class Wavetable {
private:
    unsigned size;
    float *table;
    std::function<float(double)> patch;

    static float constexpr kPI = M_PI;
    static float constexpr kTwoPi = kPI * 2;
public:

    Wavetable(std::function<float(double)> patch, int size = 128);
    ~Wavetable();

    void generate();
    unsigned get_size() const ;
    float operator[](int index) const;
    void setPatch(std::function<float(double)> new_patch);

};


#endif //PATCH_MATCHER_WAVETABLE_H
