#include "Vector.h"

void Vector::setSize(uint32_t s) {
    size_ = s;
    values_.clear();
    values_.reserve(s);
}

void Vector::setValues(const std::vector<float>& v) {
    values_ = v;
}

uint32_t Vector::getSize() const {
    return size_;
}

const std::vector<float>& Vector::getValues() const {
    return values_;
}
