#include "Storage.h"
using namespace std;

const std::vector<std::unique_ptr<Product>>& Storage::productsList() const
{
	return products;
}

void Storage::addProduct(unique_ptr<Product> product) {
	for (const auto& existProduct : products) {
		if (existProduct->getName() == product->getName()) {
			int newAmount = existProduct->getAmount() + product->getAmount();
			existProduct->setAmount(newAmount);
			return;
		}
	}
	products.push_back(move(product));
}


bool Storage::removeProduct(const string_view name) {
	for (auto iter = products.begin(); iter != products.end(); iter++) {
		if ((*iter)->getName() == name) {
			products.erase(iter);
			return true;
		}
	}
	cout << "Товар не найден " << endl;
	return false;
}

void Storage::updateProduct(const std::string_view name, Field updateField, const std::variant<double, std::string>& value) const {
	for (const auto& product : products) {
		if (product->getName() == name) {
			switch (updateField) {
				using enum Field;
			case Color:
				product->setColor(std::get<std::string>(value));
				break;
			case Price:
				product->setPrice(std::get<double>(value));
				break;
			case Weight:
				product->setWeight(std::get<double>(value));
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

void addToTable(Storage& storage, sqlite3* db) {
	string name;
	string category;
	string color = "Не указан";
	double price;
	double weight;
	int amount;

	cout << "Введите название продукта: ";
	cin >> name;
	cout << "Введите категорию: ";
	cin >> category;
	cout << "Введите цену: ";
	cin >> price;
	cout << "Введите вес: ";
	cin >> weight;
	cout << "Введите цвет (по умолчанию 'Не указан'): ";
	cin >> color;
	cout << "Введите количество: ";
	cin >> amount;

	storage.addProduct(make_unique<Product>(name, category, price, weight, color, amount));

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::string sqlInsert = std::format(
		"INSERT INTO products (name, category, color, price, weight, amount) VALUES ('{}', '{}', '{}', {}, {}, {});",
		name, category, color, price, weight, amount);

	char* errMsg = nullptr;
	int rc = sqlite3_exec(db, sqlInsert.c_str(), nullptr, nullptr, &errMsg);
	if (rc != SQLITE_OK) {
		std::cerr << "Ошибка добавления продукта в базу данных: " << errMsg << std::endl;
		sqlite3_free(errMsg);  // Освобождаем память, выделенную для сообщения об ошибке
	}
	else {
		std::cout << "Продукт успешно добавлен в базу данных." << std::endl;
	}
}

void removeProduct(Storage& storage) {
	string name;
	cout << "Введите название продукта для удаления : ";
	cin >> name;
	storage.removeProduct(name);
}

void updateProduct(const Storage& storage) {
	string name;
	string color;
	double price;
	double weight;
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
		cout << "Введите новый вес: ";
		cin >> weight;
		storage.updateProduct(name, Field::Weight, weight);
	}
	else if (fieldChoice == 4) {
		amountChange(storage, name);
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


