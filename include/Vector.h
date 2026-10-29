#pragma once
#include <cstdint>
#include <vector>

/**
 * @brief Класс, хранящий один вектор при приёме данных от клиента.
 */
class Vector {
public:
    Vector() = default;

    void setSize(uint32_t s);
    void setValues(const std::vector<float>& v);
    uint32_t getSize() const;
    const std::vector<float>& getValues() const;

private:
    uint32_t size_ = 0;
    std::vector<float> values_;
};
