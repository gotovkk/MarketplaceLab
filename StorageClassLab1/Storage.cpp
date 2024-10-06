#pragma once

#include "Storage.h"
using namespace std;

const std::vector<std::unique_ptr<Product>>& Storage::productsList() const
{
	return products;
}

void Storage::addProduct(std::unique_ptr<Product> product) {
	for (const auto& existProduct : products) {
		if (existProduct->getName() == product->getName() && existProduct->getSellerId() == product->getSellerId()) {
			int newAmount = existProduct->getAmount() + product->getAmount();
			existProduct->setAmount(newAmount);
			return;
		}
	}
	products.push_back(std::move(product));
}



bool Storage::removeProduct(const string_view name, int seller_id) {
	for (auto iter = products.begin(); iter != products.end(); iter++) {
		if ((*iter)->getName() == name) {
			products.erase(iter);
			return true;
		}
	}
	cout << "Товар не найден " << endl;
	return false;
}

void Storage::allProductsList() const
{
	for (const auto& product : products) {
		cout << "----------------------" << endl;
		product->printInfo();
	}
	cout << "----------------------" << endl;

}

vector<unique_ptr<Product>> Storage::findLowStockProd(int limit) const {
	vector<unique_ptr<Product>> lowStock;
	for (const auto& product : products) {
		if (product->getAmount() <= limit) {
			lowStock.push_back(make_unique<Product>(*product));
		}
	}
	return lowStock;
}

void removeProduct(Storage& storage) {
	int seller_id;
	cout << "Введите ID продавца: ";
	cin >> seller_id;
	string name;
	cout << "Введите название продукта для удаления : ";
	cin >> name;
	storage.removeProduct(name, seller_id);
}

void showProducts(const Storage& storage) {
	cout << "Список предметов:" << endl;
	storage.allProductsList();
}

void findLowStockProducts(const Storage& storage) {
	int limit;
	cout << "Введите лимит для низкого запаса: ";
	cin >> limit;
	auto lowStock = storage.findLowStockProd(limit);
	cout << "Товары с низким запасом:" << endl;
	for (const auto& product : lowStock) {
		product->printInfo();
	}
}

void amountChange(const Storage& storage, std::string_view name)
{
	int operationChoice;
	std::cout << "Выберите операцию (1 - добавить, 2 - уменьшить): ";
	std::cin >> operationChoice;

	int amount;
	std::cout << "Введите количество для обновления: ";
	std::cin >> amount;

	auto& products = storage.productsList();
	for (const auto& product : products) {
		if (product->getName() == name) {
			if (operationChoice == 1) {
				*product += amount;
			}
			else if (operationChoice == 2) {
				*product -= amount;
			}
			break;
		}
	}
}

void Storage::updateProduct(const std::string_view name, Field updateField, const std::variant<double, std::string>& value) const {
	for (const auto& product : products) {
		if (product->getName() == name) {
			switch (updateField) {
				using enum Field;
			case Price:
				product->setPrice(std::get<double>(value));
				break;
			case Amount: {
				auto amountChange = static_cast<int>(std::get<double>(value));
				product->setAmount(amountChange);
				break;
			}
			default:
				break;
			}
			return;
		}
	}
}


void addToTable(Storage& storage, sqlite3* db, int seller_id) {
	string name;
	string category;
	string description;
	double price;
	int amount;
	int category_id;

	cout << "Введите название продукта: ";
	cin >> name;
	cout << "Введите описание продукта: ";
	cin.ignore();
	getline(cin, description);
	cout << "Введите цену: ";
	cin >> price;
	cout << "Введите количество: ";
	cin >> amount;
	cout << "Введите ID категории ";
	cin >> category_id;


	storage.addProduct(std::make_unique<Product>(name, description, price, amount, seller_id, category_id));

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::string sqlInsert = std::format(
		"INSERT INTO products (name, description, price, seller_id, category_id, amount) VALUES ('{}', '{}', {}, {}, {}, {});",
		name, description, price, seller_id, category_id, amount);



	char* errMsg = nullptr;
	int rc = sqlite3_exec(db, sqlInsert.c_str(), nullptr, nullptr, &errMsg);
	if (rc != SQLITE_OK) {
		std::cerr << "Ошибка добавления продукта в базу данных: " << errMsg << std::endl;
		sqlite3_free(errMsg);
	}
	else {
		std::cout << "Продукт успешно добавлен в базу данных." << std::endl;
	}
}

void updateProduct(const Storage& storage) {
	string name;
	string color;
	double price;
	int fieldChoice;

	cout << "Введите название продукта для обновления: ";
	cin >> name;
	cout << "Выберите поле для обновления (1 - цвет, 2 - цена, 3 - вес, 4 - количество): ";
	cin >> fieldChoice;

	if (fieldChoice == 1) {
		cout << "Введите новый цвет: ";
		cin >> color;
		storage.updateProduct(name, Field::Color, color);
	}
	else if (fieldChoice == 2) {
		cout << "Введите новую цену: ";
		cin >> price;
		storage.updateProduct(name, Field::Price, price);
	}
	else if (fieldChoice == 3) {
		amountChange(storage, name);
	}
}

Product const* findProductByName(const Storage& storage, std::string_view productName) {
	for (const auto& product : storage.productsList()) {
		if (product->getName() == productName) {
			return product.get();
		}
	}
	return nullptr;
}

void createTable(sqlite3* db) {
	const char* sql =
		"CREATE TABLE IF NOT EXISTS products ("
		"product_id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"name VARCHAR(100) NOT NULL, "
		"description TEXT, "  
		"price DECIMAL(10, 2) NOT NULL, " 
		"amount INTEGER NOT NULL, " 
		"seller_id INTEGER NOT NULL, "  
		"category_id INTEGER, "
		"FOREIGN KEY (seller_id) REFERENCES sellers(seller_id), "
		"FOREIGN KEY (category_id) REFERENCES categories(category_id));";

	char* errMsg = nullptr;
	int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
	if (rc != SQLITE_OK) {
		std::cerr << "Ошибка в создании таблицы" << errMsg << std::endl;
		sqlite3_free(errMsg);
	}
}


void loadProductsFromDb(sqlite3* db, Storage& storage) {
	const char* selectFrom = R"(
        SELECT name, description, price, amount, seller_id, category_id 
        FROM products;
    )";
	sqlite3_stmt* stmt;

	if (sqlite3_prepare_v2(db, selectFrom, -1, &stmt, nullptr) == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
			std::string description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
			double price = sqlite3_column_double(stmt, 2);
			int amount = sqlite3_column_int(stmt, 3);
			int seller_id = sqlite3_column_int(stmt, 4); // Исправлено
			int category_id = sqlite3_column_int(stmt, 5);

			auto product = std::make_unique<Product>(name, description, price, amount, seller_id, category_id);
			storage.addProduct(std::move(product));
		}
	}
	else {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
	}

	sqlite3_finalize(stmt);
}
