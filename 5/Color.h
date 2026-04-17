#pragma once

class Color {
public:
    float R = 1, G = 1, B = 1;
    Color() {}
    Color(float r, float g, float b) : R(r), G(g), B(b) {}

    Color operator+(const Color& other) const {
        return Color(R + other.R, G + other.G, B + other.B);
    }

    static Color Lerp(Color& a, Color& b, float t);
};