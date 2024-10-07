#include "Admin.h"


Admin::Admin(const std::string& username, const std::string& password, int sellerId)
    : Seller(username, password, sellerId) {}

void Admin::approveSeller([[maybe_unused]] const Storage& storage, [[maybe_unused]] int sellerId) const {
    std::cout << "������������� " << Seller::getUsername() << " �������� �������� � ID: " << sellerId << std::endl;
}


void Admin::removeProduct(Storage& storage, int seller_id) {
    std::cout << "������������� " << Seller::getUsername() << " ������� �������." << std::endl;
    Seller::removeProduct(storage, seller_id); 
}

void Admin::login() {
    std::cout << "������������� " << Seller::getUsername() << " ����� � �������." << std::endl;
}

void Admin::logout() {
    std::cout << "������������� " << Seller::getUsername() << " ����� �� �������." << std::endl;
}

void getLoginPassword(std::string& login, std::string& password)
{
    std::cout << "������� �����:\n";
    std::cin >> login;
    std::cout << "������� ������:\n";
    std::cin >> password;
}
