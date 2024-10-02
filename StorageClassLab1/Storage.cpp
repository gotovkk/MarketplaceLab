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

void Storage::updateProduct(const string_view name, Field updateField, const variant<double, string>& value) const {
	for (const auto& product : products) {
		if (product->getName() == name) {
			switch (updateField) {
			using enum Field;
			case Color:
				product->setColor(get<string>(value));
				break;
			case Price:
				product->setPrice(get<double>(value));
				break;
			case Weight:
				product->setWeight(get<double>(value));
				break;
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
		product->printInfo();
	}
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

/*std::vector<Product> Storage::filterByPrice(double maxPrice) const
{
	std::vector<Product> filteredProducts;

	for (const auto& product : products) {

	}


	return std::vector<Product>();
}*/


//Добавление продуктов и вставочка в таблицу
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
	cin >> color;
	cout << "Введите количество: ";
	cin >> amount;

	storage.addProduct(make_unique<Product>(name, category, price, weight, color, amount));

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::string sqlInsert = "INSERT INTO products (name, category, color, price, weight, amount) VALUES ('" +
		name + "', '" + 
		category + "', '" + 
		color + "', " +
		std::to_string(price) + ", " + 
		std::to_string(weight) + ", " +
		std::to_string(amount) + ");";
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
	cout << "Выберите поле для обновления (1 - цвет, 2 - цена, 3 - вес): ";
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
