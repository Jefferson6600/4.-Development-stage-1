#include "CommandLineInterface.h"
#include <getopt.h>
#include <iostream>
#include <cstdlib>

CommandLineInterface::CommandLineInterface() = default;

bool CommandLineInterface::parseArgs(int argc, char* argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "hd:l:p:")) != -1) {
        switch (opt) {
            case 'h':
                printHelp();
                return false;
            case 'd':
                dbFile_ = optarg;
                break;
            case 'l':
                logFile_ = optarg;
                break;
            case 'p':
                port_ = std::atoi(optarg);
                break;
            default:
                printHelp();
                return false;
        }
    }
    return true;
}

void CommandLineInterface::printHelp() const {
    std::cout << "Usage: vcalc [options]\n"
              << "  -h           Show this help\n"
              << "  -d <file>    Database file (default: /etc/vcalc.conf)\n"
              << "  -l <file>    Log file (default: /var/log/vcalc.log)\n"
              << "  -p <port>    Port (default: 33333)\n";
}

std::string CommandLineInterface::getDbFile() const { return dbFile_; }
std::string CommandLineInterface::getLogFile() const { return logFile_; }
int CommandLineInterface::getPort() const { return port_; }
