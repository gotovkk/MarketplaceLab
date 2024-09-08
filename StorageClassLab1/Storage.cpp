#include "Storage.h"
using namespace std;

void Storage::addProduct(const Product& product) {
	for (auto& existProducts : products) {
		if (existProducts.getName() == product.getName()) {
			int newAmount = existProducts.getAmount() + product.getAmount();
			existProducts.setAmount(newAmount);
			return;
		}
	}
	products.push_back(product);
}

bool Storage::removeProduct(const string_view name) {
	for (auto iter = products.begin(); iter != products.end(); iter++) {
		if (iter->getName() == name) {
			products.erase(iter);
			return true;
		}
	}
	cout << "������� �� ������" << endl;
	return false;
}

void Storage::updateProduct(const string_view name, field updateField, const variant<double, string>& value) {
	for (auto& product : products) {
		if (product.getName() == name) {
			switch (updateField) {
			case field::color:
				product.setColor(get<string>(value));
				break;
			case  field::price:
				product.setPrice(get<double>(value));
				break;
			case field::weight:
				product.setWeight(get<double>(value));
				break;
			default:
				break;
			}
		}
	}
}

void Storage::productsList() const {
	for (const auto& product : products) {
		product.printInfo();
	}
}

vector<Product> Storage::findLowStockProd(int limit) const {
	vector<Product> lowStock;
	for (auto const& product : products) {
		if (product.getAmount() <= limit) {
			lowStock.push_back(product);
		}
	}
	return lowStock;
}

void addProduct(Storage& storage) {
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
	cin >> color; // Можно оставить как есть
	cout << "Введите количество: ";
	cin >> amount;

	storage.addProduct(Product(name, category, price, weight, color, amount));
}

void removeProduct(Storage& storage) {
	string name;
	cout << "Введите название продукта для удаления : ";
	cin >> name;
	storage.removeProduct(name);
}

void updateProduct(Storage& storage) {
	string name;
	string color;
	double price;
	double weight;
	int fieldChoice;

	cout << "Введите название продукта для обновления: ";
	cin >> name;
	cout << "Выберите поле для обновления (1 - цвет, 2 - цена, 3 - вес): ";
	cin >> fieldChoice;

	if (fieldChoice == 1) {
		cout << "Введите новый цвет: ";
		cin >> color;
		storage.updateProduct(name, field::color, color);
	}
	else if (fieldChoice == 2) {
		cout << "Введите новую цену: ";
		cin >> price;
		storage.updateProduct(name, field::price, price);
	}
	else if (fieldChoice == 3) {
		cout << "Введите новый вес: ";
		cin >> weight;
		storage.updateProduct(name, field::weight, weight);
	}
}

void showProducts(const Storage& storage) {
	cout << "Список предметов:" << endl;
	storage.productsList();
}

void findLowStockProducts(const Storage& storage) {
	int limit;
	cout << "Введите лимит для низкого запаса: ";
	cin >> limit;
	auto lowStock = storage.findLowStockProd(limit);
	cout << "Товары с низким запасом:" << endl;
	for (const auto& product : lowStock) {
		product.printInfo();
	}
}
