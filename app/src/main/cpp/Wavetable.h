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
    std::function<float(int)> patch;
public:

    Wavetable(int size = 128);
    ~Wavetable();

    void generate();
    unsigned get_size() const ;
    float operator[](int index) const;
    void setPatch(std::function<float(int)> new_patch);

};


#endif //PATCH_MATCHER_WAVETABLE_H
