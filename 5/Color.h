#pragma once
#include <iostream>

class Color {
public:
    float R = 0, G = 0, B = 0;
    Color() {}
    Color(float r, float g, float b) : R(r), G(g), B(b) {}

    Color operator+(const Color& other) const {
        return Color(R + other.R, G + other.G, B + other.B);
    }

    Color operator*(const Color& other) const {
        return Color(R * other.R, G * other.G, B * other.B);
    }

    Color operator/(const float other) const {
        return Color(R / other, G / other, B / other);
    }

    Color operator*(const float other) const {
        return Color(R * other, G * other, B * other);
    }

    void RebalanceOverflow() {
        float overflow = 0.0f;
        if(R > 1) overflow += R - 1;
        if(G > 1) overflow += R - 1;
        if(B > 1) overflow += R - 1;
    }

    static Color Lerp(Color& a, Color& b, float t);
    static Color MultiLerp(Color& a, Color b, Color t);
};