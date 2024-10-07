#include "Admin.h"


Admin::Admin(const std::string& username, const std::string& password, int sellerId)
    : Seller(username, password, sellerId) {}

void Admin::approveSeller([[maybe_unused]] const Storage& storage, [[maybe_unused]] int sellerId) const {
    std::cout << "Администратор " << Seller::getUsername() << " одобряет продавца с ID: " << sellerId << std::endl;
}


void Admin::removeProduct(Storage& storage, int seller_id) {
    std::cout << "Администратор " << Seller::getUsername() << " удаляет продукт." << std::endl;
    Seller::removeProduct(storage, seller_id); 
}

void Admin::login() {
    std::cout << "Администратор " << Seller::getUsername() << " вошел в систему." << std::endl;
}

void Admin::logout() {
    std::cout << "Администратор " << Seller::getUsername() << " вышел из системы." << std::endl;
}

void getLoginPassword(std::string& login, std::string& password)
{
    std::cout << "Введите логин:\n";
    std::cin >> login;
    std::cout << "Введите пароль:\n";
    std::cin >> password;
}
