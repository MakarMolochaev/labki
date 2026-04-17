#pragma once

class Color {
public:
    float R = 1, G = 1, B = 1;
    Color() {}
    Color(float r, float g, float b) : R(r), G(g), B(b) {}

    static Color Lerp(Color& a, Color& b, float t);
};

Color Color::Lerp(Color& a, Color& b, float t) {
    return Color(
        a.R + (b.R - a.R) * t,
        a.G + (b.G - a.G) * t,
        a.B + (b.B - a.B) * t
    );
}