#include "Admin.h"


Admin::Admin(const std::string& username, const std::string& password, int sellerId)
    : Seller(username, password, sellerId) {}

void Admin::approveSeller(Storage& storage, int sellerId) {
    std::cout << "������������� " << getUsername() << " �������� �������� � ID: " << sellerId << std::endl;
}

void Admin::removeProduct(Storage& storage, int seller_id) {
    std::cout << "������������� " << getUsername() << " ������� �������." << std::endl;
    Seller::removeProduct(storage, seller_id); 
}
