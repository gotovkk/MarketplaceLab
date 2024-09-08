#include <iostream>
#include <vector>
#include <variant>
#include "Storage.h"
#include "Product.h"


using namespace std;

int main() {
    system("chcp 1251");

    Storage storage;  // Создание объекта Storage
    int choice;

    while (true) {
        cout << "\nВыберите действие:\n"
            << "1. Добавить продукт\n"
            << "2. Удалить продукт\n"
            << "3. Обновить продукт\n"
            << "4. Показать список продуктов\n"
            << "5. Найти товары с низким запасом\n"
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

        case 0:
            return 0;

        default:
            cout << "Неверный выбор, попробуйте снова." << endl;
        }
    }
}