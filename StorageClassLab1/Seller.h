#ifndef SELLER_H  // Проверка, был ли определён SELLER_H
#define SELLER_H  // Определение SELLER_H

#include <iostream>
#include <string>
#include "Storage.h"

class Seller {
public:
    std::string username;
    int sellerId;

    Seller(const std::string& username, const std::string& password, int sellerId);
    virtual ~Seller() = default;

    int getSellerId() const;
    const std::string& getUsername() const;

    virtual void addProduct(Storage& storage, std::unique_ptr<Product> product) const;
    virtual void removeProduct(Storage& storage, int seller_id);

protected:
    std::string password;
};

#endif // SELLER_H
