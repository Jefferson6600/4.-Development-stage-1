#pragma once
#include <vector>

/**
 * @brief Класс, выполняющий математическую операцию над данными клиента.
 */
class Calculator {
public:
    /**
     * @brief Сумма квадратов значений вектора.
     * @param values Входной вектор.
     * @return Сумма квадратов или +inf при переполнении.
     */
    float sumOfSquares(const std::vector<float>& values) const;
};
