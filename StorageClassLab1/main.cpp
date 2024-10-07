#include <iostream>
#include <vector>
#include <variant>
#include "Admin.h"
#include "SellerManager.h"
#include "ErrorManager.h"


int main() {
    system("chcp 1251");
    std::cout << "Нажмите Enter, чтобы начать...";
    std::cin.get();

    sqlite3* db;
    SellerManager sellerManager;
    std::string password;
    std::string login;
    std::unique_ptr<Seller> currentSeller = nullptr;

    int rc;
    int choice;
    int seller_id = NULL ;
    std::string firstProductName;
    std::string secondProductName;
    Product const* first = nullptr;
    Product const* second = nullptr;

    Storage storage;
    const char* dbPath = "C:\\Users\\anima\\source\\repos\\StorageClassLab1\\mydb.db";

    rc = sqlite3_open(dbPath, &db);
    if (rc != SQLITE_OK) {
        ErrorManager::reportError("Ошибка открытия бд", db);
        return rc;
    }

    createTable(db);

    while (true) {
        std::cout << "\nВыберите действие:\n"
            << "1. Вход существующего продавца\n"
            << "2. Регистрация нового продавца\n"
            << "0. Выход\n"
            << "Ваш выбор: ";

        std::cin >> choice;

        if (choice == 0) {
            sqlite3_close(db);
            return 0; 
        }

        switch (choice) {
        case 1:
            std::cout << "Введите логин:\n";
            std::cin >> login;
            std::cout << "Введите пароль:\n";
            std::cin >> password;

        if (!sellerManager.login(db, login, password)) {
            ErrorManager::loginError();
            continue;
        }

            std::cout << "Вход выполнен успешно!\n";

            if (!sellerManager.getSellerIdByUsername(db, login, seller_id)) {
                std::cerr << "Ошибка получения ID продавца.\n";
                continue;  
            }

            break;

        case 2:
            std::cout << "Регистрация нового продавца:\n";
            std::cout << "Введите логин:\n";
            std::cin >> login;
            std::cout << "Введите пароль:\n";
            std::cin >> password;

            if (sellerManager.registerSeller(db, login, password, seller_id)) {
                std::cout << "Регистрация успешна!\n";

            }
            else {
                std::cerr << "Ошибка регистрации продавца." << std::endl;
                sqlite3_close(db);
                return 1; 
            }
            break;

        default:
            ErrorManager::choiceError();
            break;
        }


		if (login == "admin" || password == "admin") {
            std::cout << "Добро пожаловать, администратор!\n";
            std::cout << "Введите seller_id: ";
            std::cin >> seller_id;
            currentSeller = std::make_unique<Admin>(login, password, seller_id);
        }
        else {
            currentSeller = std::make_unique<Seller>(login, password, seller_id);
        }
        loadProductsFromDb(db, storage);


        while (true) {
            std::cout << "\nВыберите действие:\n"
                << "1. Добавить продукт\n"
                << "2. Удалить продукт\n"
                << "3. Обновить продукт\n"
                << "4. Показать список продуктов\n"
                << "5. Найти товары с низким запасом\n"
                << "6. Сравнить два товара\n"
                << "0. Выход\n"
                << "Ваш выбор: ";

            std::cin >> choice;

            switch (choice) {
            case 1:
                system("cls");
                addToTable(storage, db, seller_id); 
                break;

            case 2:
                system("cls");
                currentSeller->removeProduct(storage, seller_id);
                break;

            case 3:
                system("cls");
                updateProduct(storage);
                break;

            case 4:
                system("cls");
                showProducts(storage);
                break;

            case 5:
                system("cls");
                findLowStockProducts(storage);
                break;

            case 6:
                system("cls");
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Введите имя первого продукта для сравнения: ";
                std::getline(std::cin, firstProductName);
                std::cout << "Введите имя второго продукта для сравнения: ";
                std::getline(std::cin, secondProductName);
                first = findProductByName(storage, firstProductName);
                second = findProductByName(storage, secondProductName);
                comprasionCheck(first, second);
                break;

            case 0:
                sqlite3_close(db);
                return 0;

            default:
                ErrorManager::choiceError();
            }
        }
    }
}
