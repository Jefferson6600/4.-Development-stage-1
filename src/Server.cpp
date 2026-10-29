#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

Server::Server(const std::string& dbFile, const std::string& logFile, int port)
    : logger_(logFile), port_(port) {
    if (!auth_.loadUsers(dbFile)) {
        logger_.log("Failed to load user database: " + dbFile, true);
    }
}

bool Server::authenticateClient(int sock, std::string& login) {
    char buf[1024] = {0};
    ssize_t n = recv(sock, buf, sizeof(buf) - 1, 0);
    if (n <= 0) {
        return false;
    }
    std::string line(buf);
    std::istringstream iss(line);
    std::string salt, hash;
    if (!(iss >> login >> salt >> hash)) {
        return false;
    }
    return auth_.checkLogin(login, salt, hash);
}

void Server::handleClient(int sock) {
    std::string login;
    if (!authenticateClient(sock, login)) {
        send(sock, "ERR", 3, 0);
        logger_.log("Authentication failed");
        return;
    }
    send(sock, "OK", 2, 0);
    logger_.log("User authenticated: " + login);

    uint32_t nVectors = 0;
    if (recv(sock, &nVectors, sizeof(nVectors), MSG_WAITALL) != sizeof(nVectors)) {
        logger_.log("Failed to read vector count");
        return;
    }

    std::vector<float> results;
    results.reserve(nVectors);

    for (uint32_t i = 0; i < nVectors; ++i) {
        uint32_t size = 0;
        if (recv(sock, &size, sizeof(size), MSG_WAITALL) != sizeof(size)) {
            logger_.log("Failed to read vector size");
            return;
        }
        std::vector<float> values(size);
        if (size > 0) {
            ssize_t need = static_cast<ssize_t>(size * sizeof(float));
            if (recv(sock, values.data(), need, MSG_WAITALL) != need) {
                logger_.log("Failed to read vector values");
                return;
            }
        }
        results.push_back(calc_.sumOfSquares(values));
    }

    uint32_t count = static_cast<uint32_t>(results.size());
    send(sock, &count, sizeof(count), 0);
    if (count > 0) {
        send(sock, results.data(), count * sizeof(float), 0);
    }
}

void Server::start() {
    int serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd < 0) {
        logger_.log("socket() failed", true);
        return;
    }

    int opt = 1;
    setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(static_cast<uint16_t>(port_));

    if (bind(serverFd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
        logger_.log("bind() failed", true);
        close(serverFd);
        return;
    }

    if (listen(serverFd, 5) < 0) {
        logger_.log("listen() failed", true);
        close(serverFd);
        return;
    }

    logger_.log("Server started on port " + std::to_string(port_));

    while (true) {
        int clientSock = accept(serverFd, nullptr, nullptr);
        if (clientSock < 0) {
            continue;
        }
        handleClient(clientSock);
        close(clientSock);
    }
}
