#include "Admin.h"


Admin::Admin(const std::string& username, const std::string& password, int sellerId)
    : Seller(username, password, sellerId) {}

void Admin::approveSeller([[maybe_unused]] const Storage& storage, [[maybe_unused]] int sellerId) const {
    std::cout << "������������� " << getUsername() << " �������� �������� � ID: " << sellerId << std::endl;
}


void Admin::removeProduct(Storage& storage, int seller_id) {
    std::cout << "������������� " << getUsername() << " ������� �������." << std::endl;
    Seller::removeProduct(storage, seller_id); 
}
