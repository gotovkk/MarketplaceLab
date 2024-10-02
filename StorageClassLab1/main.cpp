#include <iostream>
#include <vector>
#include <variant>
#include "Storage.h"
#include "Product.h"


using namespace std;

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

    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка в создании таблицы" << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void loadProductsFromDb(sqlite3* db, Storage& storage) {
    const char* selectFrom = "SELECT name, category, color, price, weight, amount FROM products;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, selectFrom, -1, &stmt, 0) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string category = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            std::string color = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            double price = sqlite3_column_double(stmt, 3);
            double weight = sqlite3_column_double(stmt, 4);
            int amount = sqlite3_column_int(stmt, 5);

            std::unique_ptr<Product> product = std::make_unique<Product>(name, category, price, weight, color, amount);
            storage.addProduct(std::move(product));
        }
    }

    sqlite3_finalize(stmt);
}

int main() {
    system("chcp 1251");
    sqlite3* db;
    char* errMsg = nullptr;
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
            addToTable(storage, db);
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
            sqlite3_close(db);
            return 0;

        default:
            cout << "Неверный выбор, попробуйте снова." << endl;
        }
    }
}

