#pragma once
#include <string>
#include <iostream>

class User {
private:
    std::string username;
    std::string password;

protected:
    const std::string& getUsername() const {
        return username;
    }

public:
    User(const std::string& username, const std::string& password)
        : username(username), password(password) {}

    virtual void login() = 0;
    virtual void logout() = 0;

    virtual ~User() = default;
};
