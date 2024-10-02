#include <iostream>
#include <vector>
#include <variant>
#include "Storage.h"
#include "Product.h"

using namespace std;

int main() {

    system("chcp 1251");
    cout << "Нажмите Enter, чтобы начать...";
    cin.get();

    sqlite3* db;
    int rc;
    int choice;
    std::string firstProductName;
    std::string secondProductName;
    Product const* first = nullptr;
    Product const* second = nullptr;

    const char* dbPath = "C:\\Users\\anima\\source\\repos\\StorageClassLab1\\mydb.db";

    rc = sqlite3_open(dbPath, &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка открытия бд" << sqlite3_errmsg(db) << std::endl;
    }

    createTable(db);

    Storage storage;

    loadProductsFromDb(db, storage);
    system("cls");
    while (true) {

        cout << "\nВыберите действие:\n"
            << "1. Добавить продукт\n"
            << "2. Удалить продукт\n"
            << "3. Обновить продукт\n"
            << "4. Показать список продуктов\n"
            << "5. Найти товары с низким запасом\n"
            << "6. Сравнить два товара\n"
            << "0. Выход\n"
            << "Ваш выбор:";

        cin >> choice;

        switch (choice) {

        case 1:
            system("cls");

            addToTable(storage, db);
            break;

        case 2:
            system("cls");

            removeProduct(storage);
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

            cout << "Введите имя первого продукта для сравнение: ";
            getline(cin, firstProductName);

            cout << "Введите имя второго  продукта для сравнение: ";
            getline(cin, secondProductName);

            first = findProductByName(storage, firstProductName);
            second = findProductByName(storage, secondProductName);

            comprasionCheck(first, second);
            break;

        case 0:
            sqlite3_close(db);
            return 0;

        default:
            cout << "Неверный выбор, попробуйте снова." << endl;
        }
    }
}

