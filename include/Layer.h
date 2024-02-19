#ifndef MY_PAINT_LAYER_H
#define MY_PAINT_LAYER_H
#include <vector>
#include "Curve.h"
#include <optional>
class Layer {
    std::vector<Curve> curves;
    std::optional<Curve> activeCurve;
};
#endif //MY_PAINT_LAYER_H
