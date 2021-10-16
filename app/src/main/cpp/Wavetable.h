//
// Created by JohnK on 10/12/2021.
//

#ifndef PATCH_MATCHER_WAVETABLE_H
#define PATCH_MATCHER_WAVETABLE_H
#include <functional>
#include <fstream>

class Wavetable {
protected:
    static float constexpr kPI = M_PI;
    static float constexpr kTwoPi = kPI * 2;
    static int constexpr size = 128;
    float table[size];
public:
    Wavetable();
    virtual ~Wavetable() = default;

    int get_size() const ;
    float operator[](int index) const;
    void print() const;

    virtual void generate() = 0;
    virtual bool setPatch(std::function<float(double)> new_patch);

};


#endif //PATCH_MATCHER_WAVETABLE_H
