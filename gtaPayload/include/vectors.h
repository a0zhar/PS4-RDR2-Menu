#pragma once
#ifndef _VECTORS_HH
#define _VECTORS_HH

// 2D vector structure representing a point or a direction in 2D space.
struct EpineVec2 {
    float x, y;
    constexpr EpineVec2(): x(0.0f), y(0.0f) {}
    constexpr EpineVec2(float _x, float _y) :
        x(_x), y(_y) {}
};

// 3D vector structure representing a point or a direction in 3D space.
struct EpineVec3 {
    float x, y, z;
    constexpr EpineVec3(): x(0.0f), y(0.0f), z(0.0f) {}
    constexpr EpineVec3(float _x, float _y, float _z) :
        x(_x), y(_y), z(_z) {}
};

// 4D vector structure representing a point or a direction in 4D space, 
// often used for homogeneous coordinates or colors.
struct EpineVec4 {
    float x, y, z, w;
    constexpr EpineVec4(): x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    constexpr EpineVec4(float _x, float _y, float _z, float _w) :
        x(_x), y(_y), z(_z), w(_w) {}
};

// RGBA color structure with integer components.
struct EpineiRGBA {
    int r, g, b, a;
    constexpr EpineiRGBA(): r(0), g(0), b(0), a(255) {}
    constexpr EpineiRGBA(int _r, int _g, int _b, int _a) :
        r(_r), g(_g), b(_b), a(_a) {}
};

// Color structure that can be converted to and from EpineVec4 with various 
// constructors for different color representations.
struct EpineColor {
    EpineVec4 Value;
    inline operator EpineVec4() const { return Value; }
    constexpr EpineColor() {}
    constexpr EpineColor(float r, float g, float b, float a = 1.0f): Value(r, g, b, a) {}
    constexpr EpineColor(const EpineVec4 &col) : Value(col) {}
    constexpr EpineColor(int r, int g, int b, int a = 255) : Value(
        (float)r *(1.0f / 255.0f),
        (float)g *(1.0f / 255.0f),
        (float)b *(1.0f / 255.0f),
        (float)a *(1.0f / 255.0f)
    ) {}
};

#endif
