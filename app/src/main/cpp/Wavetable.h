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
    static float constexpr kPI = M_PI;
    static float constexpr kTwoPi = kPI * 2;
    static int constexpr size = 1024;
    static int constexpr s_iMaxPartials = size / 2;
    float table[size];

    void normalize();

public:

    enum Wavetable_t {
        kSine,
        kSquare,
        kTriangle,
        kSaw,
        kCustom,

        kNumTypes
    };

    Wavetable();
    virtual ~Wavetable() = default;

    int get_size() const ;
    float operator[](int index) const;
    float at(int index) const;

    virtual void generate() = 0;
    virtual bool setPatch(std::function<float(float)> new_patch);

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

class TriangleWavetable : public Wavetable
{
public:
    TriangleWavetable();
    ~TriangleWavetable() = default;

    virtual void generate() override;
};

class SawtoothWavetable : public Wavetable
{
public:
    SawtoothWavetable();
    ~SawtoothWavetable() = default;

    virtual void generate() override;
};

class CustomWavetable : public Wavetable
{
private:
    std::function<float(float)> patch;
public:
    CustomWavetable(std::function<float(float)> patch = [](float){return -1;});
    virtual ~CustomWavetable();

    virtual bool setPatch(std::function<float(float)> new_patch) override;
    virtual void generate() override;
};


#endif //PATCH_MATCHER_WAVETABLE_H
