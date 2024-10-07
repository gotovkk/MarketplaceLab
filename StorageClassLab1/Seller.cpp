#include "Seller.h"

Seller::Seller(const std::string& username, const std::string& password, int sellerId)
    : username(username), password(password), sellerId(sellerId) {}

int Seller::getSellerId() const {
    return sellerId;
}

const std::string& Seller::getUsername() const {
    return username;
}

void Seller::addProduct(Storage& storage, std::unique_ptr<Product> product) const {
    storage.addProduct(std::move(product));
}

void Seller::removeProduct(Storage& storage, int seller_id) {
    std::cout << "Продавец " << username << " удаляет продукт с ID: " << seller_id << std::endl;

    bool removed = storage.removeProduct("Product Name", seller_id);
    if (removed) {
        std::cout << "Продукт успешно удален." << std::endl;
    }
    else {
        std::cout << "Не удалось удалить продукт. Возможно, он не найден." << std::endl;
    }
}