#pragma once
#include <string>
#include <map>

/**
 * @brief Класс, отвечающий за проверку подлинности клиента.
 */
class Auth {
public:
    bool loadUsers(const std::string& filename);
    bool checkLogin(const std::string& login,
                    const std::string& salt16,
                    const std::string& clientHash) const;

private:
    std::string sha256(const std::string& input) const;
    std::map<std::string, std::string> validUsers_;
};
