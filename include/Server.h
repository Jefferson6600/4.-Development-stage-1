#pragma once
#include "Auth.h"
#include "Calculator.h"
#include "Logger.h"
#include <string>

/**
 * @brief Класс, управляющий всей серверной частью.
 */
class Server {
public:
    Server(const std::string& dbFile, const std::string& logFile, int port);
    void start();

private:
    void handleClient(int clientSock);
    bool authenticateClient(int sock, std::string& login);

    Auth auth_;
    Calculator calc_;
    Logger logger_;
    int port_;
};
