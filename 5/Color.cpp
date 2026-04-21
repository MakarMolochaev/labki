#include <cmath>
#include "Color.h"

Color Color::Lerp(Color& a, Color& b, float t) {
    return Color(
        a.R + (b.R - a.R) * t,
        a.G + (b.G - a.G) * t,
        a.B + (b.B - a.B) * t
    );
}

Color Color::MultiLerp(Color& a, Color b, Color t) {
    return Color(
        a.R + (b.R - a.R) * t.R,
        a.G + (b.G - a.G) * t.G,
        a.B + (b.B - a.B) * t.B
    );
}