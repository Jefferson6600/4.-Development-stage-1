#include "Logger.h"
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>

Logger::Logger(const std::string& filename) : filename_(filename) {}

void Logger::log(const std::string& message, bool isCritical) {
    std::ofstream file(filename_, std::ios::app);
    if (!file.is_open()) {
        return;
    }
    std::time_t now = std::time(nullptr);
    std::tm* tm = std::localtime(&now);

    std::ostringstream oss;
    oss << std::put_time(tm, "%Y-%m-%d %H:%M:%S")
        << " [" << (isCritical ? "CRITICAL" : "NON-CRITICAL") << "] "
        << message << "\n";
    file << oss.str();
}
