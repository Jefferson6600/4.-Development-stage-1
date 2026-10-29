#pragma once
#include <string>

/**
 * @brief Класс, записывающий ошибки в файл журнала.
 */
class Logger {
public:
    explicit Logger(const std::string& filename);
    void log(const std::string& message, bool isCritical = false);

private:
    std::string filename_;
};
