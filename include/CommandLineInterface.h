#pragma once
#include <string>

/**
 * @brief Класс, отвечающий за разбор параметров командной строки.
 */
class CommandLineInterface {
public:
    CommandLineInterface();

    /**
     * @return true, если нужно запускать сервер; false, если показана справка.
     */
    bool parseArgs(int argc, char* argv[]);
    void printHelp() const;

    std::string getDbFile() const;
    std::string getLogFile() const;
    int getPort() const;

private:
    std::string dbFile_ = "/etc/vcalc.conf";
    std::string logFile_ = "/var/log/vcalc.log";
    int port_ = 33333;
};
