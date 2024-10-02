#include <iostream>
#include <vector>
#include <variant>
#include "Storage.h"
#include "Product.h"


using namespace std;

//таблица
void createTable(sqlite3* db) {
    const char* sql =
        "CREATE TABLE IF NOT EXISTS products ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT UNIQUE NOT NULL, "
        "category TEXT NOT NULL, "
        "color TEXT DEFAULT 'Не указан', "
        "price REAL NOT NULL, "
        "weight REAL DEFAULT 0.0, "
        "amount INTEGER DEFAULT 1);";

    char* errMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка в создании таблицы" << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

// Сейчас написать выгрузку данных с таблицы в сторагу
void loadProductsFromDb(sqlite3* db, Storage& storage) {

}

int main() {
    system("chcp 1251");
    sqlite3* db;
    char* errMsg = 0;
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

    while (true) {
        cout << "\nВыберите действие:\n"
            << "1. Добавить продукт\n"
            << "2. Удалить продукт\n"
            << "3. Обновить продукт\n"
            << "4. Показать список продуктов\n"
            << "5. Найти товары с низким запасом\n"
            << "6. Сравнить два товара\n"
            << "0. Выход\n"
            << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
            
        case 1:
            addProduct(storage);
            break;

        case 2:
            removeProduct(storage);
            break;

        case 3:
            updateProduct(storage);
            break;

        case 4:
            showProducts(storage);
            break;

        case 5:
            findLowStockProducts(storage);
            break;
        case 6:
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "Введите имя первого продукта для сравнение: ";
            getline(cin, firstProductName);

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            
            cout << "Введите имя второго  продукта для сравнение: ";
            getline(cin, secondProductName);



            for (const auto& product : storage.productsList()) {
                if (product->getName() == firstProductName) {
                    first = product.get();
                }
                else if (product->getName() == secondProductName) {
                    second = product.get();
                }
            }

            if (first && second) {
                cout << "Результат сравнение товаров:\n";
                *first == *second;
            }
            else { cout << "Продукты не найдены\n"; }
            break;

        case 0:
            return 0;

        default:
            cout << "Неверный выбор, попробуйте снова." << endl;
        }
    }
}

