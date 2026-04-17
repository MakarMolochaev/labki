#include <cmath>
#include "Color.h"

Color Color::Lerp(Color& a, Color& b, float t) {
    return Color(
        std::min(1.0f, a.R + (b.R - a.R) * t),
        std::min(1.0f, a.G + (b.G - a.G) * t),
        std::min(1.0f, a.B + (b.B - a.B) * t)
    );
}