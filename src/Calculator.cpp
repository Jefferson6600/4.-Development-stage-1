#include "Calculator.h"
#include <cmath>
#include <limits>

float Calculator::sumOfSquares(const std::vector<float>& values) const {
    float sum = 0.0f;
    const float maxVal = std::numeric_limits<float>::max();

    for (float v : values) {
        float sq = v * v;
        if (std::isinf(sq) || sq > maxVal) {
            return std::numeric_limits<float>::infinity();
        }
        if (sum > maxVal - sq) {
            return std::numeric_limits<float>::infinity();
        }
        sum += sq;
    }
    return sum;
}
