#ifndef SELLER_H  // Проверка, был ли определён SELLER_H
#define SELLER_H  // Определение SELLER_H

#include <iostream>
#include <string>
#include "Storage.h"

class Seller {
public:
    std::string username;
    std::string password;
    int sellerId;



    Seller(const std::string& username, const std::string& password, int sellerId);
    virtual ~Seller() = default;

    int getSellerId() const;
    const std::string& getUsername() const;

    virtual void addProduct(Storage& storage, std::unique_ptr<Product> product) const;
    virtual void removeProduct(Storage& storage, int seller_id);
};

#endif // SELLER_H
