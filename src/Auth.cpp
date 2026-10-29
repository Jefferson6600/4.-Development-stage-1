#include "Auth.h"
#include <fstream>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>

std::string Auth::sha256(const std::string& input) const {
    CryptoPP::SHA256 hash;
    std::string digest;
    CryptoPP::StringSource ss(
        input, true,
        new CryptoPP::HashFilter(
            hash,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(digest))));
    return digest;
}

bool Auth::loadUsers(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto pos = line.find(':');
        if (pos == std::string::npos) continue;
        validUsers_[line.substr(0, pos)] = line.substr(pos + 1);
    }
    return true;
}

bool Auth::checkLogin(const std::string& login,
                      const std::string& salt16,
                      const std::string& clientHash) const {
    auto it = validUsers_.find(login);
    if (it == validUsers_.end()) {
        return false;
    }
    std::string expected = sha256(salt16 + it->second);
    return expected == clientHash;
}
