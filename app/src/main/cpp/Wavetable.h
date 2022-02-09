//
// Created by JohnK on 10/12/2021.
//

#ifndef PATCH_MATCHER_WAVETABLE_H
#define PATCH_MATCHER_WAVETABLE_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <functional>
#include <fstream>

class Wavetable {
protected:
    static double constexpr kPI = M_PI;
    static double constexpr kTwoPi = kPI * 2;
    static int constexpr size = 1024;
    double table[size];
public:
    Wavetable();
    virtual ~Wavetable() = default;

    int get_size() const ;
    double operator[](int index) const;
    double at(int index) const;

    virtual void generate() = 0;
    virtual bool setPatch(std::function<double(double)> new_patch);

};

class SineWavetable : public Wavetable {
public:

    SineWavetable();
    virtual ~SineWavetable() = default;

    virtual void generate() override;
};

class SquareWavetable : public Wavetable
{
public:
    SquareWavetable();
    ~SquareWavetable() = default;

    virtual void generate() override;

};

class CustomWavetable : public Wavetable
{
private:
    std::function<double(double)> patch;
public:
    CustomWavetable(std::function<double(double)> patch = [](double){return -1;});
    virtual ~CustomWavetable();

    virtual bool setPatch(std::function<double(double)> new_patch) override;
    virtual void generate() override;
};


#endif //PATCH_MATCHER_WAVETABLE_H
