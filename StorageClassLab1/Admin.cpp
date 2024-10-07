#include "Admin.h"


Admin::Admin(const std::string& username, const std::string& password, int sellerId)
    : Seller(username, password, sellerId) {}

void Admin::approveSeller([[maybe_unused]] const Storage& storage, [[maybe_unused]] int sellerId) const {
    std::cout << "Администратор " << getUsername() << " одобряет продавца с ID: " << sellerId << std::endl;
}


void Admin::removeProduct(Storage& storage, int seller_id) {
    std::cout << "Администратор " << getUsername() << " удаляет продукт." << std::endl;
    Seller::removeProduct(storage, seller_id); 
}
